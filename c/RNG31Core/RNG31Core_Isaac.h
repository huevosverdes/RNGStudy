#ifndef __RNG31CORE_ISAAC_H__
#define __RNG31CORE_ISAAC_H__

#include <stdint.h>

#include "AbstractRNG31Core.h"
#include "RNG31Core_LinearCongruential.h"

/* http://burtleburtle.net/bob/rand/isaac.html */

typedef struct {
    AbstractRNG31Core abstractRNG;
    uint32_t buffer[256];
    uint32_t state[256];
    uint32_t aa;
    uint32_t bb;
    uint32_t cc;
    uint32_t index;
} RNG31Core_Isaac;

AbstractRNG31Core *isaac_initDefault(RNG31Core_Isaac *rng);
AbstractRNG31Core *isaac_init(RNG31Core_Isaac *rng, int32_t seed);

#endif /* __RNG31CORE_ISAAC_H__ */
