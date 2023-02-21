#ifndef __R250_R521_H__
#define __R250_R521_H__

#include <cstdint>

#include "AbstractRNGCore.h"
#include "LinearCongruential.h"

namespace RNG31
{
    class R250_R521 : public AbstractRNGCore
    {
        // http://pythonlabtools.sourceforge.net/analysisdocs/html/a00152.html

    public:
        R250_R521(int32_t seed=0);
        ~R250_R521() override;

    protected:
        void initialize() override;
        int32_t calcNext() override;

    private:
        int32_t m_buffer250[250];
        int32_t m_index250;

        int32_t m_buffer521[521];
        int32_t m_index521;
    };
}

#endif /* #ifndef __R250_R521_H__ */
