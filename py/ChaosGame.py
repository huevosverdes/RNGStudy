# https://en.wikipedia.org/wiki/Chaos_game
# https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle#Chaos_game

import math

from BMPWriter import BMPWriter
from Image import Image
from Color import Color

import Utilities
from NoiseBuffer2D import NoiseBuffer2D
from RNG31Transform.Uniform import Uniform
from RNG31Transform.Perlin import Perlin

# Image Properties
WIDTH  = 800
HEIGHT = 800

class ColorMethod:
    SOLID = 0
    XY    = 1
    ANGLE = 2
    NOISE = 3

colorMethod = ColorMethod.NOISE
bluNoise = NoiseBuffer2D(WIDTH, HEIGHT)
grnNoise = NoiseBuffer2D(WIDTH, HEIGHT)

# Attractor Points
X1 = 5.0
Y1 = HEIGHT - 5.0
X2 = WIDTH - 5.0
Y2 = Y1
X3 = (X1 + X2) / 2.0
Y3 = Y1 - (math.sqrt(3.0) / 2.0) * (HEIGHT - 10.0)

XCenter = X3
YCenter = (Y3 + Y1) / 2.0

def colorAtPoint(x, y, method):
    global bluNoise
    global grnNoise

    red, grn, blu = 0.0, 0.0, 0.0

    if method == ColorMethod.SOLID:
        red = 0.15
        grn = 0.25
        blu = 0.75
    elif method == ColorMethod.XY:
        red = 0.0
        grn = float(x) / WIDTH
        blu = float(y) / HEIGHT
    elif method == ColorMethod.ANGLE:
        vecCenterX = x - XCenter
        vecCenterY = y - YCenter
        pRadius = math.sqrt(vecCenterX*vecCenterX + vecCenterY*vecCenterY)

        vecGrnX = X1 - XCenter
        vecGrnY = Y1 - YCenter
        triRadius = math.sqrt(vecGrnX*vecGrnX + vecGrnY*vecGrnY)
        angleGrn = math.acos((vecCenterX * vecGrnX + vecCenterY * vecGrnY) / (triRadius * pRadius)) * 180.0 / math.pi
        grn = ((120.0 - angleGrn) / 120.0) if (angleGrn <= 120.0) else 0.0

        vecBluX = X2 - XCenter
        vecBluY = Y2 - YCenter
        angleBlu = math.acos((vecCenterX * vecBluX + vecCenterY * vecBluY) / (triRadius * pRadius)) * 180.0 / math.pi
        blu = ((120.0 - angleBlu) / 120.0) if (angleBlu <= 120.0) else 0.0

        vecRedX = X3 - XCenter
        vecRedY = Y3 - YCenter
        angleRed = math.acos((vecCenterX * vecRedX + vecCenterY * vecRedY) / (triRadius * pRadius)) * 180.0 / math.pi
        red = ((120.0 - angleRed) / 120.0) if (angleRed <= 120.0) else 0.0
    elif method == ColorMethod.NOISE:
        red = 0.0
        blu = bluNoise.at(int(x), int(y))
        grn = grnNoise.at(int(x), int(y))

    c = Color()
    c.setF(red, grn, blu)
    return c

def addPoints(count, urng, img, lastX, lastY, sampleCount):
    global colorMethod

    for index in range(count):
        nextX, nextY = 0.0, 0.0
        targetPoint = urng.next(1, 4)

        if targetPoint == 1:
            nextX = X1
            nextY = Y1
        elif targetPoint == 2:
            nextX = X2
            nextY = Y2
        elif targetPoint == 3:
            nextX = X3
            nextY = Y3

        nextX += lastX
        nextY += lastY
        nextX /= 2.0
        nextY /= 2.0

        img.set(int(nextY), int(nextX), colorAtPoint(int(nextX), int(nextY), colorMethod))

        lastX = nextX
        lastY = nextY

    return lastX, lastY, sampleCount + count

def clearGame(urng, img):
    global colorMethod
    global bluNoise
    global grnNoise

    # Set Initial Values
    img.fill(Color.BLK)

    lastX = urng.next(0, WIDTH)
    lastY = urng.next(0, HEIGHT)
    print("The game has been reset. Starting at (%d, %d)." % (lastX, lastY))

    # Do color things
    colorMethod = Utilities.getUserInt(
        ColorMethod.SOLID,
        ColorMethod.NOISE + 1,
        "How would you like to color the results?\n" +
        "  1. Solid\n" +
        "  2. X-Y Gradient\n" +
        "  3. Angular Gradient\n" +
        "  4. Perlin Noise") - 1

    if colorMethod == ColorMethod.NOISE:
        perlin = Perlin(urng)
        perlin.shuffle()

        perlin.fill(bluNoise, 4.0, 4.0)
        bluNoise *= 0.5
        bluNoise += 0.5

        perlin.fill(grnNoise, 16.0, 16.0)

    # Draw Initial Point
    img.set(int(lastY), int(lastX), colorAtPoint(int(lastY), int(lastX), colorMethod))

    return lastX, lastY, 0


def playGame(urng, img, lastX, lastY, sampleCount):
    count = Utilities.getUserInt(1, 1000000, "How many points would you like to add?")
    lastX, lastY, sampleCount = addPoints(count, urng, img, lastX, lastY, sampleCount)
    Utilities.writeBMPImage(img, "ChaosGame_%07d.bmp", sampleCount)
    return lastX, lastY, sampleCount


