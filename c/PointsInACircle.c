#include <stdio.h>
#include <math.h>

#include "Utilities.h"
#include "RNG31Core/AbstractRNG31Core.h"
#include "RNG31Transform/RNG31_Uniform.h"

#include "Image.h"
#include "Color.h"

/* Image Properties */
#define WIDTH    1280
#define HEIGHT    768
#define MARGIN     10
#define DIAMETER  625

const double RADIUS = DIAMETER / 2.0;
const double CENTER_UNCORRECTED_X = MARGIN + RADIUS;
const double CENTER_UNCORRECTED_Y = HEIGHT / 2;
const double CENTER_CORRECTED_X = MARGIN + MARGIN + DIAMETER + RADIUS;
const double CENTER_CORRECTED_Y = CENTER_UNCORRECTED_Y;

int main(int argc, char **argv)
{
    AbstractRNG31Core *arng = getRNGCore();
    RNG31_Uniform *urng = (RNG31_Uniform*)malloc(sizeof(RNG31_Uniform));
    rng31Uniform_init(urng, arng);

    Image *img = image_init(WIDTH, HEIGHT);
    image_fill(img, COLOR_BLK);

    const int ITERATIONS = 450000;
    for(int index = 0; index < ITERATIONS; ++index) {
        double radius = rng31Uniform_nextFloat(urng, 0.0, RADIUS);
        double radians = rng31Uniform_nextFloat(urng, 0.0, 2.0 * M_PI);
        double x = radius * cos(radians) + CENTER_UNCORRECTED_X;
        double y = radius * sin(radians) + CENTER_UNCORRECTED_Y;
        addSamplePoint(img, (int)x, (int)y);
    }

    for(int index = 0; index < ITERATIONS; ++index) {
        double x, y;
        rng31Uniform_pointInCircle(urng, RADIUS, &x, &y);
        x += CENTER_CORRECTED_X;
        y += CENTER_CORRECTED_Y;
        addSamplePoint(img, (int)x, (int)y);
    }

    writeBMPImage(img, "PointsInACircle.bmp");
    printf("- The more times a point is sampled, the brighter it gets.\n");
    printf("- The circle on the left contains random points with an uncorrected Uniform sampling.\n");
    printf("- The circle on the right contains random points with a corrected Uniform sampling.\n");

    free(urng);
    free(arng);
    return 0;
}
