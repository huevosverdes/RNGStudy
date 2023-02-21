#include "RNG31_Normal.h"

void rng31Normal_init(RNG31_Normal *nrng, AbstractRNG31Core *rng)
{
    rng31Uniform_init(&(nrng->urng), rng);
    nrng->hasCachedValue = 0;
}

double rng31Normal_next(RNG31_Normal *nrng, double stdDev, double mean)
{
    double result;
    if(nrng->hasCachedValue)
    {
        result = nrng->cachedValue;
        nrng->hasCachedValue = 0;
    }
    else
    {
        double w, x1, x2;
		do
        {
			x1 = rng31Uniform_nextFloat(&(nrng->urng), -1.0, 1.0);
			x2 = rng31Uniform_nextFloat(&(nrng->urng), -1.0, 1.0);
			w = (x1 * x1) + (x2 * x2);
		} while (w >= 1.0);

		w = sqrt((-2.0 * log(w)) / w);
		result = x1 * w;
		nrng->cachedValue = x2 * w;
		nrng->hasCachedValue = 1;
    }

    return (stdDev * result) + mean;
}
