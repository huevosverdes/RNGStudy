// https://en.wikipedia.org/wiki/Chaos_game
// https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle#Chaos_game

#include <stdio.h>
#include <math.h>

#include "BMPWriter.h"
#include "Image.h"
#include "Color.h"

#include "Utilities.h"
#include "NoiseBuffer2D.h"
#include "BMPWriter.h"
#include "RNG31Core/AbstractRNGCore.h"
#include "RNG31Transform/Uniform.h"
#include "RNG31Transform/Perlin.h"

// Image Properties
#define WIDTH 1200
#define HEIGHT 1200

enum class ColorMethod {
    SOLID = 0,
    XY    = 1,
    ANGLE = 2,
    NOISE = 3
};
ColorMethod colorMethod = ColorMethod::NOISE;

// Attractor Points
const double X1 = 5.0;
const double Y1 = HEIGHT - 5.0;
const double X2 = WIDTH - 5.0;
const double Y2 = Y1;
const double X3 = (X1 + X2) / 2.0;
const double Y3 = Y1 - (sqrt(3.0) / 2.0) * (HEIGHT - 10.0);

const double XCenter = X3;
const double YCenter = (Y3 + Y1) / 2.0;

NoiseBuffer2D bluNoise(WIDTH, HEIGHT);
NoiseBuffer2D grnNoise(WIDTH, HEIGHT);

Color colorAtPoint(int x, int y, ColorMethod method);
void demo(RNG31::Uniform *urng, Image *img, int *lastX, int *lastY, int *sampleCount);
void clearGame(RNG31::Uniform *urng, Image *img, int *lastX, int *lastY, int *sampleCount);
void playGame(RNG31::Uniform *urng, Image *img, int *lastX, int *lastY, int *sampleCount);
void addPoints(int count, RNG31::Uniform *urng, Image *img, int *lastX, int *lastY, int *sampleCount);
void writeImage(Image *img, const char *prefix, int count);

int main(int argc, char **argv)
{
    Image img(WIDTH, HEIGHT);
    img.fill(Color::BLK);

    RNG31::AbstractRNGCore *arng = getRNGCore();
    RNG31::Uniform *urng = new RNG31::Uniform(arng);

    int lastX, lastY, sampleCount;
    clearGame(urng, &img, &lastX, &lastY, &sampleCount);
    int running = 1;
    do {
        int actionCode = getUserInt(
            1, 5,
            "Choose an action:\n"
            "  1. Choose an RNG Core\n"
            "  2. Give me the demo introduction to the Chaos Game\n"
            "  3. Reset the current Chaos Game\n"
            "  4. Simulate multiple rounds of the Chaos Game\n"
            "  5. Quit");
        switch(actionCode) {
        case 1:
            delete urng;
            delete arng;
            arng = getRNGCore();
            urng = new RNG31::Uniform(arng);
            break;
        case 2:
            demo(urng, &img, &lastX, &lastY, &sampleCount);
            break;
        case 3:
            clearGame(urng, &img, &lastX, &lastY, &sampleCount);
            break;
        case 4:
            playGame(urng, &img, &lastX, &lastY, &sampleCount);
            break;
        case 5:
            running = 0;
            break;
        }
    } while(running);

    delete urng;
    delete arng;
    return 0;
}

