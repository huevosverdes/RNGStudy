#include <stdio.h>
/* #include <stdlib.h> */
/* #include <string.h> */
/* #include <unistd.h> */


#include "RNG31Core/AbstractRNG31Core.h"
#include "RNG31Core/RNG31Core_GBFlip.h"
#include "RNG31Transform/RNG31_Uniform.h"

int main(int argc, char **argv)
{
    RNG31Core_GBFlip gbFlipRNG;
    AbstractRNG31Core *arng = gbFlip_initDefault(&gbFlipRNG);

    RNG31_Uniform urng;
    rng31Uniform_init(&urng, arng);

    if(rng31Uniform_coinFlip(&urng))
        printf("Heads\n");
    else
        printf("Tails\n");

    return 0;
}
