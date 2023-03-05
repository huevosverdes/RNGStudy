class NoiseBuffer2D:

    def __init__(self, width, height):
        self._width = width
        self._height = height
        self._capacity = width * height
        self._buffer = [0.0] * self._capacity

    def width(self):
        return self._width

    def height(self):
        return self._height

    def at(self, row, col):
        assert(0 <= row and row < int(self._height))
        assert(0 <= col and col < int(self._width))
        return self._buffer[(((self._height - 1) - int(row)) * self._width) + int(col)]

    def set(self, row, col, value):
        assert(0 <= row and row < int(self._height))
        assert(0 <= col and col < int(self._width))
        self._buffer[(((self._height-1) - int(row)) * self._width) + int(col)] = value

    def fill(self, value):
        for index in range(self._capacity):
            self._buffer[index] = value

    def normalize(self):
        low = min(self._buffer)
        high = max(self._buffer)

        self -= low
        self /= (high - low)

    def __iadd__(self, other):
        # += Operator
        if isinstance(other, NoiseBuffer2D):
            assert(self._width == other.self._width)
            assert(self._height == other.self._height)
            for index in range(self._capacity):
                self._buffer[index] += other.self._buffer[index]
        else:
            assert(isinstance(other, (int, float)))
            for index in range(self._capacity):
                self._buffer[index] += other
        return self

    def __isub__(self, other):
        # -= Operator
        if isinstance(other, NoiseBuffer2D):
            assert(self._width == other.self._width)
            assert(self._height == other.self._height)
            for index in range(self._capacity):
                self._buffer[index] -= other.self._buffer[index]
        else:
            assert(isinstance(other, (int, float)))
            for index in range(self._capacity):
                self._buffer[index] -= other
        return self

    def __imul__(self, factor):
        # *= Operator
        for index in range(self._capacity):
            self._buffer[index] *= factor
        return self

    def __itruediv__(self, factor):
        # /= Operator
        for index in range(self._capacity):
            self._buffer[index] /= factor
        return self
