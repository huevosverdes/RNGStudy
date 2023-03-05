#include "NoiseBuffer2D.h"

NoiseBuffer2D::NoiseBuffer2D(uint32_t width, uint32_t height)
{
    m_width = width;
    m_height = height;
    m_capacity = width * height;
    m_buffer = new double[m_capacity];
}

NoiseBuffer2D::~NoiseBuffer2D()
{
    delete m_buffer;
}

uint32_t NoiseBuffer2D::width() const
{
    return m_width;
}

uint32_t NoiseBuffer2D::height() const
{
    return m_height;
}

double NoiseBuffer2D::at(int row, int col)
{
    assert(0 <= row && row < (int)m_height);
    assert(0 <= col && col < (int)m_width);
    return m_buffer[(((m_height - 1) - row) * m_width) + col];
}

void NoiseBuffer2D::set(int row, int col, double value)
{
    assert(0 <= row && row < (int)m_height);
    assert(0 <= col && col < (int)m_width);
    m_buffer[(((m_height-1) - row) * m_width) + col] = value;
}

void NoiseBuffer2D::fill(double value)
{
    for(uint32_t index = 0; index < m_capacity; ++index)
        m_buffer[index] = value;
}

void NoiseBuffer2D::normalize()
{
    double min = m_buffer[0];
    double max = min;
    for(int index = 1; index < (int)m_capacity; ++index) {
        double value = m_buffer[index];
        if(value < min) min = value;
        if(value > max) max = value;
    }

    (*this) -= min;
    (*this) /= (max - min);
}

void NoiseBuffer2D::operator+=(const NoiseBuffer2D &other)
{
    assert(m_width == other.m_width);
    assert(m_height == other.m_height);
    for(uint32_t index = 0; index < m_capacity; ++index)
        m_buffer[index] += other.m_buffer[index];
}

void NoiseBuffer2D::operator+=(double value)
{
    for(uint32_t index = 0; index < m_capacity; ++index)
        m_buffer[index] += value;
}

void NoiseBuffer2D::operator-=(double value)
{
    for(uint32_t index = 0; index < m_capacity; ++index)
        m_buffer[index] -= value;
}

void NoiseBuffer2D::operator*=(double factor)
{
    for(uint32_t index = 0; index < m_capacity; ++index)
        m_buffer[index] *= factor;
}

void NoiseBuffer2D::operator/=(double factor)
{
    for(uint32_t index = 0; index < m_capacity; ++index)
        m_buffer[index] /= factor;
}
