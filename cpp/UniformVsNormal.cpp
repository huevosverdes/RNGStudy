#include <stdio.h>

#include "Utilities.h"
#include "RNG31Core/AbstractRNGCore.h"
#include "RNG31Transform/Uniform.h"
#include "RNG31Transform/Normal.h"

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
    RNG31::AbstractRNGCore *arng = getRNGCore();
    RNG31::Uniform urng(arng);
    RNG31::Normal  nrng(arng);

    Image img(WIDTH, HEIGHT);
    img.fill(Color::BLK);

    const Color borderColor(0x88, 0x88, 0x88);
    drawBox(&img, RECT_UNIFORM_X-1, RECT_UNIFORM_Y-1, RECT_UNIFORM_W+2, RECT_UNIFORM_H+2, borderColor);
    drawBox(&img, RECT_NORMAL_X -1, RECT_NORMAL_Y -1, RECT_NORMAL_W +2, RECT_NORMAL_H +2, borderColor);

    for(int index = 0; index < 3000000; ++index) {
        int x = urng.next(RECT_UNIFORM_W + 1);
        int y = urng.next(RECT_UNIFORM_H + 1);
        addPoint(&img, x + RECT_UNIFORM_X, y + RECT_UNIFORM_Y);
    }
    for(int index = 0; index < 1500000; ++index) {
        const int STD_DEV_X = RECT_NORMAL_W / 8;
        const int MEAN_X = RECT_NORMAL_W / 2;
        const int STD_DEV_Y = RECT_NORMAL_H / 8;
        const int MEAN_Y = RECT_NORMAL_H / 2;

        int x = (int)nrng.next(STD_DEV_X, MEAN_X);
        int y = (int)nrng.next(STD_DEV_Y, MEAN_Y);
        if((0 <= x && x < RECT_NORMAL_W) &&
           (0 <= y && y < RECT_NORMAL_H))
            /* Accept point: within 4 standard deviations from mean */
            addPoint(&img, x + RECT_NORMAL_X, y + RECT_NORMAL_Y);
        else
            /* Reject point:more than 4 standard deviations from mean */
            --index;
    }

    writeImage(&img, "UniformVsNormal");

    delete arng;
    return 0;
}

void addPoint(Image *img, int x, int y)
{
#define STEP 50
#define MAX (255 - STEP)

    Color c = img->at(y, x);

    if(c.blu() <= MAX)
        c.setBlu(c.blu() + STEP);
    else if(c.grn() <= MAX)
        c.setGrn(c.grn() + STEP);
    else if(c.red() <= MAX)
        c.setRed(c.red() + STEP);
    else
        c.set(0xFF, 0xFF, 0xFF);

    img->set(y, x, c);
}

void drawBox(Image *img, int x, int y, int w, int h, Color c)
{
    for(int count = 0; count < w+1; ++count) {
        img->set(y    , x + count, c);
        img->set(y + h, x + count, c);
    }
    for(int count = 1; count < h; ++count) {
        img->set(y + count, x    , c);
        img->set(y + count, x + w, c);
    }
}

void writeImage(Image *img, const char *prefix)
{
    int len = strlen(prefix) + 13;
    char *fName = (char*)malloc(sizeof(char) * (len + 1));
    snprintf(fName, len, "%s.bmp", prefix);
    fName[len] = '\0';

    BMPWriter::write(fName, img);
    printf("Wrote File: %s\n", fName);
    printf("- The more times a point is sampled, the brighter it gets.\n");
    printf("- The box on the left contains random points with a Uniform sampling.\n");
    printf("- The box on the right contains random points with a Gaussian sampling within 4 standard deviations of the center.\n\n");
    free(fName);
}
