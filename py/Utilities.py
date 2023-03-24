import sys
import time

from RNG31Core.GBFlip import GBFlip
from RNG31Core.LinearCongruential import LinearCongruential
from RNG31Core.R250 import R250
from RNG31Core.R250_R521 import R250_R521
from RNG31Core.MersenneTwister import MersenneTwister
from RNG31Core.Isaac import Isaac

from BMPWriter import BMPWriter


def getUserInt(low, high, prompt, *args):
    result = 0
    while True:
        print(prompt % args)
        text = input("> ")
        try:
            index = int(text)
            if low <= index and index <= high:
                result = index
                break
        except ValueError:
            pass

        print("That was either not an integer or not between %d-%d. Try again.\n" % (low, high))

    assert(low <= result and result <= high)
    print("")
    sys.stdout.flush()
    return result


def getRNGCore():
    rngCoreIndex = getUserInt(
        1, 6,
        "Choose an RNG engine:\n"
        "  1. GBFlip\n"
        "  2. Linear Congruential\n"
        "  3. Isaac\n"
        "  4. Mersenne Twister\n"
        "  5. R250\n"
        "  6. R250/R521")

    if rngCoreIndex == 1:
        return GBFlip()
    elif rngCoreIndex == 2:
        return LinearCongruential()
    elif rngCoreIndex == 3:
        return Isaac()
    elif rngCoreIndex == 4:
        return MersenneTwister()
    elif rngCoreIndex == 5:
        return R250()
    elif rngCoreIndex == 6:
        return R250_R521()

    return None


def message(timeout, msg, *args):
    print(msg % args)
    sys.stdout.flush()
    time.sleep(timeout)


def addSamplePoint(img, x, y):
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


def writeBMPImage(img, fileNameFormat, *args):
    fileName = fileNameFormat % args

    BMPWriter.write(fileName, img)
    print("Wrote File: %s" % (fileName,))
