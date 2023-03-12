#include <stdio.h>

#include "RNG31Core/GBFlip.h"
#include "RNG31Transform/Uniform.h"

int main(int argc, char **argv)
{
    RNG31::GBFlip gbFlipRNG;
    RNG31::Uniform urng(&gbFlipRNG);
    if(urng.coinFlip())
        printf("Heads\n");
    else
        printf("Tails\n");

    return 0;
}
