#ifndef __RNG31_PERLIN_H__
#define __RNG31_PERLIN_H__

#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "../RNG31Core/AbstractRNG31Core.h"
#include "../Ease.h"
#include "RNG31_Uniform.h"

/* https://rosettacode.org/wiki/Perlin_noise#C */
typedef struct {
    uint8_t permutations[512];
    EasingMethod easingMethod;
    RNG31_Uniform urng;
} RNG31_Perlin;

void rng31Perlin_init(RNG31_Perlin *perlin, AbstractRNG31Core *rng);
void rng31Perlin_reset(RNG31_Perlin *perlin);
void rng31Perlin_shuffle(RNG31_Perlin *perlin);

/* void rng31Perlin_fill(RNG31_Perlin *perlin, NoiseBuffer *buffer, double x, double y, double z); */
/* void rng31Perlin_layeredFill(RNG31_Perlin *perlin, NoiseBuffer *buffer, int layerCount, int layerScale, double signalAttenuation, double x, double y, double z); */

#endif /* __RNG31_PERLIN_H__ */
