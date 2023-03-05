#ifndef __PERLINNOISE_H__
#define __PERLINNOISE_H__

#include <cmath>
#include <cstdint>
#include <cassert>

#include "../Ease.h"
#include "../NoiseBuffer2D.h"
#include "../RNG31Transform/Uniform.h"
#include "Uniform.h"

namespace RNG31
{
    class Perlin
    {
        // https://rosettacode.org/wiki/Perlin_noise#C

    public:
        Perlin(RNG31::Uniform *urng);
        ~Perlin();

        Ease::EasingMethod getEasingMethod() const;
        void setEasingMethod(Ease::EasingMethod easingMethod);

        void reset();
        void shuffle();

        void fill(NoiseBuffer2D *buffer, double xScale, double yScale) const;
        void layeredFill(NoiseBuffer2D *buffer, int layerCount, double layerScale, double signalAttenuation, double xScale, double yScale) const;

    private:
        const static uint8_t PERMUTATIONS[];
        uint8_t m_permutations[512];
        Ease::EasingMethod m_easingMethod;

        Uniform *m_urng;

        double sample(double x, double y, double z) const;
        double fade(double t) const;
        static double lerp(double t, double a, double b);
        static double grad(int hash, double x, double y, double z);
    };
}

#endif /* #ifndef __PERLINNOISE__ */
