#ifndef __ABSTRACT_RNG31CORE_H__
#define __ABSTRACT_RNG31CORE_H__

#include <time.h>
#include <stdint.h>
#include <assert.h>

/*
Base struct and functions for generating random numbers in [0, 2^31 - 1].

This is how you do inheritance and polymorphism in C: build a vtable.
*/

static const int32_t ABSTRACT_RNG31CORE_MAX = 0x7FFFFFFF;

struct AbstractRNG31Core;

typedef void (*AbstractRNG31CoreInit)(struct AbstractRNG31Core *rng);
typedef int32_t (*AbstractRNG31CoreNext)(struct AbstractRNG31Core *rng);

struct AbstractRNG31Core {
    int32_t initialSeed;

    /* vtable */
    AbstractRNG31CoreInit initPtr;
    AbstractRNG31CoreNext nextPtr;
};
typedef struct AbstractRNG31Core AbstractRNG31Core;

void rng31Core_init(AbstractRNG31Core *rng, AbstractRNG31CoreInit initPtr, AbstractRNG31CoreNext nextPtr, int32_t seed);
void rng31Core_reseed(AbstractRNG31Core *rng, int32_t seed);
int32_t rng31Core_next(AbstractRNG31Core *rng);
int32_t rng31Core_initialSeed(AbstractRNG31Core *rng);

#endif /* __ABSTRACT_RNGCORE31_H__ */
