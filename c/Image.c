#include "Image.h"

Image *image_init(uint32_t width, uint32_t height)
{
    Image *result = (Image*)malloc(sizeof(Image));
    result->width = width;
    result->height = height;
    result->capacity = width * height;
    result->buffer = (Color*)malloc(sizeof(Color) * result->capacity);
    return result;
}

void image_destroy(Image *img)
{
    free(img->buffer);
    free(img);
}

Color image_colorAt(const Image *img, int row, int col)
{
    assert(0 <= row && row < (int)img->height);
    assert(0 <= col && col < (int)img->width);
    return img->buffer[(((img->height - 1) - row) * img->width) + col];
}

void image_fill(Image *img, Color c)
{
    for(uint32_t index = 0; index < img->capacity; ++index)
        img->buffer[index] = c;
}

void image_setPixel(Image *img, int row, int col, Color c)
{
    assert(0 <= row && row < (int)img->height);
    assert(0 <= col && col < (int)img->width);
    img->buffer[(((img->height-1) - row) * img->width) + col] = c;
}
