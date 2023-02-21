#include "R250_R521.h"

using namespace RNG31;

R250_R521::R250_R521(int32_t seed) :
    AbstractRNGCore(seed)
{
    reseed(seed);
}

R250_R521::~R250_R521()
{

}

void R250_R521::initialize()
{
    m_index250 = 0;
    m_index521 = 0;

    // Fill buffer with 31-bit random values
    LinearCongruential lcrng(initialSeed());
    for(int index = 0; index < 250; ++index)
        m_buffer250[index] = lcrng.next();
    for(int index = 0; index < 521; ++index)
        m_buffer521[index] = lcrng.next();

    uint32_t msb = 0x40000000;  // Most-Significant-Bit: To turn on the diagonal bit
    uint32_t mask = 0x7FFFFFFF; // To turn off leftmost bits
    for(int index = 0; index < 31; ++index) {
        int k = 7 * index + 3;  // Select a word to operate on
        m_buffer250[k] &= mask; // Turn off bits left of the diagonal
        m_buffer250[k] |= msb;  // Turn on the diagonal bit

        k = 13 * index + 3; // Select a word to operate on
        m_buffer521[k] &= mask; // Turn off bits left of the diagonal
        m_buffer521[k] |= msb;  // Turn on the diagonal bit

        mask >>= 1;
        msb >>= 1;
    }
}

int32_t R250_R521::calcNext()
{
    int index = (m_index250 >= 147) ? (m_index250 - 147) : (m_index250 + 103);
    int32_t newRand250 = m_buffer250[m_index250] ^= m_buffer250[index];

    if(++(m_index250) >= 250) // Increment pointer for next time
        m_index250 = 0;

    index = (m_index521 >= 353) ? (m_index521 - 353) : (m_index521 + 168);
    int32_t newRand521 = m_buffer521[m_index521] ^= m_buffer521[index];

    if(++(m_index521) >= 521) // Increment pointer for next time
        m_index521 = 0;

    return newRand250 ^ newRand521;
}
