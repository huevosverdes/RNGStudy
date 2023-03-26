import math

from RNG31Core.AbstractRNG31Core import AbstractRNG31Core


class Uniform:
    """
    Class for returning values in a uniform range

    >>> from GBFlip import GBFlip
    >>> gbFlip = GBFlip(-314159)
    >>> for _ in range(134):
    ...     _ = gbFlip.next()
    >>> urng = Uniform(gbFlip)
    >>> urng.next(0x55555555)
    748103812
    >>> urng.coinFlip()
    False
    >>> abs(urng.nextFloat() - 0.288) < 0.001
    True
    >>> urng.pointInCircle(1.5)
    (-0.048737006221392085, -0.2857889129740501)
    >>> urng.shuffle([1, 2, 3, 4, 5, 6])
    [2, 5, 1, 3, 6, 4]
    """

    def __init__(self, rng: AbstractRNG31Core):
        assert(rng is not None and isinstance(rng, AbstractRNG31Core))
        self.__rng = rng
        self.__coinValue = None
        self.__coinMask = 0x0

    def next(self, minimum=None, maximum=None):
        if minimum is None and maximum is None:
            return self.__rng.next()
        elif minimum is not None and maximum is None:
            top = minimum
            low = 0
        else:
            top = maximum - minimum
            low = minimum

        r = t = 0x80000000 - (0x80000000 % top)
        while r >= t:
            r = self.next()
        return (r % top) + low

    def nextFloat(self, minimum=None, maximum=None):
        v = self.__rng.next() / float(0x80000000)

        if minimum is None and maximum is None:
            pass
        elif minimum is not None and maximum is None:
            v *= minimum
        else:
            v *= (maximum - minimum)
            v += minimum

        return v

    def pointInCircle(self, radius):
        # https://programming.guide/random-point-within-circle.html
        assert(radius > 0.0)
        angle = self.nextFloat() * 2.0 * math.pi
        r = radius * math.sqrt(self.nextFloat())
        return (r * math.cos(angle), r * math.sin(angle))

    def shuffle(self, container: list):
        # https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
        # https://www.rosettacode.org/wiki/Knuth_shuffle
        assert(container and type(container) == list)
        for index in reversed(range(1, len(container))):
            swapIndex = self.next(index)
            temp = container[index]
            container[index] = container[swapIndex]
            container[swapIndex] = temp
        return container

    def coinFlip(self):
        if self.__coinMask <= 0:
            self.__coinValue = self.__rng.next()
            self.__coinMask = 0x80000000
        self.__coinMask >>= 1
        return (self.__coinMask & self.__coinValue) != 0
