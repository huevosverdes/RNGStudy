#ifndef __NOISEBUFFER2D_H__
#define __NOISEBUFFER2D_H__

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

class NoiseBuffer2D {
public:
    NoiseBuffer2D(uint32_t width, uint32_t height);
    ~NoiseBuffer2D();

    uint32_t width() const;
    uint32_t height() const;
    double at(int row, int col);
    void set(int row, int col, double value);

    void fill(double value);
    void normalize();
    void operator+=(const NoiseBuffer2D &other);
    void operator+=(double offset);
    void operator-=(double offset);
    void operator*=(double factor);
    void operator/=(double factor);

private:
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_capacity;
    double *m_buffer;
};

#endif /* __NOISEBUFFER2D_H__ */
