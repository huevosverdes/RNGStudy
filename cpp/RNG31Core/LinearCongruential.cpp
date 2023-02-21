#include "LinearCongruential.h"

using namespace RNG31;

LinearCongruential::LinearCongruential(int32_t seed) :
    AbstractRNGCore(seed)
{
    reseed(seed);
}

LinearCongruential::~LinearCongruential()
{

}

void LinearCongruential::initialize()
{
    m_value = initialSeed();
}

/* Increment */
#define LINEAR_CONG_A 1103515245

/* Multiplier */
#define LINEAR_CONG_C 12345

/* Modulus */
#define LINEAR_CONG_M 0x80000000

int32_t LinearCongruential::calcNext()
{
    m_value = (LINEAR_CONG_A * m_value + LINEAR_CONG_C) % LINEAR_CONG_M;
    return m_value;
}
