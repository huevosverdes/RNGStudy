#ifndef __RNG31CORE_MERSENNE_TWISTER_H__
#define __RNG31CORE_MERSENNE_TWISTER_H__

#include <stdint.h>

#include "AbstractRNG31Core.h"

/* https://en.wikipedia.org/wiki/Mersenne_Twister                  */
/* http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/mt.pdf */
/* https://create.stephan-brumme.com/mersenne-twister/             */

typedef struct {
    AbstractRNG31Core abstractRNG;
    int32_t buffer[624];
    int32_t index;
} RNG31Core_MersenneTwister;

AbstractRNG31Core *mersenneTwister_initDefault(RNG31Core_MersenneTwister *rng);
AbstractRNG31Core *mersenneTwister_init(RNG31Core_MersenneTwister *rng, int32_t seed);

#endif /* __RNG31CORE_MERSENNE_TWISTER_H__ */
