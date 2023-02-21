from RNG31Core.AbstractRNG31Core import AbstractRNG31Core


class LinearCongruential(AbstractRNG31Core):
    """
    Class for generating random numbers in [0, (2^31)-1]
    https://en.wikipedia.org/wiki/Linear_congruential_generator

    >>> rng = LinearCongruential(-314159)
    >>> rng.next()
    1924356918
    >>> for count in range(133):
    ...    x = rng.next()
    >>> rng.next()
    437872528
    """

    A = 1103515245 # Increment
    C = 12345      # Multiplier
    M = 0x80000000 # Modulus

    def __init__(self, seed=0):
        self.__value = 0
        super().__init__(seed)

    def _next(self):
        self.__value = (
            (LinearCongruential.A * self.__value + LinearCongruential.C) %
            LinearCongruential.M)
        return self.__value

    def _initialize(self):
        self.__value = self.initialSeed()
