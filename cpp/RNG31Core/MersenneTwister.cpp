#include "MersenneTwister.h"

using namespace RNG31;

MersenneTwister::MersenneTwister(int32_t seed) :
    AbstractRNGCore(seed)
{
    reseed(seed);
}

MersenneTwister::~MersenneTwister()
{

}

void MersenneTwister::initialize()
{
    m_index = N;
    uint32_t value = m_buffer[0] = initialSeed();
    for(uint32_t index = 1; index < N; ++index)
        value = m_buffer[index] = F * (value ^ ((value >> (W - 2)))) + index;
}

int32_t MersenneTwister::calcNext()
{
    if(m_index >= N)
        twist();

    uint32_t y = m_buffer[m_index++];
    y ^= (y >> U) & D;
    y ^= (y << S) & B;
    y ^= (y << T) & C;
    y ^= (y >> L);

    return (LOWER_MASK & y); // Only 31 bits
}

void MersenneTwister::twist()
{
    for(uint32_t index = 0; index < N; ++index) {
        uint32_t x = ((m_buffer[index] & UPPER_MASK) + (m_buffer[(index + 1) % N] & LOWER_MASK));
        uint32_t xA = x >> 1;
        if(x & 0x1)
            xA ^= A;
        m_buffer[index] = m_buffer[(index + M) % N] ^ xA;
    }
    m_index = 0;
}
