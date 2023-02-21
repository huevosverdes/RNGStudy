import math

from RNG31Core.AbstractRNG31Core import AbstractRNG31Core
from RNG31Transform.Uniform import Uniform


class RNGNormal:
    """
    Class for returning values in a uniform distribution
    - mean = 0.0
    - standard deviation = 1.0

    ftp://taygeta.com/pub/c/boxmuller.c

    >>> from GBFlip import GBFlip
    >>> gbFlip = GBFlip(-314159)
    >>> for _ in range(134):
    ...     _ = gbFlip.next()
    >>> nrng = RNGNormal(gbFlip)
    >>> abs(nrng.next(2.0, 1.0) - 3.656) < 0.001
    True
    """

    def __init__(self, rng: AbstractRNG31Core):
        assert(rng is not None and isinstance(rng, AbstractRNG31Core))
        self.__urng = Uniform(rng)
        self.__cached = None

    def next(self, stdDev=1.0, mean=0.0):
        if self.__cached is not None:
            y1 = self.__cached
            self.__cached = None
        else:
            while True:
                x1 = self.__urng.nextFloat(-1.0, 1.0)
                x2 = self.__urng.nextFloat(-1.0, 1.0)
                w = (x1 * x1) + (x2 * x2)
                if w < 1.0:
                    break
            w = math.sqrt((-2.0 * math.log(w)) / w)
            y1 = x1 * w
            self.__cached = x2 * w

        return (stdDev * y1) + mean
