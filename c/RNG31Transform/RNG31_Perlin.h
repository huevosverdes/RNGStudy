#ifndef __RNG31_PERLIN_H__
#define __RNG31_PERLIN_H__

#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "../RNG31Transform/RNG31_Uniform.h"
#include "../Ease.h"
#include "../NoiseBuffer2D.h"
#include "RNG31_Uniform.h"

/* https://rosettacode.org/wiki/Perlin_noise#C */
typedef struct {
    uint8_t permutations[512];
    EasingMethod easingMethod;
    RNG31_Uniform *urng;
} RNG31_Perlin;

void rng31Perlin_init(RNG31_Perlin *perlin, RNG31_Uniform *urng);
void rng31Perlin_reset(RNG31_Perlin *perlin);
void rng31Perlin_shuffle(RNG31_Perlin *perlin);

void rng31Perlin_fill(RNG31_Perlin *perlin, NoiseBuffer2D *buffer, double xScale, double yScale, double z);
void rng31Perlin_layeredFill(RNG31_Perlin *perlin, NoiseBuffer2D *buffer, int layerCount, double layerScale, double signalAttenuation, double xScale, double yScale, double z);

#endif /* __RNG31_PERLIN_H__ */
