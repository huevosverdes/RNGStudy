#ifndef __RNG31CORE_LINEAR_CONGRUENTIAL_H__
#define __RNG31CORE_LINEAR_CONGRUENTIAL_H__

#include <stdint.h>

#include "AbstractRNG31Core.h"

/* https://en.wikipedia.org/wiki/Linear_congruential_generator */

typedef struct {
    AbstractRNG31Core abstractRNG;
    int32_t value;
} RNG31Core_LinearCongruential;

AbstractRNG31Core *linearCongruential_initDefault(RNG31Core_LinearCongruential *rng);
AbstractRNG31Core *linearCongruential_init(RNG31Core_LinearCongruential *rng, int32_t seed);

#endif /* __RNG31CORE_LINEAR_CONGRUENTIAL_H__ */
