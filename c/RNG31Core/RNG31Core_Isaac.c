#include "RNG31Core_Isaac.h"

void isaac_initialize(AbstractRNG31Core *rng);
int32_t isaac_next(AbstractRNG31Core *rng);

AbstractRNG31Core *isaac_initDefault(RNG31Core_Isaac *rng)
{
    return isaac_init(rng, 0);
}

AbstractRNG31Core *isaac_init(RNG31Core_Isaac *rng, int32_t seed)
{
    AbstractRNG31Core *result = (AbstractRNG31Core*)rng;
    rng31Core_init(result, isaac_initialize, isaac_next, seed);
    return result;
}

/* Not exposed in header */
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

void isaac_populate(RNG31Core_Isaac *rng)
{
    rng->bb += ++(rng->cc);
    uint32_t x, y;

    for(int index = 0; index < 256; ++index) {
        x = rng->state[index];
        switch(index % 4)
        {
        case 0: rng->aa ^= (rng->aa << 13); break;
        case 1: rng->aa ^= (rng->aa >>  6); break;
        case 2: rng->aa ^= (rng->aa <<  2); break;
        case 3: rng->aa ^= (rng->aa >> 16); break;
        }
        rng->aa                      = rng->state[(index+128)%256] + rng->aa;
        rng->state[index]  = y       = rng->state[(x>>2)%256]      + rng->aa + rng->bb;
        rng->buffer[index] = rng->bb = rng->state[(y>>10)%256]     + x;
    }

    rng->index = 0;

    /* Note that bits 2..9 are chosen from x but 10..17 are chosen
       from y.  The only important thing here is that 2..9 and 10..17
       don't overlap.  2..9 and 10..17 were then chosen for speed in
       the optimized version (rand.c) */
}

void isaac_initialize(AbstractRNG31Core *rng)
{
    RNG31Core_Isaac *irng = (RNG31Core_Isaac*)rng;
    irng->aa = irng->bb = irng->cc = 0;

    uint32_t a, b, c, d, e, f, g, h;
    a = b = c = d = e = f = g = h = 0x9e3779b9; /* Golden Ratio */

    for(int index = 0; index < 4; ++index)
        isaac_mix(a, b, c, d, e, f, g, h);

    // Fill buffer with 31-bit random values
    RNG31Core_LinearCongruential lcrng;
    AbstractRNG31Core *arng = linearCongruential_init(&lcrng, rng31Core_initialSeed(rng));
    for(int index = 0; index < 256; ++index)
        irng->buffer[index] = rng31Core_next(arng);

    for(int index = 0; index < 256; index += 8) {
       a += irng->buffer[index  ]; b +=irng->buffer[index+1];
       c += irng->buffer[index+2]; d +=irng->buffer[index+3];
       e += irng->buffer[index+4]; f +=irng->buffer[index+5];
       g += irng->buffer[index+6]; h +=irng->buffer[index+7];

       isaac_mix(a, b, c, d, e, f, g, h);

       irng->state[index  ] = a; irng->state[index+1] = b;
       irng->state[index+2] = c; irng->state[index+3] = d;
       irng->state[index+4] = e; irng->state[index+5] = f;
       irng->state[index+6] = g; irng->state[index+7] = h;
    }

    for(int index = 0; index < 256; index += 8) {
       a += irng->state[index  ]; b += irng->state[index+1];
       c += irng->state[index+2]; d += irng->state[index+3];
       e += irng->state[index+4]; f += irng->state[index+5];
       g += irng->state[index+6]; h += irng->state[index+7];

       isaac_mix(a,b,c,d,e,f,g,h);

       irng->state[index  ] = a; irng->state[index+1] = b;
       irng->state[index+2] = c; irng->state[index+3] = d;
       irng->state[index+4] = e; irng->state[index+5] = f;
       irng->state[index+6] = g; irng->state[index+7] = h;
    }

    irng->index = 256;
}

int32_t isaac_next(AbstractRNG31Core *rng)
{
    RNG31Core_Isaac *irng = (RNG31Core_Isaac*)rng;
    if(irng->index > 255)
        isaac_populate(irng);

    return 0x7FFFFFFF & irng->buffer[(irng->index)++];
}
