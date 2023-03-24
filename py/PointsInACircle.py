import math

from Image import Image
from Color import Color

import Utilities
from RNG31Transform.Uniform import Uniform
from RNG31Transform.Normal import Normal

WIDTH    = 1024
HEIGHT   =  620
MARGIN   =   10
BOX_SIZE =  (WIDTH - (3.0 * MARGIN)) / 2.0

RECT_UNIFORM_X = MARGIN
RECT_UNIFORM_Y = (HEIGHT - BOX_SIZE) / 2
RECT_UNIFORM_W = BOX_SIZE
RECT_UNIFORM_H = BOX_SIZE

RECT_NORMAL_X = MARGIN + MARGIN + BOX_SIZE
RECT_NORMAL_Y = (HEIGHT - BOX_SIZE) / 2
RECT_NORMAL_W = BOX_SIZE
RECT_NORMAL_H = BOX_SIZE

WIDTH    = 1024
HEIGHT   =  620
MARGIN   =   10
DIAMETER =  (WIDTH - (3.0 * MARGIN)) / 2.0

RADIUS = DIAMETER / 2.0
CENTER_UNCORRECTED_X = MARGIN + RADIUS
CENTER_UNCORRECTED_Y = HEIGHT / 2.0
CENTER_CORRECTED_X = MARGIN + MARGIN + DIAMETER + RADIUS
CENTER_CORRECTED_Y = CENTER_UNCORRECTED_Y


if __name__ == "__main__":
    img = Image(WIDTH, HEIGHT)
    img.fill(Color.BLK)

    arng = Utilities.getRNGCore()
    urng = Uniform(arng)
    nrng = Normal(arng)

    ITERATIONS = 250000
    for _ in range(ITERATIONS):
        radius = urng.nextFloat(RADIUS)
        radians = urng.nextFloat(2.0 * math.pi)
        x = radius * math.cos(radians) + CENTER_UNCORRECTED_X
        y = radius * math.sin(radians) + CENTER_UNCORRECTED_Y
        Utilities.addSamplePoint(img, int(x), int(y))

    for _ in range(ITERATIONS):
        x, y = urng.pointInCircle(RADIUS)
        x += CENTER_CORRECTED_X
        y += CENTER_CORRECTED_Y
        Utilities.addSamplePoint(img, int(x), int(y))

    Utilities.writeBMPImage(img, "PointsInACircle.bmp")
    print("- The more times a point is sampled, the brighter it gets.");
    print("- The circle on the left contains random points with an uncorrected Uniform sampling.");
    print("- The circle on the right contains random points with a corrected Uniform sampling.");

    exit(0)
