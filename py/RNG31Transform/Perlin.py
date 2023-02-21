from RNG31Core.AbstractRNG31Core import AbstractRNG31Core
from RNG31Transform.Uniform import Uniform
from Ease import Ease

import math

class Perlin:
    """
    Class for filling a Noise buffer with Perlin Noise.
    - https://rosettacode.org/wiki/Perlin_noise#C

    >>> from GBFlip import GBFlip
    >>> gbFlip = GBFlip(-314159)
    >>> width = 1024
    >>> height = 768
    >>> noise = NoiseBuffer(width, height)
    >>> perlin = Perlin(gbFlip)

    >>> perlin.fill(noise, 4.0, 4.0)
    >>> noise.get(13, 135)
    -0.02643156728281086
    >>> noise.get(302, 624)
    -0.29384219406774975

    >>> noise.normalize()
    >>> noise.get(13, 135)
    0.4385588749276282
    >>> noise.get(302, 624)
    0.19374811203381082

    >>> perlin.layeredFill(noise, 3, 2.0, 0.5, 4.0, 4.0)
    >>> noise.get(13, 135)
    -0.06388842208354703
    >>> noise.get(302, 624)
    -0.34350851258237264

    >>> noise.normalize()
    >>> noise.get(13, 135)
    0.47554451798414726
    >>> noise.get(302, 624)
    0.2921388055178511
    """

    def __init__(self, rng: AbstractRNG31Core):
        assert(rng is not None and isinstance(rng, AbstractRNG31Core))
        self.__urng = Uniform(rng)
        self.__permutations = []
        self.__easingMethod = Ease.SMOOTHERSTEP
        self.reset()

    # def fill(self, noise: NoiseBuffer, x, y=0.0, z=0.0):
    #     assert(noise is not None and isinstance(noise, NoiseBuffer))
    #     if noise.is2D():
    #         rowCount = noise.height()
    #         colCount = noise.width()
    #         xScale = x
    #         yScale = y
    #         assert(xScale > 0.0)
    #         assert(yScale > 0.0)

    #         for row in range(rowCount):
    #             scaledY = yScale * row / rowCount
    #             for col in range(colCount):
    #                 noise.set(self.sample(xScale * col / colCount, scaledY, z), row, col)

    #     else:
    #         length = noise.length()
    #         xScale = x
    #         assert(xScale > 0.0)

    #         for index in range(length):
    #             noise.set(self.sample(xScale * index / length, y, z), index)

    # def layeredFill(self, noise: NoiseBuffer, layerCount, layerScale, signalAttenuation, x, y=0.0, z=0.0):
    #     assert(noise is not None and isinstance(noise, NoiseBuffer))
    #     signalFactor = 1.0 - signalAttenuation;
    #     signalStrength = 1.0;

    #     if noise.is2D():
    #         rowCount = noise.height()
    #         colCount = noise.width()
    #         xScale = x
    #         yScale = y
    #         assert(xScale > 0.0)
    #         assert(yScale > 0.0)

    #         # First iteration: No additional scaling or signal attenuation
    #         # Saves time with the multiplications in the first layer
    #         for row in range(rowCount):
    #             scaledY = yScale * row / rowCount
    #             for col in range(colCount):
    #                 noise.set(self.sample(xScale * col / colCount, scaledY, z), row, col)

    #         # The rest of the iterations
    #         for iteration in range(1, layerCount):
    #             xScale *= layerScale
    #             yScale *= layerScale
    #             signalStrength *= signalFactor
    #             for row in range(rowCount):
    #                 scaledY = yScale * row / rowCount
    #                 for col in range(colCount):
    #                     noise.add(signalStrength * self.sample(xScale * col / colCount, scaledY, z), row, col)

    #     else:
    #         length = noise.length()
    #         xScale = x
    #         assert(xScale > 0.0)

    #         # First iteration: No additional scaling or signal attenuation
    #         # Saves time with the multiplications in the first layer
    #         for index in range(length):
    #             noise.set(self.sample(xScale * index / length, y, z), index)

    #         # The rest of the iterations
    #         for iteration in range(1, layerCount):
    #             xScale *= layerScale;
    #             signalStrength *= signalFactor;
    #             for index in range(length):
    #                 noise.add(self.sample(xScale * index / length, y, z), index)

    def reset(self):
        self.__reset()
        self.__permutations += self.__permutations

    def shuffle(self):
        self.__reset()
        # TODO: Shuffle things here
        self.__permutations += self.__permutations

    def sample(self, x, y, z):
        X = int(math.floor(x)) & 255
        Y = int(math.floor(y)) & 255
        Z = int(math.floor(z)) & 255
        x -= math.floor(x)
        y -= math.floor(y)
        z -= math.floor(z)
        u = self.fade(x)
        v = self.fade(y)
        w = self.fade(z)

        A  = self.__permutations[X]+Y;
        AA = self.__permutations[A]+Z;
        AB = self.__permutations[A+1]+Z;
        B  = self.__permutations[X+1]+Y;
        BA = self.__permutations[B]+Z;
        BB = self.__permutations[B+1]+Z;

        return Perlin.lerp(
            w, Perlin.lerp(v, Perlin.lerp(u, Perlin.grad(self.__permutations[AA  ], x  , y  , z  ),
                                             Perlin.grad(self.__permutations[BA  ], x-1, y  , z  )),
                              Perlin.lerp(u, Perlin.grad(self.__permutations[AB  ], x  , y-1, z  ),
                                             Perlin.grad(self.__permutations[BB  ], x-1, y-1, z  ))),
               Perlin.lerp(v, Perlin.lerp(u, Perlin.grad(self.__permutations[AA+1], x  , y  , z-1),
                                             Perlin.grad(self.__permutations[BA+1], x-1, y  , z-1)),
                              Perlin.lerp(u, Perlin.grad(self.__permutations[AB+1], x  , y-1, z-1),
                                             Perlin.grad(self.__permutations[BB+1], x-1, y-1, z-1))));

    def fade(self, t):
        return Ease.ease(t, self.__easingMethod)

    @staticmethod
    def lerp(t, a, b):
        return a + t * (b - a)

    @staticmethod
    def grad(hashValue, x, y, z):
        h = hashValue & 15;
        u = x if h<8 else y
        v = y if h<4 else (x if h==12 or h==14 else z)
        return (u if (h&1) == 0 else -u) + (v if (h&2) == 0 else -v);

    def __reset(self):
        self.__permutations = [
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
            222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180]
