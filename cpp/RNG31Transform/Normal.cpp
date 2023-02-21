#include "Normal.h"

using namespace RNG31;

Normal::Normal(AbstractRNGCore *rng) :
    m_urng(rng)
{
    m_hasCachedValue = false;
}

Normal::~Normal()
{

}

double Normal::next()
{
    double result;
    if(m_hasCachedValue) {
        result = m_cachedValue;
        m_hasCachedValue = false;
    } else {
        double w, x1, x2;
		do {
			x1 = m_urng.nextFloat(-1.0, 1.0);
			x2 = m_urng.nextFloat(-1.0, 1.0);
			w = (x1 * x1) + (x2 * x2);
		} while (w >= 1.0);

		w = sqrt((-2.0 * log(w)) / w);
		result = x1 * w;
		m_cachedValue = x2 * w;
		m_hasCachedValue = 1;
    }

    return result;
}

double Normal::next(double stdDev)
{
    return stdDev * next();
}

double Normal::next(double stdDev, double mean)
{
    return next(stdDev) + mean;
}