Color colorAtPoint(int x, int y, ColorMethod method)
{
    double red, grn, blu;

    switch(method) {
    case ColorMethod::SOLID:
        red = 0.15;
        grn = 0.25;
        blu = 0.75;
        break;
    case ColorMethod::XY:
        red = 0.0;
        grn = (float)x / WIDTH;
        blu = (float)y / HEIGHT;
        break;
    case ColorMethod::ANGLE: {
        double vecCenterX = x - XCenter;
        double vecCenterY = y - YCenter;
        double pRadius = sqrt(vecCenterX*vecCenterX + vecCenterY*vecCenterY);

        double vecGrnX = X1 - XCenter;
        double vecGrnY = Y1 - YCenter;
        double triRadius = sqrt(vecGrnX*vecGrnX + vecGrnY*vecGrnY);
        double angleGrn = acos((vecCenterX * vecGrnX + vecCenterY * vecGrnY) / (triRadius * pRadius)) * 180.0 / M_PI;
        grn = (angleGrn <= 120.0) ? (120.0 - angleGrn) / 120.0 : 0.0;

        double vecBluX = X2 - XCenter;
        double vecBluY = Y2 - YCenter;
        double angleBlu = acos((vecCenterX * vecBluX + vecCenterY * vecBluY) / (triRadius * pRadius)) * 180.0 / M_PI;
        blu = (angleBlu <= 120.0) ? (120.0 - angleBlu) / 120.0 : 0.0;

        double vecRedX = X3 - XCenter;
        double vecRedY = Y3 - YCenter;
        double angleRed = acos((vecCenterX * vecRedX + vecCenterY * vecRedY) / (triRadius * pRadius)) * 180.0 / M_PI;
        red = (angleRed <= 120.0) ? (120.0 - angleRed) / 120.0 : 0.0; }
        break;
    case ColorMethod::NOISE:
        red = 0.0;
        blu = bluNoise.at((int)y, (int)x);
        grn = grnNoise.at((int)y, (int)x);
        break;
    };

    Color c;
    c.setF(red, grn, blu);
    return c;
}

void demo(RNG31::Uniform *urng, Image *img, int *lastX, int *lastY, int *sampleCount)
{
    if(*sampleCount != 0)
        clearGame(urng, img, lastX, lastY, sampleCount);

    message(2.0, "Let's play a chaotic game.");
    message(3.0, "We begin with the three corners of a triangle: { (%d, %d), (%d, %d), (%d, %d) }",
            (int)X1, (int)Y1,
            (int)X2, (int)Y2,
            (int)X3, (int)Y3);
    message(3.0, "Then we start at a random point: (%d, %d)", (int)*lastX, (int)*lastY);

    double nextX, nextY;
    int targetPoint = urng->next(1, 4);
    switch(targetPoint) {
    case 1: nextX = X1; nextY = Y1; break;
    case 2: nextX = X2; nextY = Y2; break;
    case 3: nextX = X3; nextY = Y3; break;
    }
    message(3.0, "Each step we pick one of the corners of the triangle at random: Corner #%d (%d, %d).", targetPoint, nextX, nextY);

    nextX += *lastX;
    nextY += *lastY;
    nextX /= 2.0;
    nextY /= 2.0;
    img->set((int)nextY, (int)nextX, colorAtPoint((int)nextX, (int)nextY, colorMethod));
    *lastX = nextX;
    *lastY = nextY;
    ++(*sampleCount);
    message(4.0, "Then we move to the point halfway between our current point and the randomly selected corner: (%d, %d)", nextX, nextY);
    writeImage(img, "Demo_ChaosGame", *sampleCount);

    addPoints(9, urng, img, lastX, lastY, sampleCount);
    message(4.0, "Let's do that a few more times ending at (%d, %d) after Move #%d.", nextX, nextY, *sampleCount);
    writeImage(img, "Demo_ChaosGame", *sampleCount);

    addPoints(90, urng, img, lastX, lastY, sampleCount);
    message(2.0, "A few more ending at (%d, %d) after Move #%d.", nextX, nextY, *sampleCount);
    writeImage(img, "Demo_ChaosGame", *sampleCount);

    addPoints(900, urng, img, lastX, lastY, sampleCount);
    message(2.0, "Keep going to (%d, %d) after Move #%d.", nextX, nextY, *sampleCount);
    writeImage(img, "Demo_ChaosGame", *sampleCount);

    addPoints(9000, urng, img, lastX, lastY, sampleCount);
    message(2.0, "Keep going to (%d, %d) after Move #%d.", nextX, nextY, *sampleCount);
    writeImage(img, "Demo_ChaosGame", *sampleCount);

    addPoints(90000, urng, img, lastX, lastY, sampleCount);
    message(2.0, "Keep going to (%d, %d) after Move #%d.", nextX, nextY, *sampleCount);
    writeImage(img, "Demo_ChaosGame", *sampleCount);

    addPoints(900000, urng, img, lastX, lastY, sampleCount);
    message(2.0, "Keep going to (%d, %d) after Move #%d.", nextX, nextY, *sampleCount);
    writeImage(img, "Demo_ChaosGame", *sampleCount);
    message(1.0, "");

    message(3.0, "If you look at the pictures you can see that no matter where we start,");
    message(3.0, "we always get pulled into a pattern called the Sierpiński Triangle.");
    message(3.0, "You might notice points where they shouldn't belong.");
    message(3.0, "Those happen at the beginning, before we get pulled into the fractal drawing pattern.");
    message(3.0, "The Sierpiński Triangle is a fractal, and we drew it with randomness!\n");

    message(0.0, "For more information: https://en.wikipedia.org/wiki/Sierpi%%C5%%84ski_triangle#Chaos_game.\n");

    clearGame(urng, img, lastX, lastY, sampleCount);
}

