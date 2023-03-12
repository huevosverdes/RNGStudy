from RNG31Core.AbstractRNG31Core import AbstractRNG31Core


class MersenneTwister(AbstractRNG31Core):
    """
    Class for generating random numbers in [0, (2^31)-1]
    - https://en.wikipedia.org/wiki/Mersenne_Twister
    - http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/mt.pdf
    - https://create.stephan-brumme.com/mersenne-twister/

    >>> rng = MersenneTwister(-314159)
    >>> rng.next()
    1925283223
    >>> for count in range(133):
    ...    x = rng.next()
    >>> rng.next()
    1908426989
    """

    # MT19937
    __W = 32         # W: word size (in number of bits)
    __N = 624        # N: degree of recurrence
    __M = 397        # M: middle word, offset for recurrence relation defining series [1, n)
    __R = 31         # R: number of bits of lower bitmask, [0, w)
    __A = 0x9908B0DF # A: coefficients of rational normal form twist matrix
    __U = 11         # U, d, l: additional Mersenne Twister tempering bit shifts/masks
    __D = 0xFFFFFFFF
    __S = 7          # S, t: TGFSR(R) tempering bit shifts
    __B = 0x9D2C5680 # B, c: TGFSR(R) tempering bitmasks
    __T = 15
    __C = 0xEFC60000
    __L = 18
    __F = 0x6C078965 # F: initialization parameter
    __MASK       = 0xFFFFFFFF # Mask 32 bit, since Python goes bigger
    __LOWER_MASK = 0x7FFFFFFF # (1 << R) - 1
    __UPPER_MASK = 0x80000000 # lowest W bits of ~LOWER_MASK

    def __init__(self, seed=0):
        self.__buffer = [0] * MersenneTwister.__N
        self.__index = MersenneTwister.__N
        super().__init__(seed & MersenneTwister.__MASK)

    def _next(self):
        if self.__index >= MersenneTwister.__N:
            self.__twist()

        y = self.__buffer[self.__index]
        y ^= (y >> MersenneTwister.__U) & MersenneTwister.__D
        y ^= (y << MersenneTwister.__S) & MersenneTwister.__B
        y ^= (y << MersenneTwister.__T) & MersenneTwister.__C
        y ^= (y >> MersenneTwister.__L)
        self.__index += 1

        return (MersenneTwister.__LOWER_MASK & y) # Only 31 bits

    def _initialize(self):
        self.__index = MersenneTwister.__N
        self.__buffer[0] = self.initialSeed()
        for index in range(1, MersenneTwister.__N):
            v = self.__buffer[index - 1]
            self.__buffer[index] = MersenneTwister.__MASK & (
                MersenneTwister.__F *
                (v ^ (v >> (MersenneTwister.__W - 2))) +
                index)

    def __twist(self):
        for index in range(MersenneTwister.__N):
            x = ((self.__buffer[index] & MersenneTwister.__UPPER_MASK) +
                 (self.__buffer[(index + 1) % MersenneTwister.__N] & MersenneTwister.__LOWER_MASK))
            xA = x >> 1
            if x & 0x1:
                xA ^= MersenneTwister.__A
            self.__buffer[index] = self.__buffer[(index + MersenneTwister.__M) % MersenneTwister.__N] ^ xA
        self.__index = 0
