#include <string.h>
#include <stdio.h>
#include <math.h>

#include "Image.h"
#include "Color.h"

#include "Utilities.h"
#include "NoiseBuffer2D.h"
#include "RNG31Core/AbstractRNGCore.h"
#include "RNG31Core/GBFlip.h"
#include "RNG31Transform/Uniform.h"
#include "RNG31Transform/Perlin.h"

/* Image Properties */
#define WIDTH 1024
#define HEIGHT 1024

#define FILENAME_LEN 1024

void describe();
void generatePerlinTexture(RNG31::Perlin *perlin, NoiseBuffer2D *noise, Image *img);
void makePerlinNoise(RNG31::Perlin *perlin, NoiseBuffer2D *noise, char *fileName);
void encodeNoiseAsGrayscaleImage(NoiseBuffer2D *noise, Image *img);

int main(int argc, char **argv)
{
    Image img(WIDTH, HEIGHT);
    img.fill(Color::BLK);

    NoiseBuffer2D noise(WIDTH, HEIGHT);

    RNG31::GBFlip gbFlip;
    RNG31::Uniform urng(&gbFlip);
    RNG31::Perlin perlin(&urng);

    bool running = true;
    while(running) {
        int menuOption = getUserInt(
            1, 3,
            "Would you like to continue?\n"
            "  1. Describe what this is\n"
            "  2. Generate a Perlin noise texture\n"
            "  3. Quit");
        switch(menuOption) {
        case 1:
            describe();
            break;
        case 2:
            generatePerlinTexture(&perlin, &noise, &img);
            break;
        case 3:
            running = false;
            break;
        }
    }

    return 0;
}

void describe()
{
    message(5.0, "Perlin noise has many uses in computer graphics: alpha blending, terrain height generation, color variation, and so much more.");
    message(2.0, "Perlin noise lends itself to using randomness to create interesting variation.");
    message(2.0, "This example doesn't actually use randomness.");
    message(3.0, "Rather, this is a tool for exploring how the parameters change the resulting texture.");
    message(3.0, "As you learn what the parameters do, you can randomize the ones you want to get a specific range of effects.\n");

    message(5.0, "A brief description of what is happening is this: Perlin noise is sampling a pseudorandom 3D volume (generalizable to more dimensions).");
    message(5.0, "  The x and y scale parameters are how tightly to sample the cube as we walk through a 2D slice of the volume. Bigger numbers mean higher-freqency noise.");
    message(5.0, "  The z value describes where we walk through a 2D slice of the volume. Moving this up and down slightly can create wave-like progressions of textures.");
    message(5.0, "  If the layer count is greater than one, we will add more noise on top of the previous layers. This can create more fractal-like affects.");
    message(5.0, "    - Layer attentuation makes each succeeding layer have less strength, so the later layers are \"fainter\".");
    message(5.0, "    - Layer scale makes each succeeding layer smaller to create that fractal feeling.");
    message(3.0, "  Not usually part of a Perlin Noise discussion, I allow you to choose from different easing curves.");
    message(2.0, "    - Normal Perlin Noise uses Smooth Step or Smoother Step. Some are more interesting than others.");
    message(0.0, "");

    message(0.0, "For more information: https://en.wikipedia.org/wiki/Perlin_noise\n");
}

void generatePerlinTexture(RNG31::Perlin *perlin, NoiseBuffer2D *noise, Image *img)
{
    char fileName[FILENAME_LEN];
    makePerlinNoise(perlin, noise, fileName);
    encodeNoiseAsGrayscaleImage(noise, img);
    writeBMPImage(img, fileName);
}

void makePerlinNoise(RNG31::Perlin *perlin, NoiseBuffer2D *noise, char *fileName)
{
    double xScale = getUserFlt(0.125, 16.0, "X Scale (0.125 - 16.0)");
    double yScale = getUserFlt(0.125, 16.0, "Y Scale (0.125 - 16.0)");
    double zValue = getUserFlt(-1.0, 1.0, "Z Value (-1.0 - 1.0)");
    int interpolation = getUserInt(
        1, 6,
        "Interpolation Method:\n"
        "  1. Smoother Step\n"
        "  2. Smooth Step\n"
        "  3. Linear\n"
        "  4. Quad In Out\n"
        "  5. Elastic In Out\n"
        "  6. Bounce In Out");

    Ease::EasingMethod easingMethod = Ease::EasingMethod::SMOOTHERSTEP;
    char easingMethodName[32];
    switch(interpolation) {
    case 1:
        easingMethod = Ease::EasingMethod::SMOOTHERSTEP;
        strcpy(easingMethodName, "SmootherStep");
        break;
    case 2:
        easingMethod = Ease::EasingMethod::SMOOTHSTEP;
        strcpy(easingMethodName, "SmoothStep");
        break;
    case 3:
        easingMethod = Ease::EasingMethod::LINEAR;
        strcpy(easingMethodName, "Linear");
        break;
    case 4:
        easingMethod = Ease::EasingMethod::QUAD_IN_OUT;
        strcpy(easingMethodName, "QuadInOut");
        break;
    case 5:
        easingMethod = Ease::EasingMethod::ELASTIC_IN_OUT;
        strcpy(easingMethodName, "ElasticInOut");
        break;
    case 6:
        easingMethod = Ease::EasingMethod::BOUNCE_IN_OUT;
        strcpy(easingMethodName, "BounceInOut");
        break;
    }
    perlin->setEasingMethod(easingMethod);

    int layerCount = getUserInt(1, 4, "Layer Count (1 - 4)");
    double layerAttenuation = 0.5;
    double layerScale = 0.5;

    if(layerCount > 1) {
        layerScale       = getUserFlt(1.125, 8.0, "Layer Size Scale (1.125 - 8.0)");
        layerAttenuation = getUserFlt(0.125, 0.875, "Layer Signal Attenuation (0.125 - 0.875)");

        perlin->layeredFill(noise, layerCount, layerScale, layerAttenuation, xScale, yScale, zValue);
        snprintf(fileName, FILENAME_LEN, "Perlin_%s_%0.3f-%0.3f-%0.3f_%d-%0.3f%0.3f.bmp", easingMethodName, xScale, yScale, zValue, layerCount, layerScale, layerAttenuation);
    } else {
        perlin->fill(noise, xScale, yScale, zValue);
        snprintf(fileName, FILENAME_LEN, "Perlin_%s_%0.3f-%0.3f-%0.3f.bmp", easingMethodName, xScale, yScale, zValue);
    }
}

void encodeNoiseAsGrayscaleImage(NoiseBuffer2D *noise, Image *img)
{
    assert(noise->width() == img->width());
    assert(noise->height() == img->height());

    Color c;
    for(uint32_t row = 0; row < noise->height(); ++row) {
        for(uint32_t col = 0; col < noise->width(); ++col) {
            double value = noise->at(row, col);
            c.setF(value, value, value, 1.0);
            img->set(row, col, c);
        }
    }
}
