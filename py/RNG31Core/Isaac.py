from RNG31Core.AbstractRNG31Core import AbstractRNG31Core
from RNG31Core.LinearCongruential import LinearCongruential


class Isaac(AbstractRNG31Core):
    """
    Class for generating random numbers in [0, (2^31)-1]
    http://burtleburtle.net/bob/rand/isaac.html

    If seeded with LinearCongruential
    >>> rng = Isaac(-314159)
    >>> rng.next()
    232323904
    >>> for count in range(133):
    ...     x = rng.next()
    >>> rng.next()
    2140087090
    """

    ## If seeded with Zeros (remove the three lines using the LinearCongruential)
    ## This is useful if comparing to readable.c
    # >>> rng = Isaac(-314159)
    # >>> rng.next()
    # 1735250745
    # >>> for count in range(133):
    # ...     x = rng.next()
    # >>> rng.next()
    # 1603003720

    def __init__(self, seed=0):
        self.__buffer = [0] * 256
        self.__state = [0] * 256
        self.__aa = 0
        self.__bb = 0
        self.__cc = 0
        self.__index = 0
        super().__init__(seed)

    def _next(self):
        if self.__index > 255:
            self.__populate()

        result = self.__buffer[self.__index]
        self.__index += 1
        return result & 0x7FFFFFFF

    def _initialize(self):
        self.__buffer = [0] * 256
        self.__state = [0] * 256
        self.__aa = 0
        self.__bb = 0
        self.__cc = 0
        self.__index = 256

        a = 0x9e3779b9 # Golden Ratio
        b = a
        c = a
        d = a
        e = a
        f = a
        g = a
        h = a

        for index in range(4):
            (a, b, c, d, e, f, g, h) = Isaac.__mix(a, b, c, d, e, f, g, h)

        lcrng = LinearCongruential(self.initialSeed())
        for index in range(256):
            self.__buffer[index] = lcrng.next()

        for index in range(0, 256, 8):
            a = (a + self.__buffer[index  ]) & 0xFFFFFFFF
            b = (b + self.__buffer[index+1]) & 0xFFFFFFFF
            c = (c + self.__buffer[index+2]) & 0xFFFFFFFF
            d = (d + self.__buffer[index+3]) & 0xFFFFFFFF
            e = (e + self.__buffer[index+4]) & 0xFFFFFFFF
            f = (f + self.__buffer[index+5]) & 0xFFFFFFFF
            g = (g + self.__buffer[index+6]) & 0xFFFFFFFF
            h = (h + self.__buffer[index+7]) & 0xFFFFFFFF
            (a, b, c, d, e, f, g, h) = Isaac.__mix(a, b, c, d, e, f, g, h)
            self.__state[index  ] = a
            self.__state[index+1] = b
            self.__state[index+2] = c
            self.__state[index+3] = d
            self.__state[index+4] = e
            self.__state[index+5] = f
            self.__state[index+6] = g
            self.__state[index+7] = h

        for index in range(0, 256, 8):
            a = (a + self.__state[index  ]) & 0xFFFFFFFF
            b = (b + self.__state[index+1]) & 0xFFFFFFFF
            c = (c + self.__state[index+2]) & 0xFFFFFFFF
            d = (d + self.__state[index+3]) & 0xFFFFFFFF
            e = (e + self.__state[index+4]) & 0xFFFFFFFF
            f = (f + self.__state[index+5]) & 0xFFFFFFFF
            g = (g + self.__state[index+6]) & 0xFFFFFFFF
            h = (h + self.__state[index+7]) & 0xFFFFFFFF
            (a, b, c, d, e, f, g, h) = Isaac.__mix(a, b, c, d, e, f, g, h)
            self.__state[index  ] = a
            self.__state[index+1] = b
            self.__state[index+2] = c
            self.__state[index+3] = d
            self.__state[index+4] = e
            self.__state[index+5] = f
            self.__state[index+6] = g
            self.__state[index+7] = h

        self.__index = 256

    def __populate(self):
        self.__cc = self.__cc + 1         # cc just gets incremented once per 256 results
        self.__bb = self.__bb + self.__cc # then combined with bb

        for index in range(256):
            x = self.__state[index]
            choice = index % 4
            if choice == 0:
                self.__aa = self.__aa ^ ((self.__aa<<13) & 0xFFFFFFFF)
            elif choice == 1:
                self.__aa = self.__aa ^ (self.__aa>>6)
            elif choice == 2:
                self.__aa = self.__aa ^ ((self.__aa<<2) & 0xFFFFFFFF)
            elif choice == 3:
                self.__aa = self.__aa ^ (self.__aa>>16)

            self.__aa = (self.__state[(index+128)%256] + self.__aa) & 0xFFFFFFFF
            y  = (self.__state[(x>>2)%256] + self.__aa + self.__bb) & 0xFFFFFFFF
            self.__state[index] = y
            self.__bb = (self.__state[(y>>10)%256] + x) & 0xFFFFFFFF
            self.__buffer[index] = self.__bb

        self.__index = 0;

        # Note that bits 2..9 are chosen from x but 10..17 are chosen
        # from y.  The only important thing here is that 2..9 and 10..17
        # don't overlap.  2..9 and 10..17 were then chosen for speed in
        # the optimized version (rand.c)

    @staticmethod
    def __mix(a, b, c, d, e, f, g, h):
        a = (a ^ (b << 11)) & 0xFFFFFFFF
        d = (d + a)         & 0xFFFFFFFF
        b = (b + c)         & 0xFFFFFFFF
        b = (b ^ (c >> 2))  & 0xFFFFFFFF
        e = (e + b)         & 0xFFFFFFFF
        c = (c + d)         & 0xFFFFFFFF
        c = (c ^ (d << 8))  & 0xFFFFFFFF
        f = (f + c)         & 0xFFFFFFFF
        d = (d + e)         & 0xFFFFFFFF
        d = (d ^ (e >> 16)) & 0xFFFFFFFF
        g = (g + d)         & 0xFFFFFFFF
        e = (e + f)         & 0xFFFFFFFF
        e = (e ^ (f << 10)) & 0xFFFFFFFF
        h = (h + e)         & 0xFFFFFFFF
        f = (f + g)         & 0xFFFFFFFF
        f = (f ^ (g >> 4))  & 0xFFFFFFFF
        a = (a + f)         & 0xFFFFFFFF
        g = (g + h)         & 0xFFFFFFFF
        g = (g ^ (h << 8))  & 0xFFFFFFFF
        b = (b + g)         & 0xFFFFFFFF
        h = (h + a)         & 0xFFFFFFFF
        h = (h ^ (a >> 9))  & 0xFFFFFFFF
        c = (c + h)         & 0xFFFFFFFF
        a = (a + b)         & 0xFFFFFFFF
        return (a, b, c, d, e, f, g, h)
