#ifndef __ABSTRACTRNGCORE_H__
#define __ABSTRACTRNGCORE_H__

#include <ctime>
#include <cstdint>
#include <cassert>

namespace RNG31
{
    class AbstractRNGCore
    {
        // Abstract base class for generating random numbers in [0, 2^31 - 1].
        // - Implement initialize() to set up the initial state. This is called by reseed().
        // - Implement calcNext(). This must generate a number in the range above.
        // - Your constructor must call reseed because this base class cannot invoke
        //   the pure virtual method `initialize` (via reseed) in its constructor.

    public:

        static const int32_t MAX = 0x7FFFFFFF;

        AbstractRNGCore(int32_t seed=0);
        virtual ~AbstractRNGCore();

        int32_t next();
        void reseed(int32_t seed=0);

        int32_t initialSeed() const;

    protected:
        virtual void initialize() = 0;
        virtual int32_t calcNext() = 0;

    private:
        int32_t m_initialSeed;
    };
}

#endif /* #ifndef __ABSTRACTRNG31CORE_H__ */
