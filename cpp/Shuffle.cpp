#include <vector>
#include <iostream>
#include <cstdint>

#include "RNG31Core/GBFlip.h"
#include "RNG31Transform/Uniform.h"

void printVector(std::vector<int> v, const char *prefix);
void intVectorSwap(void *container, int index1, int index2);

int main(int argc, char **argv)
{
    RNG31::GBFlip gbFlipRNG;
    RNG31::Uniform urng(&gbFlipRNG);

    std::vector<int> v;
    for(int index = 0; index < 20; ++index)
        v.push_back(index);

    printVector(v, "Sorted");
    urng.shuffle(&v, v.size(), intVectorSwap);
    printVector(v, "Shuffled");

    return 0;
}

void printVector(std::vector<int> v, const char *prefix)
{
    std::cout << prefix << " Array:" << std::endl;
    std::cout << " - {";
    for(uint32_t index = 0; index < v.size(); ++index)
        if(index == 0)
            std::cout << v[index];
        else
            std::cout << ", " << v[index];
    std::cout << "}" << std::endl << std::endl;
}

void intVectorSwap(void *container, int index1, int index2)
{
    std::vector<int> *v = (std::vector<int>*)container;
    int value = (*v)[index1];
    (*v)[index1] = (*v)[index2];
    (*v)[index2] = value;
}
