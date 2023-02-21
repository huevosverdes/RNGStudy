#ifndef __RNG31_VOSE_H__
#define __RNG31_VOSE_H__

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "../RNG31Core/AbstractRNG31Core.h"
#include "RNG31_Uniform.h"

/* Technical Explanation: http://web.eecs.utk.edu/~vose/Publications/random.pdf */
/* Practical Explanation: http://www.keithschwarz.com/darts-dice-coins/ */

typedef struct {
    RNG31_Uniform urng;
    int itemCount;
    double *probabilities;
    int *aliases;
} RNG31_Vose;

void rng31Vose_init(RNG31_Vose *vrng, AbstractRNG31Core *rng, const double *itemWeights, int itemCount);
void rng31Vose_release(RNG31_Vose *vrng);
int32_t rng31Vose_next(RNG31_Vose *vrng);

#endif /* __RNGVOSE_H__ */