def demo(urng, img, lastX, lastY, sampleCount):
    if sampleCount != 0:
        lastX, lastY, sampleCount = clearGame(urng, img, lastX, lastY, sampleCount)

    Utilities.message(2.0, "Let's play a chaotic game.")
    Utilities.message(3.0, "We begin with the three corners of a triangle: { (%d, %d), (%d, %d), (%d, %d) }",
                       int(X1), int(Y1),
                       int(X2), int(Y2),
                       int(X3), int(Y3))
    Utilities.message(3.0, "Then we start at a random point: (%d, %d)", int(lastX), int(lastY))

    nextX, nextY = 0.0, 0.0
    targetPoint = urng.next(1, 4)
    if targetPoint == 1:
        nextX = X1
        nextY = Y1
    elif targetPoint == 2:
        nextX = X2
        nextY = Y2
    elif targetPoint == 3:
        nextX = X3
        nextY = Y3
    Utilities.message(3.0, "Each step we pick one of the corners of the triangle at random: Corner #%d (%d, %d).", targetPoint, nextX, nextY)

    nextX += lastX
    nextY += lastY
    nextX /= 2.0
    nextY /= 2.0
    img.set(int(nextY), int(nextX), colorAtPoint(int(nextX), int(nextY), colorMethod))
    lastX = nextX
    lastY = nextY
    sampleCount += 1
    Utilities.message(4.0, "Then we move to the point halfway between our current point and the randomly selected corner: (%d, %d)", nextX, nextY)
    Utilities.writeBMPImage(img, "Demo_ChaosGame_%07d.bmp", sampleCount)

    lastX, lastY, sampleCount = addPoints(9, urng, img, lastX, lastY, sampleCount)
    Utilities.message(4.0, "Let's do that a few more times ending at (%d, %d) after Move #%d.", nextX, nextY, sampleCount)
    Utilities.writeBMPImage(img, "Demo_ChaosGame_%07d.bmp", sampleCount)

    lastX, lastY, sampleCount = addPoints(90, urng, img, lastX, lastY, sampleCount)
    Utilities.message(2.0, "A few more ending at (%d, %d) after Move #%d.", nextX, nextY, sampleCount)
    Utilities.writeBMPImage(img, "Demo_ChaosGame_%07d.bmp", sampleCount)

    lastX, lastY, sampleCount = addPoints(900, urng, img, lastX, lastY, sampleCount)
    Utilities.message(2.0, "Keep going to (%d, %d) after Move #%d.", nextX, nextY, sampleCount)
    Utilities.writeBMPImage(img, "Demo_ChaosGame_%07d.bmp", sampleCount)

    lastX, lastY, sampleCount = addPoints(9000, urng, img, lastX, lastY, sampleCount)
    Utilities.message(2.0, "Keep going to (%d, %d) after Move #%d.", nextX, nextY, sampleCount)
    Utilities.writeBMPImage(img, "Demo_ChaosGame_%07d.bmp", sampleCount)

    lastX, lastY, sampleCount = addPoints(90000, urng, img, lastX, lastY, sampleCount)
    Utilities.message(2.0, "Keep going to (%d, %d) after Move #%d.", nextX, nextY, sampleCount)
    Utilities.writeBMPImage(img, "Demo_ChaosGame_%07d.bmp", sampleCount)

    Utilities.message(3.0, "If you look at the pictures you can see that no matter where we start,")
    Utilities.message(3.0, "we always get pulled into a pattern called the Sierpinski Triangle.")
    Utilities.message(3.0, "You might notice points where they shouldn't belong.")
    Utilities.message(3.0, "Those happen at the beginning, before we get pulled into the fractal drawing pattern.")
    Utilities.message(3.0, "The Sierpinski Triangle is a fractal, and we drew it with randomness!\n")

    Utilities.message(0.0, "For more information: https://en.wikipedia.org/wiki/Sierpi%%C5%%84ski_triangle#Chaos_game.\n")

    return clearGame(urng, img)


if __name__ == "__main__":
    img = Image(WIDTH, HEIGHT)
    img.fill(Color.BLK)

    arng = Utilities.getRNGCore()
    urng = Uniform(arng)

    lastX, lastY, sampleCount = clearGame(urng, img)
    running = True
    while running:
        actionCode = Utilities.getUserInt(
            1, 5,
            "Choose an action:\n" +
            "  1. Choose an RNG Core\n" +
            "  2. Give me the demo introduction to the Chaos Game\n" +
            "  3. Reset the current Chaos Game\n" +
            "  4. Simulate multiple rounds of the Chaos Game\n" +
            "  5. Quit")
        if actionCode == 1:
            arng = Utilities.getRNGCore()
            urng = Uniform(arng)
        elif actionCode == 2:
            lastX, lastY, sampleCount = demo(urng, img, lastX, lastY, sampleCount)
        elif actionCode == 3:
            lastX, lastY, sampleCount = clearGame(urng, img)
        elif actionCode == 4:
            lastX, lastY, sampleCount = playGame(urng, img, lastX, lastY, sampleCount)
        elif actionCode == 5:
            running = False

    exit(0)