void clearGame(RNG31::Uniform *urng, Image *img, int *lastX, int *lastY, int *sampleCount)
{
    // Set Initial Values
    img->fill(Color::BLK);

    *sampleCount = 0;
    *lastX = urng->next(0, WIDTH);
    *lastY = urng->next(0, HEIGHT);
    printf("The game has been reset. Starting at (%d, %d).\n", *lastX, *lastY);

    // Do color things
    colorMethod = static_cast<ColorMethod>(
        getUserInt(
            static_cast<int>(ColorMethod::SOLID),
            static_cast<int>(ColorMethod::NOISE) + 1,
            "How would you like to color the results?\n"
            "  1. Solid\n"
            "  2. X-Y Gradient\n"
            "  3. Angular Gradient\n"
            "  4. Perlin Noise") - 1);

    if(colorMethod == ColorMethod::NOISE) {
        RNG31::Perlin perlin(urng);
        perlin.shuffle();

        perlin.fill(&bluNoise, 4.0, 4.0);
        bluNoise *= 0.5;
        bluNoise += 0.5;

        perlin.fill(&grnNoise, 16.0, 16.0);
    }

    // Draw Initial Point
    img->set((int)*lastY, (int)*lastX, colorAtPoint((int)*lastY, (int)*lastX, colorMethod));
}

void playGame(RNG31::Uniform *urng, Image *img, int *lastX, int *lastY, int *sampleCount)
{
    int count = getUserInt(1, 1000000, "How many points would you like to add?");
    addPoints(count, urng, img, lastX, lastY, sampleCount);
    writeImage(img, "ChaosGame", *sampleCount);
}

void addPoints(int count, RNG31::Uniform *urng, Image *img, int *lastX, int *lastY, int *sampleCount)
{
    for(int index = 0; index < count; ++index)
    {
        double nextX, nextY;
        int targetPoint = urng->next(1, 4);

        switch(targetPoint) {
        case 1:
            nextX = X1;
            nextY = Y1;
            break;
        case 2:
            nextX = X2;
            nextY = Y2;
            break;
        case 3:
            nextX = X3;
            nextY = Y3;
            break;
        }

        nextX += *lastX;
        nextY += *lastY;
        nextX /= 2.0;
        nextY /= 2.0;

        img->set((int)nextY, (int)nextX, colorAtPoint((int)nextX, (int)nextY, colorMethod));

        *lastX = nextX;
        *lastY = nextY;
    }
    *sampleCount += count;
}

void writeImage(Image *img, const char *prefix, int count)
{
    int len = strlen(prefix) + 13;
    char *fName = (char*)malloc(sizeof(char) * (len + 1));
    snprintf(fName, len, "%s_%07d.bmp", prefix, count);
    fName[len] = '\0';

    BMPWriter::write(fName, img);
    printf("Wrote File: %s\n", fName);
    free(fName);
}
