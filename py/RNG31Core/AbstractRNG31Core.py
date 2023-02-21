import time


class AbstractRNG31Core:
    """
    Abstract base class for generating random numbers in [0, 2^31 - 1].
    - Implement _initialize() to set up the initial state. This is called by reseed().
    - Implement _next(). This must generate a number in the range above.
    """

    MAX = 0x7FFFFFFF

    def __init__(self, seed=0):
        self.__initialSeed = 0

        self.reseed(seed)

    def _initialize(self):
        raise NotImplementedError

    def _next(self):
        raise NotImplementedError

    def next(self):
        result = self._next()
        assert(0 <= result and result <= AbstractRNG31Core.MAX)
        return result

    def reseed(self, seed):
        if seed == 0:
            seed = int(time.time())
        self.__initialSeed = seed
        self._initialize()

    def initialSeed(self):
        return self.__initialSeed
