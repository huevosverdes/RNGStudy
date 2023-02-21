#include "RNG31Core_LinearCongruential.h"

void linearCongruential_initialize(AbstractRNG31Core *rng);
int32_t linearCongruential_next(AbstractRNG31Core *rng);

AbstractRNG31Core *linearCongruential_initDefault(RNG31Core_LinearCongruential *rng)
{
    return linearCongruential_init(rng, 0);
}

AbstractRNG31Core *linearCongruential_init(RNG31Core_LinearCongruential *rng, int32_t seed)
{
    rng->value = seed;
    AbstractRNG31Core *result = (AbstractRNG31Core*)rng;
    rng31Core_init(result, linearCongruential_initialize, linearCongruential_next, seed);
    return result;
}

/* Not exposed in header */

/* Increment */
#define LINEAR_CONG_A 1103515245

/* Multiplier */
#define LINEAR_CONG_C 12345

/* Modulus */
#define LINEAR_CONG_M 0x80000000

void linearCongruential_initialize(AbstractRNG31Core *rng)
{
    ((RNG31Core_LinearCongruential*)rng)->value = rng->initialSeed;
}

int32_t linearCongruential_next(AbstractRNG31Core *rng)
{
    RNG31Core_LinearCongruential *lcrng = (RNG31Core_LinearCongruential*)rng;
    lcrng->value = (LINEAR_CONG_A * lcrng->value + LINEAR_CONG_C) % LINEAR_CONG_M;
    return lcrng->value;
}
