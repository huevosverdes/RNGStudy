#ifndef __RNG31_UNIFORM_H__
#define __RNG31_UNIFORM_H__

#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "../RNG31Core/AbstractRNG31Core.h"

typedef void (*SwapFuncPtr)(void *container, int index1, int index2);

typedef struct
{
    AbstractRNG31Core *rng;
    int32_t coinValue;
    uint32_t coinMask;
} RNG31_Uniform;

void rng31Uniform_init(RNG31_Uniform *urng, AbstractRNG31Core *rng);
int32_t rng31Uniform_next(RNG31_Uniform *urng, int32_t low, int32_t high);
double rng31Uniform_nextFloat(RNG31_Uniform *urng, double low, double high);
void rng31Uniform_pointInCircle(RNG31_Uniform *urng, double radius, double *x, double *y);
void rng31Uniform_shuffle(RNG31_Uniform *urng, void *container, int length, SwapFuncPtr swap);
int rng31Uniform_coinFlip(RNG31_Uniform *urng);

#endif /* __RNG31_UNIFORM_H__ */
