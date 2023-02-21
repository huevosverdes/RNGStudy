#ifndef __VOSE_H__
#define __VOSE_H__

#include <cstdint>
#include <queue>

#include "../RNG31Core/AbstractRNGCore.h"
#include "Uniform.h"

namespace RNG31
{
    class Vose
    {
        // Technical Explanation: http://web.eecs.utk.edu/~vose/Publications/random.pdf
        // Practical Explanation: http://www.keithschwarz.com/darts-dice-coins/

    public:
        Vose(AbstractRNGCore *rng, const double *itemWeights, int itemCount);
        ~Vose();

        int next();

    private:
        Uniform m_urng;

        int m_itemCount;
        double *m_probabilities;
        int *m_aliases;
    };
}

#endif /* #ifndef __VOSE_H__ */
