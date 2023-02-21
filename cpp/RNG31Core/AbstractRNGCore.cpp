#include "AbstractRNGCore.h"

using namespace RNG31;

AbstractRNGCore::AbstractRNGCore(int32_t seed)
{

}

AbstractRNGCore::~AbstractRNGCore()
{

}

int32_t AbstractRNGCore::next()
{
    int32_t result = calcNext();
    assert(0 <= result && result <= AbstractRNGCore::MAX);
    return result;
}

void AbstractRNGCore::reseed(int32_t seed)
{
    if(seed == 0)
        seed = time(nullptr);
    m_initialSeed = seed;
    initialize();
}

int32_t AbstractRNGCore::initialSeed() const
{
    return m_initialSeed;
}
