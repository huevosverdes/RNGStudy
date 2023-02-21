#ifndef __PERLINNOISE_H__
#define __PERLINNOISE_H__

#include <cmath>
#include <cstdint>
#include <cassert>

#include "../Ease.h"
#include "../RNG31Core/AbstractRNGCore.h"
#include "Uniform.h"

namespace RNG31
{
    class Perlin
    {
        // https://rosettacode.org/wiki/Perlin_noise#C

    public:
        Perlin(AbstractRNGCore *rng);
        ~Perlin();

        Ease::EasingMethod getEasingMethod() const;
        void setEasingMethod(Ease::EasingMethod easingMethod);

        void reset();
        void shuffle();

        // void fill(NoiseBuffer *buffer, double x, double y=0.0, double z=0.0) const;
        // void layeredFill(NoiseBuffer *buffer, int layerCount, double layerScale, double signalAttenuation, double x, double y=0.0, double z=0.0) const;

    private:
        const static uint8_t PERMUTATIONS[];
        uint8_t m_permutations[512];
        Ease::EasingMethod m_easingMethod;

        Uniform m_urng;

        double sample(double x, double y, double z) const;
        double fade(double t) const;
        static double lerp(double t, double a, double b);
        static double grad(int hash, double x, double y, double z);
    };
}

#endif /* #ifndef __PERLINNOISE__ */
