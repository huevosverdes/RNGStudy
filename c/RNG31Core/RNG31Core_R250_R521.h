#ifndef __RNG31CORE_R250_R521_H__
#define __RNG31CORE_R250_R521_H__

#include <stdint.h>

#include "AbstractRNG31Core.h"
#include "RNG31Core_LinearCongruential.h"

/* http://pythonlabtools.sourceforge.net/analysisdocs/html/a00152.html */

typedef struct {
    AbstractRNG31Core abstractRNG;
    int32_t buffer250[250];
    int32_t index250;
    int32_t buffer521[521];
    int32_t index521;
} RNG31Core_R250_R521;

AbstractRNG31Core *r250_r521_initDefault(RNG31Core_R250_R521 *rng);
AbstractRNG31Core *r250_r521_init(RNG31Core_R250_R521 *rng, int32_t seed);

#endif /* __RNG31CORE_R250_R521_H__ */
