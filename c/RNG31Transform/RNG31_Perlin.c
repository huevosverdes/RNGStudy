#include "RNG31_Perlin.h"

const uint8_t RNG31_PERLIN_PERMUTATIONS[] = {
    151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225, 140,  36, 103,  30,
     69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148, 247, 120, 234,  75,   0,  26, 197,  62,
     94, 252, 219, 203, 117,  35,  11,  32,  57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136,
    171, 168,  68, 175,  74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
     60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,  65,  25,  63, 161,
      1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169, 200, 196, 135, 130, 116, 188, 159,  86,
    164, 100, 109, 198, 173, 186,   3,  64,  52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126,
    255,  82,  85, 212, 207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
    119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9, 129,  22,  39, 253,
     19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104, 218, 246,  97, 228, 251,  34, 242, 193,
    238, 210, 144,  12, 191, 179, 162, 241,  81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31,
    181, 199, 106, 157, 184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
    222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180
};

double rng31Perlin_sample(const RNG31_Perlin *perlin, double x, double y, double z);
double rng31Perlin_fade(const RNG31_Perlin *perlin, double t);
double rng31Perlin_lerp(double t, double a, double b);
double rng31Perlin_grad(int hash, double x, double y, double z);

void rng31Perlin_init(RNG31_Perlin *perlin, AbstractRNG31Core *rng)
{
    rng31Perlin_reset(perlin);
    perlin->easingMethod = SMOOTHERSTEP;
    rng31Uniform_init(&(perlin->urng), rng);
}

void rng31Perlin_reset(RNG31_Perlin *perlin)
{
    for(int index = 0; index < 256; ++index)
        perlin->permutations[index] = RNG31_PERLIN_PERMUTATIONS[index];
    for(int index = 0; index < 256; ++index)
        perlin->permutations[index + 256] = perlin->permutations[index];
}

void rng31Perlin_shuffle(RNG31_Perlin *perlin)
{
    /* TODO: Shuffle first 256 */
    for(int index = 0; index < 256; ++index)
        perlin->permutations[index + 256] = perlin->permutations[index];
}

/* void rng31Perlin_fill(RNG31_Perlin *perlin, NoiseBuffer *buffer, double x, double y, double z) */
/* { */
/*     if(noiseBuffer_is2D(buffer)) */
/*     { */
/*         int rowCount = noiseBuffer_height(buffer); */
/*         int colCount = noiseBuffer_width(buffer); */
/*         double xScale = x; */
/*         double yScale = y; */
/*         assert(xScale > 0.0); */
/*         assert(yScale > 0.0); */

/*         for(int row = 0; row < rowCount; ++row) */
/*         { */
/*             double scaledY = yScale * row / rowCount; */
/*             for(int col = 0; col < colCount; ++col) */
/*                 noiseBuffer_set2D(buffer, row, col, rng31Perlin_sample(perlin, xScale * col / colCount, scaledY, z)); */
/*         } */
/*     } */
/*     else */
/*     { */
/*         int length = noiseBuffer_length(buffer); */
/*         double xScale = x; */
/*         assert(xScale > 0.0); */

/*         for(int index = 0; index < length; ++index) */
/*             noiseBuffer_set1D(buffer, index, rng31Perlin_sample(perlin, xScale * index / length, y, z)); */
/*     } */
/* } */

/* void rng31Perlin_layeredFill(RNG31_Perlin *perlin, NoiseBuffer *buffer, int layerCount, int layerScale, double signalAttenuation, double x, double y, double z) */
/* { */
/*     double signalFactor = 1.0 - signalAttenuation; */
/*     double signalStrength = 1.0; */

/*     if(noiseBuffer_is2D(buffer)) */
/*     { */
/*         int rowCount = noiseBuffer_height(buffer); */
/*         int colCount = noiseBuffer_width(buffer); */
/*         double xScale = x; */
/*         double yScale = y; */
/*         assert(xScale > 0.0); */
/*         assert(yScale > 0.0); */

