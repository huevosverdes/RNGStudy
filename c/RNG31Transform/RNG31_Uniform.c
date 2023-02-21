#include "RNG31_Uniform.h"

#include <stdio.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif /* M_PI */

void rng31Uniform_init(RNG31_Uniform *urng, AbstractRNG31Core *rng)
{
    urng->rng = rng;
    urng->coinValue = 0;
    urng->coinMask = 0;
}

int32_t rng31Uniform_next(RNG31_Uniform *urng, int32_t low, int32_t high)
{
    assert(low <= high);
    int32_t result;

    if(low != high) {
        uint32_t delta = high - low;
        uint32_t t = 0x80000000 - (0x80000000 % delta);
        do {
            result = (uint32_t)rng31Core_next(urng->rng);
        } while(t <= result);
        result = (result % delta) + low;
    } else {
        result = rng31Core_next(urng->rng);
    }

    return result;
}

double rng31Uniform_nextFloat(RNG31_Uniform *urng, double low, double high)
{
    assert(low < high);
    double v = rng31Core_next(urng->rng) / (double)0x80000000; // 2147483648
    return (v * (high - low)) + low;
}

void rng31Uniform_pointInCircle(RNG31_Uniform *urng, double radius, double *x, double *y)
{
    /* https://programming.guide/random-point-within-circle.html */
    assert(radius > 0.0);
    double angle = rng31Uniform_nextFloat(urng, 0.0, 1.0) * 2.0 * M_PI;
    double r = radius * sqrt(rng31Uniform_nextFloat(urng, 0.0, 1.0));
    *x = (r * cos(angle));
    *y = (r * sin(angle));
}

void rng31Uniform_shuffle(RNG31_Uniform *urng, void *container, int length, SwapFuncPtr swap)
{
    /* https://www.rosettacode.org/wiki/Knuth_shuffle */
    for(int index = length - 1; index > 0; --index) {
        int swapIndex = rng31Uniform_next(urng, 0, index);
        swap(container, index, swapIndex);
    }
}

int rng31Uniform_coinFlip(RNG31_Uniform *urng)
{
    if(urng->coinMask <= 0) {
        urng->coinValue = rng31Core_next(urng->rng);
        urng->coinMask = 0x80000000;
    }
    urng->coinMask >>= 1;
    return (urng->coinMask & urng->coinValue) != 0;
}
