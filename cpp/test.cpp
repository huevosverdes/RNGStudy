#include "RNG31Core/AbstractRNGCore.h"
#include "RNG31Core/GBFlip.h"
#include "RNG31Core/LinearCongruential.h"
#include "RNG31Core/Isaac.h"
#include "RNG31Core/MersenneTwister.h"
#include "RNG31Core/R250.h"
#include "RNG31Core/R250_R521.h"
#include "RNG31Transform/Uniform.h"
#include "Ease.h"

#include <cmath>
#include <iostream>

using namespace RNG31;

#define TEST_SEED -314159

int testAllRNGCores();
int testRNGCore(AbstractRNGCore *rng, const char *label, int expectedSample1, int expectedSample135);
int testRNGUniform();
int testEasingCurves();
int testEasingCurve(const char *label, double value, double expected);

int main(int argc, char **argv)
{
    int failedTests = 0;

    failedTests += testAllRNGCores();
    failedTests += testRNGUniform();
    failedTests += testEasingCurves();

    std::cout << failedTests << " test" << (failedTests == 1 ? "" : "s") << " failed\n" << std::endl;
    return failedTests;
}

int testEasingCurves()
{
    int failedTests = 0;
    printf("Testing Easing Curves\n");

    const double t = 0.25;

    /* Just spot checking, not exhaustive */
    failedTests += testEasingCurve("Linear", Ease::linear(t), 0.25);
    failedTests += testEasingCurve("QuadIn", Ease::quadIn(t), 0.0625);
    failedTests += testEasingCurve("QuadInOut", Ease::quadInOut(t), 0.125);
    failedTests += testEasingCurve("CubeInOut", Ease::cubeInOut(t), 0.0625);
    failedTests += testEasingCurve("QuartInOut", Ease::quartInOut(t), 0.03125);
    failedTests += testEasingCurve("SinIn", Ease::sinIn(t), 2.0);
    failedTests += testEasingCurve("SinOut", Ease::sinOut(t), 1.0);
    failedTests += testEasingCurve("EaseBackInOut", Ease::backInOut(t), -0.1875);
    failedTests += testEasingCurve("EaseSquare", Ease::square(t), 0.0);
    failedTests += testEasingCurve("Smoothstep", Ease::smoothstep(t), 0.15625);

    if(failedTests == 0)
        std::cout << "    SUCCESS!" << std::endl;
    std::cout << std::endl;
    return failedTests;
}

int testEasingCurve(const char *label, double value, double expected)
{
    int result = fabs(value - expected) < 0.000001 ? 0 : 1;
    if(result)
        std::cout << "    FAILED: " << label << ": Expected "
                  << expected << ", Got " << value << std::endl;
    return result;
}

int testRNGUniform()
{
    int failedTests = 0;
    std::cout << "Testing Uniform RNG" << std::endl;

    GBFlip gbFlip(TEST_SEED);
    for(int index = 0; index < 134; ++index)
        (void)gbFlip.next();
    Uniform urng(&gbFlip);
    int sample135 = urng.next(0, 0x55555555);
    int expectedSample135 = 748103812;
    if(sample135 != expectedSample135) {
        std::cout << "    FAILED: " << "Uniform" << "[" << 135 << "]: Expected "
                  << expectedSample135 << ", Got " << sample135 << std::endl;
        ++failedTests;
    }

    if(failedTests == 0)
        std::cout << "    SUCCESS!" << std::endl;
    std::cout << std::endl;
    return failedTests;
}

int testAllRNGCores()
{
    int failedTests = 0;
    std::cout << "Testing 31-bit RNG Cores" << std::endl;

    GBFlip gbFlip(TEST_SEED);
    failedTests += testRNGCore(&gbFlip, "GBFlip", 119318998, 2081307921);

    LinearCongruential linCong(TEST_SEED);
    failedTests += testRNGCore(&linCong, "Linear Congruential", 1924356918, 437872528);

    Isaac isaac(TEST_SEED);
    failedTests += testRNGCore(&isaac, "Isaac", 232323904, 2140087090);

    MersenneTwister mt(TEST_SEED);
    failedTests += testRNGCore(&mt, "Mersenne Twister", 1925283223, 1908426989);

    R250 r250(TEST_SEED);
    failedTests += testRNGCore(&r250, "R250", 1467021983, 224186363);

    R250_R521 r250r521(TEST_SEED);
    failedTests += testRNGCore(&r250r521, "R250/R521", 812580887, 56312995);

    if(failedTests == 0)
        std::cout << "    SUCCESS!" << std::endl;
    std::cout << std::endl;
    return failedTests;
}

int testRNGCore(AbstractRNGCore *rng, const char *label, int expectedSample1, int expectedSample135)
{
    int failedTests = 0;

    int sample = rng->next();
    if(sample != expectedSample1) {
        std::cout << "    FAILED: " << label << "[" << 1 << "]: Expected "
                  << expectedSample1 << ", Got " << sample << std::endl;
        ++failedTests;
    }

    for(int index = 0; index < 133; ++index)
        (void)rng->next();

    sample = rng->next();
    if(sample != expectedSample135) {
        std::cout << "    FAILED: " << label << "[" << 133 << "]: Expected "
                  << expectedSample135 << ", Got " << sample << std::endl;
        ++failedTests;
    }

    return failedTests;
}
