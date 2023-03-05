#include "Image.h"

Image::Image(uint32_t width, uint32_t height)
{
    m_width = width;
    m_height = height;
    m_capacity = m_width * m_height;
    m_buffer = new Color[m_capacity];
}

Image::~Image()
{
    delete[] m_buffer;
}

uint32_t Image::width() const
{
    return m_width;
}

uint32_t Image::height() const
{
    return m_height;
}

Color Image::at(int row, int col) const
{
    assert(0 <= row && row < static_cast<int>(m_height));
    assert(0 <= col && col < static_cast<int>(m_width));
    return m_buffer[(((m_height - 1) - row) * m_width) + col];
}

void Image::set(int row, int col, Color c)
{
    assert(0 <= row && row < static_cast<int>(m_height));
    assert(0 <= col && col < static_cast<int>(m_width));
    m_buffer[(((m_height-1) - row) * m_width) + col] = c;
}

void Image::fill(Color c)
{
    for(uint32_t index = 0; index < m_capacity; ++index)
        m_buffer[index] = c;
}

void Image::write(FILE *outFile) const
{
    fwrite(m_buffer, sizeof(m_buffer[0]), m_capacity, outFile);
}
