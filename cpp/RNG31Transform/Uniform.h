#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <cassert>
#include <cstdint>
#include <cmath>

#include "../RNG31Core/AbstractRNGCore.h"

// TODO: Poisson
// - https://a5huynh.github.io/posts/2019/poisson-disk-sampling/
// - https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf
// - https://www.youtube.com/watch?v=flQgnCUxHlw

namespace RNG31
{
    typedef void (*SwapFuncPtr)(void *container, int index1, int index2);

    class Uniform
    {

    public:
        Uniform(AbstractRNGCore *rng);
        ~Uniform();

        int32_t next();
        int32_t next(int32_t high);
        int32_t next(int32_t low, int32_t high);

        double nextFloat();
        double nextFloat(double high);
        double nextFloat(double low, double high);
        void pointInCircle(double radius, double &x, double &y);
        void shuffle(void *container, int length, SwapFuncPtr swap);

        bool coinFlip();

    private:
        AbstractRNGCore *m_rng;
        int32_t m_coinValue;
        uint32_t m_coinMask;
    };
}

#endif /* #ifndef __UNIFORM_H__ */
