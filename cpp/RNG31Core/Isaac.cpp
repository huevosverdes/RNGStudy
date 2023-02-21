#include "Isaac.h"

using namespace RNG31;

#define isaac_mix(a,b,c,d,e,f,g,h) \
{ \
   a ^= b << 11; d += a; b += c; \
   b ^= c >> 2;  e += b; c += d; \
   c ^= d << 8;  f += c; d += e; \
   d ^= e >> 16; g += d; e += f; \
   e ^= f << 10; h += e; f += g; \
   f ^= g >> 4;  a += f; g += h; \
   g ^= h << 8;  b += g; h += a; \
   h ^= a >> 9;  c += h; a += b; \
}

Isaac::Isaac(int32_t seed) :
    AbstractRNGCore(seed)
{
    reseed(seed);
}

Isaac::~Isaac()
{

}

void Isaac::initialize()
{
    m_aa = m_bb = m_cc = 0;

    uint32_t a, b, c, d, e, f, g, h;
    a = b = c = d = e = f = g = h = 0x9e3779b9; /* Golden Ratio */

    for(int index = 0; index < 4; ++index)
        isaac_mix(a, b, c, d, e, f, g, h);

    // Fill buffer with 31-bit random values
    LinearCongruential lcrng(initialSeed());
    for(int index = 0; index < 256; ++index)
        m_buffer[index] = lcrng.next();

    for(int index = 0; index < 256; index += 8)
    {
       a +=m_buffer[index  ]; b += m_buffer[index+1];
       c +=m_buffer[index+2]; d += m_buffer[index+3];
       e +=m_buffer[index+4]; f += m_buffer[index+5];
       g +=m_buffer[index+6]; h += m_buffer[index+7];

       isaac_mix(a, b, c, d, e, f, g, h);

       m_state[index  ] = a; m_state[index+1] = b;
       m_state[index+2] = c; m_state[index+3] = d;
       m_state[index+4] = e; m_state[index+5] = f;
       m_state[index+6] = g; m_state[index+7] = h;
    }

    for(int index = 0; index < 256; index += 8)
    {
       a += m_state[index  ]; b += m_state[index+1];
       c += m_state[index+2]; d += m_state[index+3];
       e += m_state[index+4]; f += m_state[index+5];
       g += m_state[index+6]; h += m_state[index+7];

       isaac_mix(a,b,c,d,e,f,g,h);

       m_state[index  ] = a; m_state[index+1] = b;
       m_state[index+2] = c; m_state[index+3] = d;
       m_state[index+4] = e; m_state[index+5] = f;
       m_state[index+6] = g; m_state[index+7] = h;
    }

    m_index = 256;
}

int32_t Isaac::calcNext()
{
    if(m_index > 255) populate();

    return 0x7FFFFFFF & m_buffer[m_index++];
}

void Isaac::populate()
{
    m_bb += ++(m_cc);
    uint32_t x, y;

    for(int index = 0; index < 256; ++index) {
        x = m_state[index];
        switch(index % 4)
        {
        case 0: m_aa ^= (m_aa << 13); break;
        case 1: m_aa ^= (m_aa >>  6); break;
        case 2: m_aa ^= (m_aa <<  2); break;
        case 3: m_aa ^= (m_aa >> 16); break;
        }
        m_aa                   = m_state[(index+128)%256] + m_aa;
        m_state[index]  = y    = m_state[(x>>2)%256]      + m_aa + m_bb;
        m_buffer[index] = m_bb = m_state[(y>>10)%256]     + x;
    }

    m_index = 0;

    // Note that bits 2..9 are chosen from x but 10..17 are chosen
    // from y.  The only important thing here is that 2..9 and 10..17
    // don't overlap.  2..9 and 10..17 were then chosen for speed in
    // the optimized version (rand.c)
}
