#include <stdio.h>

#include "RNG31Core/AbstractRNG31Core.h"
#include "RNG31Core/RNG31Core_GBFlip.h"
#include "RNG31Transform/RNG31_Uniform.h"

void printArray(int *array, int arraySize, const char *prefix);
void intArraySwap(void *container, int index1, int index2);

int main(int argc, char **argv)
{
    RNG31Core_GBFlip gbFlipRNG;
    AbstractRNG31Core *arng = gbFlip_initDefault(&gbFlipRNG);

    RNG31_Uniform urng;
    rng31Uniform_init(&urng, arng);

#define ARRAY_SIZE 20
    int array[ARRAY_SIZE];
    for(int index = 0; index < ARRAY_SIZE; ++index)
        array[index] = index;

    printArray(array, ARRAY_SIZE, "Sorted");
    rng31Uniform_shuffle(&urng, array, ARRAY_SIZE, intArraySwap);
    printArray(array, ARRAY_SIZE, "Shuffled");

    return 0;
}

void printArray(int *array, int arraySize, const char *prefix)
{
    printf("%s Array:\n - {", prefix);
    for(int index = 0; index < arraySize; ++index)
        if(index == 0)
            printf("%d", array[index]);
        else
            printf(", %d", array[index]);
    printf("}\n\n");
}

void intArraySwap(void *container, int index1, int index2)
{
    int *array = (int*)container;
    int value = array[index1];
    array[index1] = array[index2];
    array[index2] = value;
}
