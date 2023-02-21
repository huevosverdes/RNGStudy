#include <cstdio>

#include "Utilities.h"
#include "RNG31Core/AbstractRNGCore.h"
#include "RNG31Transform/Uniform.h"

void throwNeedles(RNG31::Uniform *urng, int throwCount, int *totalThrows, int *totalHits);
bool throwNeedle(RNG31::Uniform *urng);

void demo(RNG31::Uniform *urng);
void dropSingleNeedle(RNG31::Uniform *urng);
void dropLotsOfNeedles(RNG31::Uniform *urng);

int main(int argc, char **argv)
{
    RNG31::AbstractRNGCore *arng = getRNGCore();
    RNG31::Uniform *urng = new RNG31::Uniform(arng);

    int running = 1;
    do {
        int actionCode = getUserInt(
            1, 5,
            "Choose an action:\n"
            "  1. Choose an RNG Core\n"
            "  2. Give me the demo introduction to the Buffon's Needle Problem\n"
            "  3. Drop one of Buffon's Needles for yourself\n"
            "  4. Estimate pi by simulating a lot of needle drops\n"
            "  5. Quit");
        switch(actionCode) {
        case 1:
            delete urng;
            delete arng;
            arng = getRNGCore();
            urng = new RNG31::Uniform(arng);
            break;
        case 2:
            demo(urng);
            break;
        case 3:
            dropSingleNeedle(urng);
            break;
        case 4:
            dropLotsOfNeedles(urng);
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

void throwNeedles(RNG31::Uniform *urng, int throwCount, int *totalThrows, int *totalHits)
{
    for(int count = 0; count < throwCount; ++count)
        if(throwNeedle(urng))
            ++(*totalHits);
    (*totalThrows) += throwCount;
}

bool throwNeedle(RNG31::Uniform *urng)
{
    // Does the dropped needle cross any line?
    // - Needle length: 1.0
    // - Line spacing: 1.0
    // - We don't care about the x position, it doesn't matter on an infinite plane
    // - We don't really care about y position, only y position with respect to the next line (remainder)
    double y1 = urng->nextFloat();
    double rotationRadians = urng->nextFloat(2.0 * M_PI);
    double y2 = sin(rotationRadians) + y1;

    bool crossedLine = false;
    if(y1 > y2)
        // Positive delta-y
        crossedLine = (y2 <= 0.0 && 0.0 < y1);
    else
        // Negative delta-y
        crossedLine = (y1 <= 1.0 && 1.0 < y2);
    return crossedLine;
}

void demo(RNG31::Uniform *urng)
{
    int throwCount = 0;
    int hitCount = 0;

    message(4.0, "Imagine an infinite plane, with infinite parallel lines every inch.");
    message(2.0, "If you drop an infinite number of one inch needles on the plane,");
    message(2.0, "how many needles will land across one of the lines?");
    message(4.0, "In other words: What is the probability that a needle will land crossing a line?");
    message(1.0, "");

    message(2.0, "We could do a lot of math to figure it out ...");
    message(4.0, "or we could drop a lot of needles on some lined butcher paper ...");
    message(1.0, "or we could just simulate a lot of needle drops with RNG.");
    message(1.0, "");
    message(1.0, "Let's drop a few needles ...\n");

    throwNeedles(urng, 10, &throwCount, &hitCount);
    message(3.0, "We dropped %d needles. %d landed crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount);
    message(1.0, "Let's drop a few more ...\n");

    throwNeedles(urng, 90, &throwCount, &hitCount);
    message(3.0, "Now we've dropped %d needles. %d landed crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount);
    message(1.0, "Let's keep going ...\n");

    throwNeedles(urng, 900, &throwCount, &hitCount);
    message(3.0, "%d needles dropped with %d crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount);
    message(1.0, "Let's keep going ...\n");

    throwNeedles(urng, 9000, &throwCount, &hitCount);
    message(3.0, "%d needles dropped with %d crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount);
    throwNeedles(urng, 90000, &throwCount, &hitCount);
    message(3.0, "%d needles dropped with %d crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount);
    throwNeedles(urng, 900000, &throwCount, &hitCount);
    message(3.0, "%d needles dropped with %d crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount);
    throwNeedles(urng, 9000000, &throwCount, &hitCount);
    message(3.0, "%d needles dropped with %d crossing a line. The probability is %0.4f%%.", throwCount, hitCount, 100.0 * hitCount / throwCount);

    message(1.0, "Wait a minute ...");
    message(1.0, "That number looks strangely familiar ...");

    double value = (double)hitCount / throwCount;
    message(2.0, "Let's just talk about the ratio, not the percentage ... %0.4f", value);
    value = 1.0 / value;
    message(2.0, "Then invert it ... %0.4f", value);
    value = value * 2.0;
    message(2.0, "And multiply by 2 ... %0.4f", value);

    message(1.0, "");
    message(3.0, "That's right! If we drop enough needles, the probability is 2/pi!");
    message(3.0, "We can calculate an approximation of pi just by randomly dropping needles!");
    message(0.0, "For more information: https://en.wikipedia.org/wiki/Buffon%%27s_needle_problem.\n");
}

void dropSingleNeedle(RNG31::Uniform *urng)
{
    double y1 = urng->nextFloat();
    double rotationRadians = urng->nextFloat(0.0, 2.0 * M_PI);
    double y2 = sin(rotationRadians) + y1;

    int crossedLine = 0;
    if(y1 > y2)
        /* Negative delta-y */
        crossedLine = (y2 <= 0.0 && 0.0 < y1) ? 1 : 0;
    else
        /* Positive delta-y */
        crossedLine = (y1 <= 1.0 && 1.0 < y2) ? 1 : 0;

    printf("You drop a one inch needle on an infinite plane with inifinite parallel lines one inch apart.\n");
    printf("One end of the needle lands %0.3f inches from the nearest line at an angle of %0.2f degrees.\n", y1, 180.0 * rotationRadians / M_PI);
    if(crossedLine)
        printf("This needle DOES cross a line.\n");
    else
        printf("This needle does NOT cross a line.\n");
    printf("\n");
    fflush(stdout);
}

void dropLotsOfNeedles(RNG31::Uniform *urng)
{
    int sampleCount = getUserInt(2, 1000000, "How many needles do you want to drop?");

    int throwCount = 0;
    int hitCount = 0;
    throwNeedles(urng, sampleCount, &throwCount, &hitCount);

    printf("%d hits / %d drops = %0.6f%%\n", hitCount, throwCount, 100.0 * hitCount / throwCount);
    printf("pi approximation: %f\n", 2.0 * throwCount / hitCount);
    printf("\n");
    fflush(stdout);
}
