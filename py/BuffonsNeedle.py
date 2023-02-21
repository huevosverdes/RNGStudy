import sys
import math

import Utilities
from RNG31Transform.Uniform import Uniform


def throwNeedles(urng, throwCount, totalThrows, totalHits):
    for _ in range(throwCount):
        totalHits += throwNeedle(urng)
    return (totalThrows + throwCount, totalHits)


def throwNeedle(urng):
    # Does the dropped needle cross any line?
    # - Needle length: 1.0
    # - Line spacing: 1.0
    # - We don't care about the x position, it doesn't matter on an infinite plane
    # - We don't really care about y position, only y position with respect to the next line (remainder)
    y1 = urng.nextFloat(0.0, 1.0)
    rotationRadians = urng.nextFloat(2.0 * math.pi)
    y2 = math.sin(rotationRadians) + y1

    crossedLine = 0
    if y1 > y2:
        # Positive delta-y
        crossedLine = (y2 <= 0.0 and 0.0 < y1)
    else:
        # Negative delta-y
        crossedLine = (y1 <= 1.0 and 1.0 < y2)
    return crossedLine


def demo(urng):
    throwCount = 0
    hitCount = 0

    Utilities.message(4.0, "Imagine an infinite plane, with infinite parallel lines every inch.")
    Utilities.message(2.0, "If you drop an infinite number of one inch needles on the plane,")
    Utilities.message(2.0, "how many needles will land across one of the lines?")
    Utilities.message(4.0, "In other words: What is the probability that a needle will land crossing a line?")
    Utilities.message(1.0, "")

    Utilities.message(2.0, "We could do a lot of math to figure it out ...")
    Utilities.message(4.0, "or we could drop a lot of needles on some lined butcher paper ...")
    Utilities.message(1.0, "or we could just simulate a lot of needle drops with RNG.")
    Utilities.message(1.0, "")
    Utilities.message(1.0, "Let's drop a few needles ...\n")

    throwCount, hitCount = throwNeedles(urng, 10, throwCount, hitCount)
    Utilities.message(3.0, "We dropped %d needles. %d landed crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount)
    Utilities.message(1.0, "Let's drop a few more ...\n")

    throwCount, hitCount = throwNeedles(urng, 90, throwCount, hitCount)
    Utilities.message(3.0, "Now we've dropped %d needles. %d landed crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount)
    Utilities.message(1.0, "Let's keep going ...\n")

    throwCount, hitCount = throwNeedles(urng, 900, throwCount, hitCount)
    Utilities.message(3.0, "%d needles dropped with %d crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount)
    Utilities.message(1.0, "Let's keep going ...\n")

    throwCount, hitCount = throwNeedles(urng, 9000, throwCount, hitCount)
    Utilities.message(3.0, "%d needles dropped with %d crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount)
    throwCount, hitCount = throwNeedles(urng, 90000, throwCount, hitCount)
    Utilities.message(3.0, "%d needles dropped with %d crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount)
    throwCount, hitCount = throwNeedles(urng, 900000, throwCount, hitCount)
    Utilities.message(3.0, "%d needles dropped with %d crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount)

    Utilities.message(1.0, "Wait a minute ...")
    Utilities.message(1.0, "That number looks strangely familiar ...")

    value = float(hitCount) / throwCount
    Utilities.message(2.0, "Let's just talk about the ratio, not the percentage ... %0.4f", value)
    value = 1.0 / value
    Utilities.message(2.0, "Then invert it ... %0.4f", value)
    value = value * 2.0
    Utilities.message(2.0, "And multiply by 2 ... %0.4f", value)

    Utilities.message(1.0, "")
    Utilities.message(3.0, "That's right! If we drop enough needles, the probability is 2/pi!")
    Utilities.message(3.0, "We can calculate an approximation of pi just by randomly dropping needles!")
    Utilities.message(0.0, "For more information: https://en.wikipedia.org/wiki/Buffon%%27s_needle_problem.")

    print("")
    sys.stdout.flush()


def dropSingleNeedle(urng):
    y1 = urng.nextFloat()
    rotationRadians = urng.nextFloat(0.0, 2.0 * math.pi)
    y2 = math.sin(rotationRadians) + y1

    crossedLine = False
    if y1 > y2:
        # Negative delta-y
        crossedLine = (y2 <= 0.0 and 0.0 < y1)
    else:
        # Positive delta-y
        crossedLine = (y1 <= 1.0 and 1.0 < y2)

    print("You drop a one inch needle on an infinite plane with inifinite parallel lines one inch apart.");
    print("One end of the needle lands %0.3f inches from the nearest line at an angle of %0.2f degrees." % (y1, 180.0 * rotationRadians / math.pi));
    if crossedLine:
        print("This needle DOES cross a line.")
    else:
        print("This needle does NOT cross a line.")
    print("")
    sys.stdout.flush()


def dropLotsOfNeedles(urng):
    sampleCount = Utilities.getUserInt(2, 100000, "How many needles do you want to drop?")

    throwCount = 0
    hitCount = 0
    throwCount, hitCount = throwNeedles(urng, sampleCount, throwCount, hitCount)

    print("%d hits / %d drops = %0.6f%%" % (hitCount, throwCount, 100.0 * hitCount / throwCount))
    print("pi approximation: %f" % (2.0 * throwCount / hitCount,))
    print("")
    sys.stdout.flush()


if __name__ == "__main__":

    arng = Utilities.getRNGCore()
    urng = Uniform(arng)

    running = True;
    while running:
        actionCode = Utilities.getUserInt(
            1, 5,
            "Choose an action:\n" +
            "  1. Choose an RNG Core\n" +
            "  2. Give me the demo introduction to the Buffon's Needle Problem\n" +
            "  3. Drop one of Buffon's Needles for yourself\n" +
            "  4. Estimate pi by simulating a lot of needle drops\n" +
            "  5. Quit")
        if actionCode == 1:
            arng = Utilities.getRNGCore()
            urng = Uniform(arng)
        elif actionCode == 2:
            demo(urng);
        elif actionCode == 3:
            dropSingleNeedle(urng)
        elif actionCode == 4:
            dropLotsOfNeedles(urng)
        elif actionCode == 5:
            running = False

    exit(0)
