#ifndef __RNG31CORE_GBFLIP_H__
#define __RNG31CORE_GBFLIP_H__

#include <stdint.h>

#include "AbstractRNG31Core.h"

/* https://tex.loria.fr/sgb/gb_flip.pdf */

typedef struct {
    AbstractRNG31Core abstractRNG;
    int32_t array[56];
    int32_t *ptr;
} RNG31Core_GBFlip;

AbstractRNG31Core *gbFlip_initDefault(RNG31Core_GBFlip *rng);
AbstractRNG31Core *gbFlip_init(RNG31Core_GBFlip *rng, int32_t seed);

#endif /* __RNG31CORE_GBFLIP_H__ */
