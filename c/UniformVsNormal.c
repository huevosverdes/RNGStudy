#include <stdio.h>

#include "Utilities.h"
#include "RNG31Core/AbstractRNG31Core.h"
#include "RNG31Transform/RNG31_Uniform.h"
#include "RNG31Transform/RNG31_Normal.h"

#include "BMPWriter.h"
#include "Image.h"
#include "Color.h"

/* Image Properties */
#define WIDTH    1280
#define HEIGHT    768
#define MARGIN     10
#define BOX_SIZE  625

const int RECT_UNIFORM_X = MARGIN;
const int RECT_UNIFORM_Y = (HEIGHT - BOX_SIZE) / 2;
const int RECT_UNIFORM_W = BOX_SIZE;
const int RECT_UNIFORM_H = BOX_SIZE;

const int RECT_NORMAL_X = MARGIN + MARGIN + BOX_SIZE;
const int RECT_NORMAL_Y = (HEIGHT - BOX_SIZE) / 2;
const int RECT_NORMAL_W = BOX_SIZE;
const int RECT_NORMAL_H = BOX_SIZE;

void addPoint(Image *img, int x, int y);
void drawBox(Image *img, int x, int y, int w, int h, Color c);
void writeImage(Image *img, const char *prefix);

int main(int argc, char **argv)
{
    AbstractRNG31Core *arng = getRNGCore();
    RNG31_Uniform *urng = (RNG31_Uniform*)malloc(sizeof(RNG31_Uniform));
    rng31Uniform_init(urng, arng);
    RNG31_Normal *nrng = (RNG31_Normal*)malloc(sizeof(RNG31_Normal));
    rng31Normal_init(nrng, arng);

    Image *img = image_init(WIDTH, HEIGHT);
    image_fill(img, COLOR_BLK);

    Color borderColor = {0xFF888888};
    drawBox(img, RECT_UNIFORM_X-1, RECT_UNIFORM_Y-1, RECT_UNIFORM_W+2, RECT_UNIFORM_H+2, borderColor);
    drawBox(img, RECT_NORMAL_X -1, RECT_NORMAL_Y -1, RECT_NORMAL_W +2, RECT_NORMAL_H +2, borderColor);

    for(int index = 0; index < 3000000; ++index) {
        int x = rng31Uniform_next(urng, 0, RECT_UNIFORM_W + 1);
        int y = rng31Uniform_next(urng, 0, RECT_UNIFORM_H + 1);
        addPoint(img, x + RECT_UNIFORM_X, y + RECT_UNIFORM_Y);
    }
    for(int index = 0; index < 1500000; ++index) {
        const int STD_DEV_X = RECT_NORMAL_W / 8;
        const int MEAN_X = RECT_NORMAL_W / 2;
        const int STD_DEV_Y = RECT_NORMAL_H / 8;
        const int MEAN_Y = RECT_NORMAL_H / 2;

        int x = (int)rng31Normal_next(nrng, STD_DEV_X, MEAN_X);
        int y = (int)rng31Normal_next(nrng, STD_DEV_Y, MEAN_Y);
        if((0 <= x && x < RECT_NORMAL_W) &&
           (0 <= y && y < RECT_NORMAL_H))
            /* Accept point: within 4 standard deviations from mean */
            addPoint(img, x + RECT_NORMAL_X, y + RECT_NORMAL_Y);
        else
            /* Reject point:more than 4 standard deviations from mean */
            --index;
    }

    writeImage(img, "UniformVsNormal");

    free(urng);
    free(arng);
    return 0;
}

void addPoint(Image *img, int x, int y)
{
#define STEP 50
#define MAX (255 - STEP)

    Color c = image_colorAt(img, y, x);

    if(c.bytes[BLU_BYTE] <= MAX)
        c.bytes[BLU_BYTE] += STEP;
    else if(c.bytes[GRN_BYTE] <= MAX)
        c.bytes[GRN_BYTE] += STEP;
    else if(c.bytes[RED_BYTE] <= MAX)
        c.bytes[RED_BYTE] += STEP;
    else
        c.value = 0xFFFFFFFF;

    image_setPixel(img, y, x, c);
}

void drawBox(Image *img, int x, int y, int w, int h, Color c)
{
    for(int count = 0; count < w+1; ++count) {
        image_setPixel(img, y    , x + count, c);
        image_setPixel(img, y + h, x + count, c);
    }
    for(int count = 1; count < h; ++count) {
        image_setPixel(img, y + count, x    , c);
        image_setPixel(img, y + count, x + w, c);
    }
}

void writeImage(Image *img, const char *prefix)
{
    int len = strlen(prefix) + 13;
    char *fName = (char*)malloc(sizeof(char) * (len + 1));
    snprintf(fName, len, "%s.bmp", prefix);
    fName[len] = '\0';

    bmp_write(fName, img);
    printf("Wrote File: %s\n", fName);
    printf("- The more times a point is sampled, the brighter it gets.\n");
    printf("- The box on the left contains random points with a Uniform sampling.\n");
    printf("- The box on the right contains random points with a Gaussian sampling within 4 standard deviations of the center.\n\n");
    free(fName);
}
