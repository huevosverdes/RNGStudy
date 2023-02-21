from RNG31Core.AbstractRNG31Core import AbstractRNG31Core
from RNG31Core.LinearCongruential import LinearCongruential


class R250(AbstractRNG31Core):
    """
    Class for generating random numbers in [0, (2^31)-1]
    - http://faculty.uml.edu/jpropp/r250.c

    >>> rng = R250(-314159)
    >>> rng.next()
    1467021983
    >>> for count in range(133):
    ...     x = rng.next()
    >>> rng.next()
    224186363
    """

    def __init__(self, seed=0):
        self.__buffer = [0] * 250
        self.__index = 0
        super().__init__(seed)

    def _next(self):
        index = (self.__index - 147) if (self.__index >= 147) else (self.__index + 103)
        newRand = self.__buffer[self.__index] ^ self.__buffer[index]
        self.__buffer[self.__index] = newRand

        self.__index += 1
        if self.__index >= 250: # Increment pointer for next time
            self.__index = 0

        return newRand

    def _initialize(self):
        self.__index = 0

        # Fill r250 buffer with 31-bit random values
        lcg = LinearCongruential(self.initialSeed())
        for index in range(250):
            self.__buffer[index] = lcg.next()

        msb = 0x40000000  # Most-Significant-Bit: To turn on the diagonal bit
        mask = 0x7FFFFFFF # oTo turn off leftmost bits
        for index in range(31):
            k = 7 * index + 3        # Select a word to operate on
            self.__buffer[k] &= mask # Turn off bits left of the diagonal
            self.__buffer[k] |= msb  # Turn on the diagonal bit
            mask >>= 1
            msb >>= 1
