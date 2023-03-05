#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <cassert>
#include <cstdint>
#include <iostream>

#include "Color.h"

class Image
{

public:
    Image(uint32_t width, uint32_t height);
    ~Image();

    uint32_t width() const;
    uint32_t height() const;

    Color at(int row, int col) const;
    void fill(Color c=Color());

    void set(int row, int col, Color c);

    void write(FILE *outFile) const;

private:
    uint32_t m_capacity;
    uint32_t m_width;
    uint32_t m_height;
    Color *m_buffer;
};

#endif /* #ifndef __IMAGE_H__ */
