from Color import Color

import struct

class Image:

    def __init__(self, width, height):
        self._width = width
        self._height = height
        self._capacity = width * height
        self._buffer = [Color(0, 0, 0, 255)] * self._capacity

    def width(self):
        return self._width

    def height(self):
        return self._height

    def at(self, row, col):
        assert(0 <= row and row < int(self._height));
        assert(0 <= col and col < int(self._width));
        return self._buffer[(((self._height - 1) - row) * self._width) + col];

    def set(self, row, col, color):
        assert(0 <= row and row < int(self._height));
        assert(0 <= col and col < int(self._width));
        self._buffer[(((self._height-1) - row) * self._width) + col] = color;

    def fill(self, color):
        for c in self._buffer:
            c._color = color._color

    def write(self, outFile):
        tmpBuffer = bytes("", encoding="latin_1")
        for c in self._buffer:
            outFile.write(struct.pack("<I", c._color))
