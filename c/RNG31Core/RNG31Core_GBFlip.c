#include "RNG31Core_GBFlip.h"

void gbFlip_initialize(AbstractRNG31Core *rng);
int32_t gbFlip_next(AbstractRNG31Core *rng);

AbstractRNG31Core *gbFlip_initDefault(RNG31Core_GBFlip *rng)
{
    return gbFlip_init(rng, 0);
}

AbstractRNG31Core *gbFlip_init(RNG31Core_GBFlip *rng, int32_t seed)
{
    rng->array[0] = -1;
    AbstractRNG31Core *result = (AbstractRNG31Core*)rng;
    rng31Core_init(result, gbFlip_initialize, gbFlip_next, seed);
    return result;
}

/* Not exposed in header */
#define MOD_DIFF(x, y) (((x) - (y)) & ABSTRACT_RNG31CORE_MAX)

int32_t gbFlip_cycle(RNG31Core_GBFlip *rng)
{
    int32_t *array = &(((RNG31Core_GBFlip*)rng)->array[0]);

    int32_t *ii;
    int32_t *jj;
    for(ii = &array[1], jj = &array[32]; jj <= &array[55]; ii++, jj++)
        *ii = MOD_DIFF(*ii , *jj);
    for(jj = &array[1]; ii <= &array[55]; ii++, jj++)
        *ii = MOD_DIFF(*ii, *jj);
    rng->ptr = &array[54];
    return array[55];
}

void gbFlip_initialize(AbstractRNG31Core *rng)
{
    int32_t *array = &(((RNG31Core_GBFlip*)rng)->array[0]);

    int32_t prev = rng->initialSeed;
    int32_t next = 1;
    int32_t seed = prev = MOD_DIFF(prev , 0);
    array[55] = prev;

    for(int32_t i = 21; i; i = (i + 21) % 55) {
        array[i] = next;

        next = MOD_DIFF(prev , next);
        if(seed & 1) seed = 0x40000000 | (seed >> 1);
        else seed >>= 1;
        next = MOD_DIFF(next, seed);

        prev = array[i];
    }

    (void)gbFlip_cycle((RNG31Core_GBFlip*)rng);
    (void)gbFlip_cycle((RNG31Core_GBFlip*)rng);
    (void)gbFlip_cycle((RNG31Core_GBFlip*)rng);
    (void)gbFlip_cycle((RNG31Core_GBFlip*)rng);
    (void)gbFlip_cycle((RNG31Core_GBFlip*)rng);
}

int32_t gbFlip_next(AbstractRNG31Core *rng)
{
    RNG31Core_GBFlip *gbflip = (RNG31Core_GBFlip*)rng;
    return (*gbflip->ptr >= 0 ? *gbflip->ptr-- : gbFlip_cycle(gbflip));
}
