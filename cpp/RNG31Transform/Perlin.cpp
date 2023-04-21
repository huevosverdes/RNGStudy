#include "Perlin.h"

using namespace RNG31;

void perlin_swap_permutation(void *permutations, int index1, int index2);

const uint8_t Perlin::PERMUTATIONS[] = {
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

Perlin::Perlin(RNG31::Uniform *urng)
{
    m_urng = urng;
    m_easingMethod = Ease::EasingMethod::SMOOTHERSTEP;
    reset();
}

Perlin::~Perlin()
{

}

Ease::EasingMethod Perlin::getEasingMethod() const
{
    return m_easingMethod;
}

void Perlin::setEasingMethod(Ease::EasingMethod easingMethod)
{
    m_easingMethod = easingMethod;
}

void Perlin::reset()
{
    for(int index = 0; index < 256; ++index)
        m_permutations[index] = PERMUTATIONS[index];
    for(int index = 0; index < 256; ++index)
        m_permutations[index + 256] = m_permutations[index];
}

void Perlin::shuffle()
{
    // Shuffle the first half
    m_urng->shuffle(m_permutations, 256, &perlin_swap_permutation);

    // Copy first half to the second half
    for(int index = 0; index < 256; ++index)
        m_permutations[index + 256] = m_permutations[index];
}

void Perlin::fill(NoiseBuffer2D *buffer, double xScale, double yScale, double z) const
{
    uint32_t rowCount = buffer->height();
    uint32_t colCount = buffer->width();
    assert(xScale > 0.0);
    assert(yScale > 0.0);

    for(uint32_t row = 0; row < rowCount; ++row)
    {
        double scaledY = yScale * row / rowCount;
        for(uint32_t col = 0; col < colCount; ++col)
            buffer->set(row, col, sample(xScale * col / colCount, scaledY, z));
    }

    buffer->normalize();
}

void Perlin::layeredFill(NoiseBuffer2D *buffer, int layerCount, double layerScale, double signalAttenuation, double xScale, double yScale, double z) const
{
    double signalFactor = 1.0 - signalAttenuation;
    double signalStrength = 1.0;

    int rowCount = buffer->height();
    int colCount = buffer->width();
    assert(xScale > 0.0);
    assert(yScale > 0.0);

    // First iteration: No additional scaling or signal attenuation
    for(int row = 0; row < rowCount; ++row) {
        double scaledY = yScale * row / rowCount;
        for(int col = 0; col < colCount; ++col)
            buffer->set(row, col, sample(xScale * col / colCount, scaledY, z));
    }

    // The rest of the iterations
    for(int iteration = 1; iteration < layerCount; ++iteration) {
        xScale *= layerScale;
        yScale *= layerScale;
        signalStrength *= signalFactor;
        for(int row = 0; row < rowCount; ++row) {
            double scaledY = yScale * row / rowCount;
            for(int col = 0; col < colCount; ++col)
                buffer->set(row, col, buffer->at(row, col) + signalStrength * sample(xScale * col / colCount, scaledY, z));
        }
    }

    buffer->normalize();
}

double Perlin::sample(double x, double y, double z) const
{
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    int  A = m_permutations[X]+Y;
    int AA = m_permutations[A]+Z;
    int AB = m_permutations[A+1]+Z;
    int  B = m_permutations[X+1]+Y;
    int BA = m_permutations[B]+Z;
    int BB = m_permutations[B+1]+Z;

    return Perlin::lerp(
        w, Perlin::lerp(v, Perlin::lerp(u, Perlin::grad(m_permutations[AA  ], x  , y  , z   ),
                                           Perlin::grad(m_permutations[BA  ], x-1, y  , z   )),
                           Perlin::lerp(u, Perlin::grad(m_permutations[AB  ], x  , y-1, z   ),
                                           Perlin::grad(m_permutations[BB  ], x-1, y-1, z   ))),
           Perlin::lerp(v, Perlin::lerp(u, Perlin::grad(m_permutations[AA+1], x  , y  , z-1 ),
                                           Perlin::grad(m_permutations[BA+1], x-1, y  , z-1 )),
                           Perlin::lerp(u, Perlin::grad(m_permutations[AB+1], x  , y-1, z-1 ),
                                           Perlin::grad(m_permutations[BB+1], x-1, y-1, z-1 ))));
}

double Perlin::fade(double t) const
{
    return Ease::ease(t, m_easingMethod);
}

double Perlin::lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

double Perlin::grad(int hash, double x, double y, double z)
{
    int h = hash & 15;
    double u = h<8 ? x : y;
    double v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

// Just a helper function
void perlin_swap_permutation(void *permutations, int index1, int index2)
{
    uint8_t *p = (uint8_t*)permutations;
    uint8_t value1 = p[index1];

    p[index1] = p[index2];
    p[index2] = value1;
}
