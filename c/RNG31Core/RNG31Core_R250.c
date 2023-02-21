#include "RNG31Core_R250.h"

void r250_initialize(AbstractRNG31Core *rng);
int32_t r250_next(AbstractRNG31Core *rng);

AbstractRNG31Core *r250_initDefault(RNG31Core_R250 *rng)
{
    return r250_init(rng, 0);
}

AbstractRNG31Core *r250_init(RNG31Core_R250 *rng, int32_t seed)
{
    AbstractRNG31Core *result = (AbstractRNG31Core*)rng;
    rng31Core_init(result, r250_initialize, r250_next, seed);
    return result;
}

/* Not exposed in header */
void r250_initialize(AbstractRNG31Core *rng)
{
    RNG31Core_R250 *r250rng = (RNG31Core_R250*)rng;
    r250rng->index = 0;

    // Fill buffer with 31-bit random values
    RNG31Core_LinearCongruential lcrng;
    AbstractRNG31Core *arng = linearCongruential_init(&lcrng, rng31Core_initialSeed(rng));
    for(int index = 0; index < 250; ++index)
        r250rng->buffer[index] = rng31Core_next(arng);

    uint32_t msb = 0x40000000;  // Most-Significant-Bit: To turn on the diagonal bit
    uint32_t mask = 0x7FFFFFFF; // To turn off leftmost bits
    for(int index = 0; index < 31; ++index) {
        int k = 7 * index + 3; // Select a word to operate on
        r250rng->buffer[k] &= mask;        // Turn off bits left of the diagonal
        r250rng->buffer[k] |= msb;         // Turn on the diagonal bit
        mask >>= 1;
        msb >>= 1;
    }
}

int32_t r250_next(AbstractRNG31Core *rng)
{
    RNG31Core_R250 *r250rng = (RNG31Core_R250*)rng;
    int index = (r250rng->index >= 147) ? (r250rng->index - 147) : (r250rng->index + 103);
    int32_t newRand = r250rng->buffer[r250rng->index] ^= r250rng->buffer[index];

    if(++(r250rng->index) >= 250) /* Increment pointer for next time */
        r250rng->index = 0;

    return newRand;
}
