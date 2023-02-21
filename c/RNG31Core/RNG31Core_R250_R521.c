#include "RNG31Core_R250_R521.h"

void r250_r521_initialize(AbstractRNG31Core *rng);
int32_t r250_r521_next(AbstractRNG31Core *rng);

AbstractRNG31Core *r250_r521_initDefault(RNG31Core_R250_R521 *rng)
{
    return r250_r521_init(rng, 0);
}

AbstractRNG31Core *r250_r521_init(RNG31Core_R250_R521 *rng, int32_t seed)
{
    AbstractRNG31Core *result = (AbstractRNG31Core*)rng;
    rng31Core_init(result, r250_r521_initialize, r250_r521_next, seed);
    return result;
}

/******************************************************************************/
/* Not for general use                                                        */
/******************************************************************************/

void r250_r521_initialize(AbstractRNG31Core *rng)
{
    RNG31Core_R250_R521 *r250r521rng = (RNG31Core_R250_R521*)rng;
    r250r521rng->index250 = 0;
    r250r521rng->index521 = 0;

    // Fill buffer with 31-bit random values
    RNG31Core_LinearCongruential lcrng;
    AbstractRNG31Core *arng = linearCongruential_init(&lcrng, rng31Core_initialSeed(rng));
    for(int index = 0; index < 250; ++index)
        r250r521rng->buffer250[index] = rng31Core_next(arng);
    for(int index = 0; index < 521; ++index)
        r250r521rng->buffer521[index] = rng31Core_next(arng);

    uint32_t msb = 0x40000000;  // Most-Significant-Bit: To turn on the diagonal bit
    uint32_t mask = 0x7FFFFFFF; // To turn off leftmost bits
    for(int index = 0; index < 31; ++index) {
        int k = 7 * index + 3;        // Select a word to operate on
        r250r521rng->buffer250[k] &= mask; // Turn off bits left of the diagonal
        r250r521rng->buffer250[k] |= msb;  // Turn on the diagonal bit

        k = 13 * index + 3;                // Select a word to operate on
        r250r521rng->buffer521[k] &= mask; // Turn off bits left of the diagonal
        r250r521rng->buffer521[k] |= msb;  // Turn on the diagonal bit

        mask >>= 1;
        msb >>= 1;
    }
}

int32_t r250_r521_next(AbstractRNG31Core *rng)
{
    RNG31Core_R250_R521 *r250r521rng = (RNG31Core_R250_R521*)rng;

    int index = (r250r521rng->index250 >= 147) ? (r250r521rng->index250 - 147) : (r250r521rng->index250 + 103);
    int32_t newRand250 = r250r521rng->buffer250[r250r521rng->index250] ^= r250r521rng->buffer250[index];

    if(++(r250r521rng->index250) >= 250) /* Increment pointer for next time */
        r250r521rng->index250 = 0;

    index = (r250r521rng->index521 >= 353) ? (r250r521rng->index521 - 353) : (r250r521rng->index521 + 168);
    int32_t newRand521 = r250r521rng->buffer521[r250r521rng->index521] ^= r250r521rng->buffer521[index];

    if(++(r250r521rng->index521) >= 521) /* Increment pointer for next time */
        r250r521rng->index521 = 0;

    return newRand250 ^ newRand521;
}
