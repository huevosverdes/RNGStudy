#ifndef __NORMAL_H__
#define __NORMAL_H__

#include <cassert>
#include <cstdint>
#include <cmath>

#include "../RNG31Core/AbstractRNGCore.h"
#include "Uniform.h"

namespace RNG31
{
    class Normal
    {
        // ftp://taygeta.com/pub/c/boxmuller.c

    public:
        Normal(AbstractRNGCore *rng);
        ~Normal();

        double next();
        double next(double stdDev);
        double next(double stdDev, double mean);

    private:
        Uniform m_urng;
        double m_cachedValue;
        bool m_hasCachedValue;
    };
}

#endif /* #ifndef __NORMAL_H__ */