/*         /\* First iteration: No additional scaling or signal attenuation *\/ */
/*         /\* Saves time with the multiplications in the first layer       *\/ */
/*         for(int row = 0; row < rowCount; ++row) */
/*         { */
/*             double scaledY = yScale * row / rowCount; */
/*             for(int col = 0; col < colCount; ++col) */
/*                 noiseBuffer_set2D(buffer, row, col, rng31Perlin_sample(perlin, xScale * col / colCount, scaledY, z)); */
/*         } */

/*         /\* The rest of the iterations *\/ */
/*         for(int iteration = 1; iteration < layerCount; ++iteration) */
/*         { */
/*             xScale *= layerScale; */
/*             yScale *= layerScale; */
/*             signalStrength *= signalFactor; */
/*             for(int row = 0; row < rowCount; ++row) */
/*             { */
/*                 double scaledY = yScale * row / rowCount; */
/*                 for(int col = 0; col < colCount; ++col) */
/*                     noiseBuffer_add2D(buffer, row, col, signalStrength * rng31Perlin_sample(perlin, xScale * col / colCount, scaledY, z)); */
/*             } */
/*         } */
/*     } */
/*     else */
/*     { */
/*         int length = noiseBuffer_length(buffer); */
/*         double xScale = x; */
/*         assert(xScale > 0.0); */

/*         /\* First iteration: No additional scaling or signal attenuation *\/ */
/*         /\* Saves time with the multiplications in the first layer       *\/ */
/*         for(int index = 0; index < length; ++index) */
/*             noiseBuffer_set1D(buffer, index, rng31Perlin_sample(perlin, xScale * index / length, y, z)); */

/*         /\* The rest of the iterations *\/ */
/*         for(int iteration = 1; iteration < layerCount; ++iteration) */
/*         { */
/*             xScale *= layerScale; */
/*             signalStrength *= signalFactor; */

/*             for(int index = 0; index < length; ++index) */
/*                 noiseBuffer_add1D(buffer, index, signalStrength * rng31Perlin_sample(perlin, xScale * index / length, y, z)); */
/*         } */
/*     } */
/* } */

/* Not exposed in header */
double rng31Perlin_sample(const RNG31_Perlin *perlin, double x, double y, double z)
{
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    double u = rng31Perlin_fade(perlin, x);
    double v = rng31Perlin_fade(perlin, y);
    double w = rng31Perlin_fade(perlin, z);

    int  A = perlin->permutations[X]+Y;
    int AA = perlin->permutations[A]+Z;
    int AB = perlin->permutations[A+1]+Z;
    int  B = perlin->permutations[X+1]+Y;
    int BA = perlin->permutations[B]+Z;
    int BB = perlin->permutations[B+1]+Z;

    return rng31Perlin_lerp(
        w, rng31Perlin_lerp(v, rng31Perlin_lerp(u, rng31Perlin_grad(perlin->permutations[AA  ], x  , y  , z   ),
                                                   rng31Perlin_grad(perlin->permutations[BA  ], x-1, y  , z   )),
                               rng31Perlin_lerp(u, rng31Perlin_grad(perlin->permutations[AB  ], x  , y-1, z   ),
                                                   rng31Perlin_grad(perlin->permutations[BB  ], x-1, y-1, z   ))),
           rng31Perlin_lerp(v, rng31Perlin_lerp(u, rng31Perlin_grad(perlin->permutations[AA+1], x  , y  , z-1 ),
                                                   rng31Perlin_grad(perlin->permutations[BA+1], x-1, y  , z-1 )),
                               rng31Perlin_lerp(u, rng31Perlin_grad(perlin->permutations[AB+1], x  , y-1, z-1 ),
                                                   rng31Perlin_grad(perlin->permutations[BB+1], x-1, y-1, z-1 ))));
}

double rng31Perlin_fade(const RNG31_Perlin *perlin, double t)
{
    return ease(t, perlin->easingMethod);
}

double rng31Perlin_lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

double rng31Perlin_grad(int hash, double x, double y, double z)
{
    int h = hash & 15;
    double u = h<8 ? x : y;
    double v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}
