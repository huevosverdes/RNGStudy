#include "RNG31Core_MersenneTwister.h"

void mersenneTwister_initialize(AbstractRNG31Core *rng);
int32_t mersenneTwister_next(AbstractRNG31Core *rng);

AbstractRNG31Core *mersenneTwister_initDefault(RNG31Core_MersenneTwister *rng)
{
    return mersenneTwister_init(rng, 0);
}

AbstractRNG31Core *mersenneTwister_init(RNG31Core_MersenneTwister *rng, int32_t seed)
{
    AbstractRNG31Core *result = (AbstractRNG31Core*)rng;
    rng31Core_init(result, mersenneTwister_initialize, mersenneTwister_next, seed);
    return result;
}

/* Not exposed in header */

// MT19937
#define MT_W 32         // W: word size (in number of bits)
#define MT_N 624        // N: degree of recurrence
#define MT_M 397        // M: middle word, offset for recurrence relation defining series [1, n)
#define MT_R 31         // R: number of bits of lower bitmask, [0, w)
#define MT_A 0x9908B0DF // A: coefficients of rational normal form twist matrix
#define MT_U 11         // U, d, l: additional Mersenne Twister tempering bit shifts/masks
#define MT_D 0xFFFFFFFF
#define MT_S 7          // S, t: TGFSR(R) tempering bit shifts
#define MT_B 0x9D2C5680 // B, c: TGFSR(R) tempering bitmasks
#define MT_T 15
#define MT_C 0xEFC60000
#define MT_L 18
#define MT_F 0x6C078965 // F: initialization parameter
#define MT_LOWER_MASK 0x7FFFFFFF // (1 << R) - 1
#define MT_UPPER_MASK 0x80000000 // lowest W bits of ~LOWER_MASK

void mersenneTwister_twist(RNG31Core_MersenneTwister* mt)
{
    for(uint32_t index = 0; index < MT_N; ++index) {
        uint32_t x = ((mt->buffer[index] & MT_UPPER_MASK) + (mt->buffer[(index + 1) % MT_N] & MT_LOWER_MASK));
        uint32_t xA = x >> 1;
        if(x & 0x1)
            xA ^= MT_A;
        mt->buffer[index] = mt->buffer[(index + MT_M) % MT_N] ^ xA;
    }
    mt->index = 0;
}

void mersenneTwister_initialize(AbstractRNG31Core *rng)
{
    RNG31Core_MersenneTwister *mt = (RNG31Core_MersenneTwister*)rng;

    mt->index = MT_N;
    uint32_t value = mt->buffer[0] = rng->initialSeed;
    for(uint32_t index = 1; index < MT_N; ++index)
        value = mt->buffer[index] = MT_F * (value ^ ((value >> (MT_W - 2)))) + index;
}

int32_t mersenneTwister_next(AbstractRNG31Core *rng)
{
    RNG31Core_MersenneTwister *mt = (RNG31Core_MersenneTwister*)rng;

    if(mt->index >= MT_N)
        mersenneTwister_twist(mt);

    uint32_t y = mt->buffer[mt->index++];
    y ^= (y >> MT_U) & MT_D;
    y ^= (y << MT_S) & MT_B;
    y ^= (y << MT_T) & MT_C;
    y ^= (y >> MT_L);

    return (MT_LOWER_MASK & y); // Only 31 bits
}
