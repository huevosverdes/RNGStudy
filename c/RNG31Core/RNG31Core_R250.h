#ifndef __RNG31CORE_R250_H__
#define __RNG31CORE_R250_H__

#include <stdint.h>

#include "AbstractRNG31Core.h"
#include "RNG31Core_LinearCongruential.h"

/* http://faculty.uml.edu/jpropp/r250.c */

typedef struct {
    AbstractRNG31Core abstractRNG;
    int32_t buffer[250];
    int32_t index;
} RNG31Core_R250;

AbstractRNG31Core *r250_initDefault(RNG31Core_R250 *rng);
AbstractRNG31Core *r250_init(RNG31Core_R250 *rng, int32_t seed);

#endif /* __RNG31CORE_R250_H__ */
