#include "NoiseBuffer2D.h"

NoiseBuffer2D *noiseBuffer2D_init(uint32_t width, uint32_t height)
{
    NoiseBuffer2D *result = (NoiseBuffer2D*)malloc(sizeof(NoiseBuffer2D));
    result->width = width;
    result->height = height;
    result->capacity = width * height;
    result->buffer = (double*)malloc(sizeof(double) * result->capacity);
    return result;
}

void noiseBuffer2D_destroy(NoiseBuffer2D *buff)
{
    free(buff->buffer);
    free(buff);
}

double noiseBuffer2D_valueAt(const NoiseBuffer2D *buff, int row, int col)
{
    assert(0 <= row && row < (int)buff->height);
    assert(0 <= col && col < (int)buff->width);
    return buff->buffer[(((buff->height - 1) - row) * buff->width) + col];
}

void noiseBuffer2D_setValue(NoiseBuffer2D *buff, int row, int col, double value)
{
    assert(0 <= row && row < (int)buff->height);
    assert(0 <= col && col < (int)buff->width);
    buff->buffer[(((buff->height-1) - row) * buff->width) + col] = value;
}

void noiseBuffer2D_fill(NoiseBuffer2D *buff, double value)
{
    for(uint32_t index = 0; index < buff->capacity; ++index)
        buff->buffer[index] = value;
}

void noiseBuffer2D_normalize(NoiseBuffer2D *buff)
{
    double min = buff->buffer[0];
    double max = min;
    for(int index = 1; index < buff->capacity; ++index) {
        double value = buff->buffer[index];
        if(value < min) min = value;
        if(value > max) max = value;
    }
    noiseBuffer2D_offset(buff, -min);
    noiseBuffer2D_scale(buff, 1.0 / (max - min));
}

void noiseBuffer2D_scale(NoiseBuffer2D *buff, double value)
{
    for(int index = 0; index < buff->capacity; ++index)
        buff->buffer[index] *= value;
}

void noiseBuffer2D_offset(NoiseBuffer2D *buff, double value)
{
    for(int index = 0; index < buff->capacity; ++index)
        buff->buffer[index] += value;
}

void noiseBuffer2D_add(NoiseBuffer2D *buff1, NoiseBuffer2D *buff2)
{
    assert(buff1->width == buff2->width);
    assert(buff1->height == buff2->height);
    for(int index = 0; index < buff1->capacity; ++index)
        buff1->buffer[index] += buff2->buffer[index];
}
