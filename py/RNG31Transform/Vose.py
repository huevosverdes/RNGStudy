from collections import deque

from RNG31Core.AbstractRNG31Core import AbstractRNG31Core
from RNG31Transform.RNGUniform import RNGUniform


class RNGVose:
    """
    Class for returning weighted discrete values

    Technical Explanation: http://web.eecs.utk.edu/~vose/Publications/random.pdf
    Practical Explanation: http://www.keithschwarz.com/darts-dice-coins/

    >>> from GBFlip import GBFlip
    >>> gbFlip = GBFlip(-314159)
    >>> for _ in range(134):
    ...     _ = gbFlip.next()
    >>> vrng = RNGVose(gbFlip, 3, 6, 1, 1, 1)
    >>> vrng.next()
    1
    >>> vrng.next()
    3
    """

    def __init__(self, rng: AbstractRNG31Core, *probabilities):
        assert(rng is not None and isinstance(rng, AbstractRNG31Core))

        # Normalize
        # - sum(probabilities) is always 1.0
        # - each probability is in [0.0, 1.0]
        total = float(sum(probabilities))
        probabilities = [(p / total) for p in probabilities]

        self.__n = len(probabilities)
        avg = 1.0 / self.__n
        small = deque([])
        large = deque([])

        self.__alias = [0.0] * self.__n
        self.__prob = [0.0] * self.__n
        self.__rng = RNGUniform(rng)

        for index in range(self.__n):
            if probabilities[index] >= avg:
                large.append(index)
            else:
                small.append(index)

        while small and large:
            less = small.popleft()
            more = large.popleft()

            self.__prob[less] = probabilities[less] * self.__n
            self.__alias[less] = more

            probabilities[more] = (probabilities[more] +
                                   probabilities[less]) - avg

            if probabilities[more] >= avg:
                large.append(more)
            else:
                small.append(more)

        while small:
            self.__prob[small.popleft()] = 1.0
        while large:
            self.__prob[large.popleft()] = 1.0

    def next(self):
        col = self.__rng.next(self.__n)
        if self.__rng.nextFloat() < self.__prob[col]:
            result = col
        else:
            result = self.__alias[col]
        return result
