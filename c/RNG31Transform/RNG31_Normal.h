#ifndef __RNG31_NORMAL_H__
#define __RNG31_NORMAL_H__

#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "../RNG31Core/AbstractRNG31Core.h"
#include "RNG31_Uniform.h"

/* ftp://taygeta.com/pub/c/boxmuller.c */

typedef struct {
    RNG31_Uniform urng;
    double cachedValue;
    int hasCachedValue;
} RNG31_Normal;

void rng31Normal_init(RNG31_Normal *nrng, AbstractRNG31Core *rng);
double rng31Normal_next(RNG31_Normal *nrng, double stdDev, double mean);

#endif /* __RNG31_NORMAL_H__ */
