#ifndef __MERSENNETWISTER__
#define __MERSENNETWISTER__

#include <cstdint>

#include "AbstractRNGCore.h"

namespace RNG31
{
    class MersenneTwister : public AbstractRNGCore
    {
        // https://en.wikipedia.org/wiki/Mersenne_Twister
        // http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/mt.pdf
        // https://create.stephan-brumme.com/mersenne-twister/

    public:
        MersenneTwister(int32_t seed=0);
        ~MersenneTwister() override;

    protected:
        void initialize() override;
        int32_t calcNext() override;

    private:
        // MT19937
        static const uint32_t W = 32;         // W: word size (in number of bits)
        static const uint32_t N = 624;        // N: degree of recurrence
        static const uint32_t M = 397;        // M: middle word, offset for recurrence relation defining series [1, n)
        static const uint32_t R = 31;         // R: number of bits of lower bitmask, [0, w)
        static const uint32_t A = 0x9908B0DF; // A: coefficients of rational normal form twist matrix
        static const uint32_t U = 11;         // U, d, l: additional Mersenne Twister tempering bit shifts/masks
        static const uint32_t D = 0xFFFFFFFF;
        static const uint32_t S = 7;          // S, t: TGFSR(R) tempering bit shifts
        static const uint32_t B = 0x9D2C5680; // B, c: TGFSR(R) tempering bitmasks
        static const uint32_t T = 15;
        static const uint32_t C = 0xEFC60000;
        static const uint32_t L = 18;
        static const uint32_t F = 0x6C078965; // F: initialization parameter
        static const uint32_t LOWER_MASK = 0x7FFFFFFF; // (1 << R) - 1
        static const uint32_t UPPER_MASK = 0x80000000; // lowest W bits of ~LOWER_MASK

        int32_t m_buffer[N];
        uint32_t m_index;

        void twist();
    };
}

#endif /* #ifndef __MERSENNETWISTER__ */
