from RNG31Core.AbstractRNG31Core import AbstractRNG31Core
from RNG31Core.LinearCongruential import LinearCongruential


class R250_R521(AbstractRNG31Core):
    """
    Class for generating random numbers in [0, (2^31)-1]
    - http://pythonlabtools.sourceforge.net/analysisdocs/html/a00152.html

    >>> rng = R250_R521(-314159)
    >>> rng.next()
    812580887
    >>> for count in range(133):
    ...     x = rng.next()
    >>> rng.next()
    56312995
    """

    def __init__(self, seed=0):
        self.__buffer250 = [0] * 250
        self.__buffer521 = [0] * 521
        self.__index250 = 0
        self.__index521 = 0
        super().__init__(seed)

    def _next(self):
        index = (self.__index250 - 147) if (self.__index250 >= 147) else (self.__index250 + 103)
        newRand250 = self.__buffer250[self.__index250] ^ self.__buffer250[index]
        self.__buffer250[self.__index250] = newRand250

        self.__index250 += 1
        if self.__index250 >= 250: # Increment pointer for next time
            self.__index250 = 0

        index = (self.__index521 - 353) if (self.__index521 >= 353) else (self.__index521 + 168)
        newRand521 = self.__buffer521[self.__index521] ^ self.__buffer521[index]
        self.__buffer521[self.__index521] = newRand521

        self.__index521 += 1
        if self.__index521 >= 521: # Increment pointer for next time
            self.__index521 = 0

        return newRand250 ^ newRand521

    def _initialize(self):
        self.__index250 = 0
        self.__index521 = 0

        # Fill r250 buffer with 31-bit random values
        lcg = LinearCongruential(self.initialSeed())
        for index in range(250):
            self.__buffer250[index] = lcg.next()
        for index in range(521):
            self.__buffer521[index] = lcg.next()

        msb = 0x40000000  # Most-Significant-Bit: To turn on the diagonal bit
        mask = 0x7FFFFFFF # To turn off leftmost bits
        for index in range(31):
            j = 7 * index + 3           # Select a word to operate on
            self.__buffer250[j] &= mask # Turn off bits left of the diagonal
            self.__buffer250[j] |= msb     # Turn on the diagonal bit

            j = 13 * index + 3
            self.__buffer521[j] &= mask # Turn off bits left of the diagonal
            self.__buffer521[j] |= msb     # Turn on the diagonal bit

            mask >>= 1
            msb >>= 1
