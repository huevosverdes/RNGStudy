#ifndef __LINEARCONGRUENTIAL_H__
#define __LINEARCONGRUENTIAL_H__

#include <cstdint>

#include "AbstractRNGCore.h"

namespace RNG31
{
    class LinearCongruential : public AbstractRNGCore
    {
        // https://en.wikipedia.org/wiki/Linear_congruential_generator

    public:
        LinearCongruential(int32_t seed=0);
        ~LinearCongruential() override;

    protected:
        void initialize() override;
        int32_t calcNext() override;

    private:
        int32_t m_value;
    };
}

#endif /* #ifndef __LINEARCONGRUENTIAL_H__ */
