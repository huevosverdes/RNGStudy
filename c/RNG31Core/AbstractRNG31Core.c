#include "AbstractRNG31Core.h"

void rng31Core_initDefault(AbstractRNG31Core *rng, AbstractRNG31CoreInit initPtr, AbstractRNG31CoreNext nextPtr)
{
    rng31Core_init(rng, initPtr, nextPtr, 0);
}

void rng31Core_init(AbstractRNG31Core *rng, AbstractRNG31CoreInit initPtr, AbstractRNG31CoreNext nextPtr, int32_t seed)
{
    rng->initPtr = initPtr;
    rng->nextPtr = nextPtr;
    rng31Core_reseed(rng, seed);
}

void rng31Core_reseedDefault(AbstractRNG31Core *rng)
{
    rng31Core_reseed(rng, 0);
}

void rng31Core_reseed(AbstractRNG31Core *rng, int32_t seed)
{
    if(seed == 0)
        seed = (int)time(NULL);
    rng->initialSeed = seed;
    rng->initPtr(rng);
}

int32_t rng31Core_next(AbstractRNG31Core *rng)
{
    int32_t result = rng->nextPtr(rng);
    assert(0 <= result && result <= ABSTRACT_RNG31CORE_MAX);
    return result;
}

int32_t rng31Core_initialSeed(AbstractRNG31Core *rng)
{
    return rng->initialSeed;
}
