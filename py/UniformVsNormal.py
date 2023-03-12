from BMPWriter import BMPWriter
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


def addPoint(img, x, y):
    STEP = 50
    MAX  = 255 - STEP

    c = img.at(y, x)

    if c.blu() <= MAX:
        c.setBlu(c.blu() + STEP)
    elif c.grn() <= MAX:
        c.setGrn(c.grn() + STEP)
    elif c.red() <= MAX:
        c.setRed(c.red() + STEP)
    else:
        c.set(0xFF, 0xFF, 0xFF)

    img.set(y, x, c)


def drawBox(img, x, y, w, h, c):
    for count in range(w+1):
        img.set(y    , x + count, c)
        img.set(y + h, x + count, c)
    for count in range(1, h):
        img.set(y + count, x    , c)
        img.set(y + count, x + w, c)


def writeImage(img, prefix):
    fName = "%s.bmp" % (prefix,)

    BMPWriter.write(fName, img)
    print("Wrote File: %s" % (fName,))
    print("- The more times a point is sampled, the brighter it gets.");
    print("- The box on the left contains random points with a Uniform sampling.");
    print("- The box on the right contains random points with a Gaussian sampling within 4 standard deviations of the center.\n");


if __name__ == "__main__":
    img = Image(WIDTH, HEIGHT)
    img.fill(Color.BLK)

    arng = Utilities.getRNGCore()
    urng = Uniform(arng)
    nrng = Normal(arng)

    borderColor = Color(0x88, 0x88, 0x88)
    drawBox(img,
            int(RECT_UNIFORM_X-1), int(RECT_UNIFORM_Y-1),
            int(RECT_UNIFORM_W+2), int(RECT_UNIFORM_H+2),
            borderColor)
    drawBox(img,
            int(RECT_NORMAL_X -1), int(RECT_NORMAL_Y -1),
            int(RECT_NORMAL_W +2), int(RECT_NORMAL_H +2),
            borderColor)

    for _ in range(1000000):
        x = urng.next(RECT_UNIFORM_W+1)
        y = urng.next(RECT_UNIFORM_H+1)
        addPoint(img, int(x + RECT_UNIFORM_X), int(y + RECT_UNIFORM_Y))

    count = 0
    while count < 500000:
        STD_DEV_X = RECT_NORMAL_W / 8
        MEAN_X = RECT_NORMAL_W / 2
        STD_DEV_Y = RECT_NORMAL_H / 8
        MEAN_Y = RECT_NORMAL_H / 2

        x = int(nrng.next(STD_DEV_X, MEAN_X))
        y = int(nrng.next(STD_DEV_Y, MEAN_Y))
        if ((0 <= x and x < RECT_NORMAL_W) and
            (0 <= y and y < RECT_NORMAL_H)):
            # Accept point: within 4 standard deviations from mean
            addPoint(img, int(x + RECT_NORMAL_X), int(y + RECT_NORMAL_Y))
            count += 1

    writeImage(img, "UniformVsNormal")

    exit(0)
