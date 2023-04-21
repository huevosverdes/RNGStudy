#include <string.h>
#include <stdio.h>
#include <math.h>

#include "Image.h"
#include "Color.h"

#include "Utilities.h"
#include "NoiseBuffer2D.h"
#include "RNG31Core/AbstractRNG31Core.h"
#include "RNG31Core/RNG31Core_GBFlip.h"
#include "RNG31Transform/RNG31_Uniform.h"
#include "RNG31Transform/RNG31_Perlin.h"

/* Image Properties */
#define WIDTH 1024
#define HEIGHT 1024

#define FILENAME_LEN 1024

void describe();
void generatePerlinTexture(RNG31_Perlin *perlin, NoiseBuffer2D *noise, Image *img);
void makePerlinNoise(RNG31_Perlin *perlin, NoiseBuffer2D *noise, char *fileName);
void encodeNoiseAsGrayscaleImage(NoiseBuffer2D *noise, Image *img);

int main(int argc, char **argv)
{
    Image *img = image_init(WIDTH, HEIGHT);
    image_fill(img, COLOR_BLK);

    NoiseBuffer2D *noise = noiseBuffer2D_init(WIDTH, HEIGHT);

    AbstractRNG31Core *arng = gbFlip_initDefault((RNG31Core_GBFlip*)malloc(sizeof(RNG31Core_GBFlip)));
    RNG31_Uniform *urng = (RNG31_Uniform*)malloc(sizeof(RNG31_Uniform));
    rng31Uniform_init(urng, arng);

    RNG31_Perlin perlin;
    rng31Perlin_init(&perlin, urng);

    int running = 1;
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
            generatePerlinTexture(&perlin, noise, img);
            break;
        case 3:
            running = 0;
            break;
        }
    }

    free(urng);
    free(arng);
    image_destroy(img);
    noiseBuffer2D_destroy(noise);
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

void generatePerlinTexture(RNG31_Perlin *perlin, NoiseBuffer2D *noise, Image *img)
{
    char fileName[FILENAME_LEN];
    makePerlinNoise(perlin, noise, fileName);
    encodeNoiseAsGrayscaleImage(noise, img);
    writeBMPImage(img, fileName);
}

void makePerlinNoise(RNG31_Perlin *perlin, NoiseBuffer2D *noise, char *fileName)
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

    EasingMethod easingMethod = SMOOTHERSTEP;
    char easingMethodName[32];
    switch(interpolation) {
    case 1:
        easingMethod = SMOOTHERSTEP;
        strcpy(easingMethodName, "SmootherStep");
        break;
    case 2:
        easingMethod = SMOOTHSTEP;
        strcpy(easingMethodName, "SmoothStep");
        break;
    case 3:
        easingMethod = LINEAR;
        strcpy(easingMethodName, "Linear");
        break;
    case 4:
        easingMethod = QUAD_IN_OUT;
        strcpy(easingMethodName, "QuadInOut");
        break;
    case 5:
        easingMethod = ELASTIC_IN_OUT;
        strcpy(easingMethodName, "ElasticInOut");
        break;
    case 6:
        easingMethod = BOUNCE_IN_OUT;
        strcpy(easingMethodName, "BounceInOut");
        break;
    }
    perlin->easingMethod = easingMethod;

    int layerCount = getUserInt(1, 4, "Layer Count (1 - 4)");
    double layerAttenuation = 0.5;
    double layerScale = 0.5;

    if(layerCount > 1) {
        layerScale       = getUserFlt(1.125, 8.0, "Layer Size Scale (1.125 - 8.0)");
        layerAttenuation = getUserFlt(0.125, 0.875, "Layer Signal Attenuation (0.125 - 0.875)");

        rng31Perlin_layeredFill(perlin, noise, layerCount, layerScale, layerAttenuation, xScale, yScale, zValue);
        snprintf(fileName, FILENAME_LEN, "Perlin_%s_%0.3f-%0.3f-%0.3f_%d-%0.3f%0.3f.bmp", easingMethodName, xScale, yScale, zValue, layerCount, layerScale, layerAttenuation);
    } else {
        rng31Perlin_fill(perlin, noise, xScale, yScale, zValue);
        snprintf(fileName, FILENAME_LEN, "Perlin_%s_%0.3f-%0.3f-%0.3f.bmp", easingMethodName, xScale, yScale, zValue);
    }
}

void encodeNoiseAsGrayscaleImage(NoiseBuffer2D *noise, Image *img)
{
    assert(noise->width == img->width);
    assert(noise->height == img->height);

    Color c;
    for(int row = 0; row < noise->height; ++row) {
        for(int col = 0; col < noise->width; ++col) {
            double value = noiseBuffer2D_valueAt(noise, row, col);
            color_setF(&c, value, value, value, 1.0);
            image_setPixel(img, row, col, c);
        }
    }
}
