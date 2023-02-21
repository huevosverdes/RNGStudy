#include "GBFlip.h"

using namespace RNG31;

GBFlip::GBFlip(int32_t seed) :
    AbstractRNGCore(seed)
{
    reseed(seed);
}

GBFlip::~GBFlip()
{

}

#define MOD_DIFF(x, y) (((x) - (y)) & AbstractRNGCore::MAX)
void GBFlip::initialize()
{
    m_array[0] = -1;

    int32_t prev = initialSeed();
    int32_t next = 1;
    int32_t seed = prev = MOD_DIFF(prev , 0);
    m_array[55] = prev;

    for(int32_t i = 21; i; i = (i + 21) % 55) {
        m_array[i] = next;

        next = MOD_DIFF(prev , next);
        if(seed & 1) seed = 0x40000000 | (seed >> 1);
        else seed >>= 1;
        next = MOD_DIFF(next, seed);

        prev = m_array[i];
    }

    (void)cycle();
    (void)cycle();
    (void)cycle();
    (void)cycle();
    (void)cycle();
}

int32_t GBFlip::calcNext()
{
    return (*m_ptr >= 0 ? *m_ptr-- : cycle());
}

int32_t GBFlip::cycle()
{
    int32_t *ii;
    int32_t *jj;
    for(ii = &m_array[1], jj = &m_array[32]; jj <= &m_array[55]; ii++, jj++)
        *ii = MOD_DIFF(*ii , *jj);
    for(jj = &m_array[1]; ii <= &m_array[55]; ii++, jj++)
        *ii = MOD_DIFF (*ii, *jj);
    m_ptr = &m_array[54];
    return m_array[55];
}
