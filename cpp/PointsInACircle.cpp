#include <cstdio>
#include <cmath>

#include "Utilities.h"
#include "RNG31Core/AbstractRNGCore.h"
#include "RNG31Transform/Uniform.h"

#include "Image.h"
#include "Color.h"

// Image Properties
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
    RNG31::AbstractRNGCore *arng = getRNGCore();
    RNG31::Uniform urng(arng);

    Image img(WIDTH, HEIGHT);
    img.fill(Color::BLK);

    const int ITERATIONS = 450000;
    for(int index = 0; index < ITERATIONS; ++index) {
        double radius = urng.nextFloat(RADIUS);
        double radians = urng.nextFloat(2.0 * M_PI);
        double x = radius * cos(radians) + CENTER_UNCORRECTED_X;
        double y = radius * sin(radians) + CENTER_UNCORRECTED_Y;
        addSamplePoint(&img, (int)x, (int)y);
    }

    for(int index = 0; index < ITERATIONS; ++index) {
        double x, y;
        urng.pointInCircle(RADIUS, x, y);
        x += CENTER_CORRECTED_X;
        y += CENTER_CORRECTED_Y;
        addSamplePoint(&img, (int)x, (int)y);
    }

    writeBMPImage(&img, (char*)"PointsInACircle.bmp");
    printf("- The more times a point is sampled, the brighter it gets.\n");
    printf("- The circle on the left contains random points with an uncorrected Uniform sampling.\n");
    printf("- The circle on the right contains random points with a corrected Uniform sampling.\n");

    delete arng;
    return 0;
}
