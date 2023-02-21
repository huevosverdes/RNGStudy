#ifndef __ISAAC_H__
#define __ISAAC_H__

#include <cstdint>

#include "AbstractRNGCore.h"
#include "LinearCongruential.h"

namespace RNG31
{
    class Isaac : public AbstractRNGCore
    {
        // http://burtleburtle.net/bob/rand/isaac.html

    public:
        Isaac(int32_t seed=0);
        ~Isaac() override;

    protected:
        void initialize() override;
        int32_t calcNext() override;

    private:
        uint32_t m_buffer[256];
        uint32_t m_state[256];
        uint32_t m_aa;
        uint32_t m_bb;
        uint32_t m_cc;
        uint32_t m_index;

        void populate();
    };
}

#endif /* #ifndef __ISAAC_H__ */
