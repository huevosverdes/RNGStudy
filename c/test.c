#include "RNG31Core/AbstractRNG31Core.h"
#include "RNG31Core/RNG31Core_GBFlip.h"
#include "RNG31Core/RNG31Core_LinearCongruential.h"
#include "RNG31Core/RNG31Core_Isaac.h"
#include "RNG31Core/RNG31Core_MersenneTwister.h"
#include "RNG31Core/RNG31Core_R250.h"
#include "RNG31Core/RNG31Core_R250_R521.h"
#include "RNG31Transform/RNG31_Uniform.h"
#include "Ease.h"

#include <stdio.h>
#include <math.h>

#define TEST_SEED -314159

int testAllRNGCores();
int testRNGCore(AbstractRNG31Core *rng, const char *label, int expectedSample1, int expectedSample135);
int testRNGUniform();
int testEasingCurves();
int testEasingCurve(const char *label, double value, double expected);

int main(int argc, char **argv)
{
    int failedTests = 0;

    failedTests += testAllRNGCores();
    failedTests += testRNGUniform();
    failedTests += testEasingCurves();

    printf("%d test%s failed\n", failedTests, failedTests == 1 ? "" : "s");
    return failedTests;
}

int testEasingCurves()
{
    int failedTests = 0;
    printf("Testing Easing Curves\n");

    const double t = 0.25;

    /* Just spot checking, not exhaustive */
    failedTests += testEasingCurve("Linear", easeLinear(t), 0.25);
    failedTests += testEasingCurve("QuadIn", easeQuadIn(t), 0.0625);
    failedTests += testEasingCurve("QuadInOut", easeQuadInOut(t), 0.125);
    failedTests += testEasingCurve("CubeInOut", easeCubeInOut(t), 0.0625);
    failedTests += testEasingCurve("QuartInOut", easeQuartInOut(t), 0.03125);
    failedTests += testEasingCurve("SinIn", easeSinIn(t), 2.0);
    failedTests += testEasingCurve("SinOut", easeSinOut(t), 1.0);
    failedTests += testEasingCurve("EaseBackInOut", easeBackInOut(t), -0.1875);
    failedTests += testEasingCurve("EaseSquare", easeSquare(t), 0.0);
    failedTests += testEasingCurve("Smoothstep", easeSmoothstep(t), 0.15625);

    if(failedTests == 0)
        printf("    SUCCESS!\n");
    printf("\n");
    return failedTests;
}

int testEasingCurve(const char *label, double value, double expected)
{
    int result = fabs(value - expected) < 0.000001 ? 0 : 1;
    if(result)
        printf("    FAILED: %s: Expected %f, Got %f\n", label, expected, value);
    return result;
}

int testRNGUniform()
{
    int failedTests = 0;
    printf("Testing Uniform RNG\n");

    RNG31Core_GBFlip gbFlip;
    AbstractRNG31Core *arng = gbFlip_init(&gbFlip, TEST_SEED);
    for(int index = 0; index < 134; ++index)
        (void)rng31Core_next(arng);
    RNG31_Uniform urng;
    rng31Uniform_init(&urng, arng);
    int sample135 = rng31Uniform_next(&urng, 0, 0x55555555);
    int expectedSample135 = 748103812;
    if(sample135 != expectedSample135) {
        printf("    FAILED: %s[%d]: Expected %d, Got %d\n", "Uniform", 135, expectedSample135, sample135);
        ++failedTests;
    }

    if(failedTests == 0)
        printf("    SUCCESS!\n");
    printf("\n");
    return failedTests;
}

int testAllRNGCores()
{
    int failedTests = 0;
    printf("Testing 31-bit RNG Cores\n");

    RNG31Core_GBFlip gbFlip;
    failedTests += testRNGCore(gbFlip_init(&gbFlip, TEST_SEED), "GBFlip", 119318998, 2081307921);

    RNG31Core_LinearCongruential linCong;
    failedTests += testRNGCore(linearCongruential_init(&linCong, TEST_SEED), "Linear Congruential", 1924356918, 437872528);

    RNG31Core_Isaac isaac;
    failedTests += testRNGCore(isaac_init(&isaac, TEST_SEED), "Isaac", 232323904, 2140087090);

    RNG31Core_MersenneTwister mt;
    failedTests += testRNGCore(mersenneTwister_init(&mt, TEST_SEED), "Mersenne Twister", 1925283223, 1908426989);

    RNG31Core_R250 r250;
    failedTests += testRNGCore(r250_init(&r250, TEST_SEED), "R250", 1467021983, 224186363);

    RNG31Core_R250_R521 r250r521;
    failedTests += testRNGCore(r250_r521_init(&r250r521, TEST_SEED), "R250/R521", 812580887, 56312995);

    if(failedTests == 0)
        printf("    SUCCESS!\n");
    printf("\n");
    return failedTests;
}

int testRNGCore(AbstractRNG31Core *rng, const char *label, int expectedSample1, int expectedSample135)
{
    int failedTests = 0;

    int sample = rng31Core_next(rng);
    if(sample != expectedSample1) {
        printf("    FAILED: %s[  %d]: Expected %d, Got %d\n", label, 1, expectedSample1, sample);
        ++failedTests;
    }

    for(int index = 0; index < 133; ++index)
        (void)rng31Core_next(rng);

    sample = rng31Core_next(rng);
    if(sample != expectedSample135) {
        printf("    FAILED: %s[%d]: Expected %d, Got %d\n", label, 135, expectedSample135, sample);
        ++failedTests;
    }

    return failedTests;
}
