from RNG31Core.GBFlip import GBFlip
from RNG31Core.LinearCongruential import LinearCongruential
from RNG31Core.R250 import R250
from RNG31Core.R250_R521 import R250_R521
from RNG31Core.MersenneTwister import MersenneTwister
from RNG31Core.Isaac import Isaac
from RNG31Transform.Uniform import Uniform

from Ease import Ease


def testEasingCurve(label, value, expected):
    result = 0 if abs(value - expected) < 0.000001 else 1
    if result:
        print("    FAILED: %s: Expected %f, Got %f" % (label, expected, value))
    return result


def testEasingCurves():
    failedTests = 0
    print("Testing Easing Curves")

    t = 0.25

    # Just spot checking, not exhaustive
    failedTests += testEasingCurve("Linear", Ease.linear(t), 0.25)
    failedTests += testEasingCurve("QuadIn", Ease.quadIn(t), 0.0625)
    failedTests += testEasingCurve("QuadInOut", Ease.quadInOut(t), 0.125)
    failedTests += testEasingCurve("CubeInOut", Ease.cubeInOut(t), 0.0625)
    failedTests += testEasingCurve("QuartInOut", Ease.quartInOut(t), 0.03125)
    failedTests += testEasingCurve("SinIn", Ease.sinIn(t), 2.0)
    failedTests += testEasingCurve("SinOut", Ease.sinOut(t), 1.0)
    failedTests += testEasingCurve("EaseBackInOut", Ease.backInOut(t), -0.1875)
    failedTests += testEasingCurve("EaseSquare", Ease.square(t), 0.0)
    failedTests += testEasingCurve("Smoothstep", Ease.smoothstep(t), 0.15625)

    if failedTests == 0:
        print("    SUCCESS!")
    print("")
    return failedTests


def testRNGCore(rng, label, expectedSample1, expectedSample135):
    failedTests = 0

    sample = rng.next()
    if sample != expectedSample1:
        print("    FAILED: %s[  %d]: Expected %d, Got %d\n" % (label, 1, expectedSample1, sample))
        failedTests += 1

    for index in range(133):
        _ = rng.next()

    sample = rng.next()
    if(sample != expectedSample135):
        print("    FAILED: %s[%d]: Expected %d, Got %d\n" % (label, 135, expectedSample135, sample))
        failedTests += 1

    return failedTests


def testUniform():
    failedTests = 0
    print("Testing Uniform RNG");

    gbFlip = GBFlip(TEST_SEED)
    for _ in range(134):
        _ = gbFlip.next()
    urng = Uniform(gbFlip)
    sample135 = urng.next(0, 0x55555555)
    expectedSample135 = 748103812
    if sample135 != expectedSample135:
        print("    FAILED: %s[%d]: Expected %d, Got %d\n" % ("Uniform", 135, expectedSample135, sample135))
        failedTests += 1

    if failedTests == 0:
        print("    SUCCESS!")
    print("")
    return failedTests


def testAllRNGCores():
    failedTests = 0
    print("Testing 31-bit RNG Cores")

    gbFlip = GBFlip(TEST_SEED)
    failedTests += testRNGCore(gbFlip, "GBFlip", 119318998, 2081307921)

    linCong = LinearCongruential(TEST_SEED)
    failedTests += testRNGCore(linCong, "Linear Congruential", 1924356918, 437872528)

    isaac = Isaac(TEST_SEED)
    failedTests += testRNGCore(isaac, "Isaac", 232323904, 2140087090)

    mt = MersenneTwister(TEST_SEED)
    failedTests += testRNGCore(mt, "Mersenne Twister", 1925283223, 1908426989)

    r250 = R250(TEST_SEED)
    failedTests += testRNGCore(r250, "R250", 1467021983, 224186363)

    r250r521 = R250_R521(TEST_SEED)
    failedTests += testRNGCore(r250r521, "R250/R521", 812580887, 56312995)

    if failedTests == 0:
        print("    SUCCESS!")
    print("")
    return failedTests


if __name__ == "__main__":
    # Normally I would test with doctest, but for consistency with the C/C++ versions
    # I'm doing this testing in accordance with that

    TEST_SEED = -314159
    failedTests = 0

    failedTests += testAllRNGCores()
    failedTests += testUniform()
    failedTests += testEasingCurves()

    print("%d test%s failed" % (failedTests, "" if failedTests == 1 else "s"))
    exit(failedTests)
