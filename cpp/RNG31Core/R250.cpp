#include "R250.h"

using namespace RNG31;

R250::R250(int32_t seed) :
    AbstractRNGCore(seed)
{
    reseed(seed);
}

R250::~R250()
{

}

void R250::initialize()
{
    m_index = 0;

    // Fill buffer with 31-bit random values
    LinearCongruential lcrng(initialSeed());
    for(int index = 0; index < 250; ++index)
        m_buffer[index] = lcrng.next();

    uint32_t msb = 0x40000000;  // Most-Significant-Bit: To turn on the diagonal bit
    uint32_t mask = 0x7FFFFFFF; // To turn off leftmost bits
    for(int index = 0; index < 31; ++index) {
        int k = 7 * index + 3; // Select a word to operate on
        m_buffer[k] &= mask;        // Turn off bits left of the diagonal
        m_buffer[k] |= msb;         // Turn on the diagonal bit
        mask >>= 1;
        msb >>= 1;
    }

}

int32_t R250::calcNext()
{
    int index = (m_index >= 147) ? (m_index - 147) : (m_index + 103);
    int32_t newRand = m_buffer[m_index] ^= m_buffer[index];

    if(++(m_index) >= 250) /* Increment pointer for next time */
        m_index = 0;

    return newRand;
}
