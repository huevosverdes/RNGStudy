#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "Color.h"

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t capacity;
    Color *buffer;
} Image;

Image *image_init(uint32_t width, uint32_t height);
void image_destroy(Image *img);

Color image_colorAt(const Image *img, int row, int col);

void image_fill(Image *img, Color c);
void image_setPixel(Image *img, int row, int col, Color c);

#endif /* #ifndef __IMAGE__ */
