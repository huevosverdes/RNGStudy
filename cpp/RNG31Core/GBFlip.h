#ifndef __GBFLIP_H__
#define __GBFLIP_H__

#include <cstdint>

#include "AbstractRNGCore.h"

namespace RNG31
{
    class GBFlip : public AbstractRNGCore
    {
        // https://tex.loria.fr/sgb/gb_flip.pdf

    public:
        explicit GBFlip(int32_t seed=0);
        ~GBFlip() override;

    protected:
        void initialize() override;
        int32_t calcNext() override;

    private:
        int32_t m_array[56];
        int32_t *m_ptr;

        int32_t cycle();
    };
}

#endif /* #ifndef __GBFLIP_H__ */
