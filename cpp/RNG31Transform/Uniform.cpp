#include "Uniform.h"

using namespace RNG31;

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif /* M_PI */

Uniform::Uniform(AbstractRNGCore *rng)
{
    m_rng = rng;
    m_coinValue = 0;
    m_coinMask = 0x0;
}

Uniform::~Uniform()
{
    m_rng = nullptr;
}

int32_t Uniform::next()
{
    return m_rng->next();
}

int32_t Uniform::next(int32_t high)
{
    uint32_t t = 0x80000000 - (0x80000000 % high);
    uint32_t result;

    do {
        result = (uint32_t)m_rng->next();
    } while(t <= result);

    return result % high;
}

int32_t Uniform::next(int32_t low, int32_t high)
{
    assert(low < high);
    return next(high - low) + low;
}

double Uniform::nextFloat()
{
    return m_rng->next() / (double)0x80000000;
}

double Uniform::nextFloat(double high)
{
    return nextFloat() * high;
}

double Uniform::nextFloat(double low, double high)
{
    assert(low < high);
    return nextFloat(high-low) + low;
}

void Uniform::pointInCircle(double radius, double &x, double &y)
{
    // https://programming.guide/random-point-within-circle.html
    assert(radius > 0.0);
    double angle = nextFloat() * 2.0 * M_PI;
    double r = radius * sqrt(nextFloat());
    x = (r * cos(angle));
    y = (r * sin(angle));
}

void Uniform::shuffle(void *container, int length, SwapFuncPtr swap)
{
    // https://www.rosettacode.org/wiki/Knuth_shuffle
    for(int index = length - 1; index > 0; --index) {
        int swapIndex = next(index);
        swap(container, index, swapIndex);
    }
}

bool Uniform::coinFlip()
{
    if(m_coinMask <= 0) {
        m_coinValue = m_rng->next();
        m_coinMask = 0x80000000;
    }
    m_coinMask >>= 1;
    return (m_coinMask & m_coinValue) != 0;
}
