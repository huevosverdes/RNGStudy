from RNG31Core.AbstractRNG31Core import AbstractRNG31Core


class GBFlip(AbstractRNG31Core):
    """
    Class for generating random numbers in [0, (2^31)-1]
    https://tex.loria.fr/sgb/gb_flip.pdf

    >>> rng = GBFlip(-314159)
    >>> rng.next()
    119318998
    >>> for count in range(133):
    ...     x = rng.next()
    >>> rng.next()
    2081307921
    """

    # >>> from RNGUniform import RNGUniform
    # >>> urng = RNGUniform(rng)
    # >>> urng.next(0x55555555)
    # 748103812

    def __init__(self, seed=0):
        self.__array = [-1] * 56
        self.__index = 0
        super().__init__(seed)

    def _next(self):
        if self.__array[self.__index] >= 0:
            result = self.__array[self.__index]
            self.__index -= 1
            return result
        else:
            return self.__flip_cycle()

    def _initialize(self):
        currSeed = GBFlip.__mod_diff(self.initialSeed(), 0)
        prev = currSeed
        self.__array[55] = currSeed
        nxt = 1

        iterator = 1
        counter = ((21 * iterator) % 55)
        while counter:
            self.__array[counter] = nxt
            nxt = GBFlip.__mod_diff(prev, nxt)

            if currSeed & 1:
                currSeed = 0x40000000 | (currSeed >> 1)
            else:
                currSeed >>= 1
            nxt = GBFlip.__mod_diff(nxt, currSeed)
            prev = self.__array[counter]

            iterator += 1
            counter = ((21 * iterator) % 55)

        self.__flip_cycle()
        self.__flip_cycle()
        self.__flip_cycle()
        self.__flip_cycle()
        self.__flip_cycle()

    def __flip_cycle(self):
        for index in range(1, 56):
            self.__array[index] = GBFlip.__mod_diff(
                self.__array[index],
                self.__array[((index + 30) % 55) + 1])
        self.__index = 54
        return self.__array[55]

    @staticmethod
    def __mod_diff(x, y):
        return ((x - y) & 0x7fffffff)
