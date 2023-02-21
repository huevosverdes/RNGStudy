#ifndef __R250_H__
#define __R250_H__

#include <cstdint>

#include "AbstractRNGCore.h"
#include "LinearCongruential.h"

namespace RNG31
{
    class R250 : public AbstractRNGCore
    {
        // http://faculty.uml.edu/jpropp/r250.c

    public:
        R250(int32_t seed=0);
        ~R250() override;

    protected:
        void initialize() override;
        int32_t calcNext() override;

    private:
        int32_t m_buffer[250];
        int32_t m_index;
    };
}

#endif /* #ifndef __R250_H__ */
