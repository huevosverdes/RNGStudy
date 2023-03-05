#ifndef __NOISEBUFFER2D_H__
#define __NOISEBUFFER2D_H__

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t capacity;
    double *buffer;
} NoiseBuffer2D;

NoiseBuffer2D *noiseBuffer2D_init(uint32_t width, uint32_t height);
void noiseBuffer2D_destroy(NoiseBuffer2D *buff);

double noiseBuffer2D_valueAt(const NoiseBuffer2D *buff, int row, int col);
void noiseBuffer2D_setValue(NoiseBuffer2D *buff, int row, int col, double value);

void noiseBuffer2D_fill(NoiseBuffer2D *buff, double value);
void noiseBuffer2D_normalize(NoiseBuffer2D *buff);
void noiseBuffer2D_scale(NoiseBuffer2D *buff, double value);
void noiseBuffer2D_offset(NoiseBuffer2D *buff, double value);
void noiseBuffer2D_add(NoiseBuffer2D *buff1, NoiseBuffer2D *buff2);

#endif /* __NOISEBUFFER2D_H__ */
