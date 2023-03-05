#include "BMPWriter.h"

void bmp_writeStr(FILE *f, const char *str);
void bmp_write16BitInt(FILE *f, int16_t value);
void bmp_write32BitInt(FILE *f, uint32_t value);

const int BMP_HEADER_SIZE = 14;
const int DIB_HEADER_SIZE = 108;

void bmp_write(const char *fileName, Image *image)
{
    FILE *outFile = fopen(fileName, "wb");
    if(outFile == NULL) {
        printf("ERROR: Could not open file \"%s\" for writing.\n", fileName);
    } else {
        // BMP Header
        bmp_writeStr(outFile, "BM"); // Magic Number
        // BMP File Size (bytes)
        bmp_write32BitInt(outFile, BMP_HEADER_SIZE + DIB_HEADER_SIZE + (image->width * 4 * image->height * 4));
        bmp_write16BitInt(outFile, 0); // Reserved
        bmp_write16BitInt(outFile, 0); // Reserved
        bmp_write32BitInt(outFile, BMP_HEADER_SIZE + DIB_HEADER_SIZE); // Address of Pixel Data (bytes)

        // DIB Header (BITMAPV4HEADER)
        bmp_write32BitInt(outFile, DIB_HEADER_SIZE); // DIB Header Size
        bmp_write32BitInt(outFile, image->width); // Pixel Width
        bmp_write32BitInt(outFile, image->height); // Pixel Height
        bmp_write16BitInt(outFile, 1); // Number of Color Planes
        bmp_write16BitInt(outFile, 32); // Bits per Pixel
        bmp_write32BitInt(outFile, BI_BITFIELDS); // Compression (None)
        bmp_write32BitInt(outFile, image->width * 4 * image->height * 4); // Bitmap Size (w*h in bytes)
        bmp_write32BitInt(outFile, 2835); // Print Resolution: Pixels/Meter Horizontal
        bmp_write32BitInt(outFile, 2835); // Print Resolution: Pixels/Meter Vertical
        bmp_write32BitInt(outFile, 0); // Number of colors in Palette
        bmp_write32BitInt(outFile, 0); // Number of important colors
        bmp_write32BitInt(outFile, 0x00FF0000); // Red channel bit mask
        bmp_write32BitInt(outFile, 0x0000FF00); // Grn channel bit mask
        bmp_write32BitInt(outFile, 0x000000FF); // Blu channel bit mask
        bmp_write32BitInt(outFile, 0xFF000000); // Alpha channel bit mask
        bmp_writeStr(outFile, "sRGB"); // Color Space
        bmp_write32BitInt(outFile, 0); // (36 bytes) Color Space Endpoints, unused for sRGB
        bmp_write32BitInt(outFile, 0);
        bmp_write32BitInt(outFile, 0);
        bmp_write32BitInt(outFile, 0);
        bmp_write32BitInt(outFile, 0);
        bmp_write32BitInt(outFile, 0);
        bmp_write32BitInt(outFile, 0);
        bmp_write32BitInt(outFile, 0);
        bmp_write32BitInt(outFile, 0);
        bmp_write32BitInt(outFile, 0); // Red Gamma Correction, unused for sRGB
        bmp_write32BitInt(outFile, 0); // Grn Gamma Correction, unused for sRGB
        bmp_write32BitInt(outFile, 0); // Blu Gamma Correction, unused for sRGB

        // Pixel data
        fwrite(image->buffer, sizeof(image->buffer[0]), image->capacity, outFile);

        fflush(outFile);
        fclose(outFile);
    }
}

void bmp_writeStr(FILE *f, const char *str)
{
    fwrite(str, sizeof(str[0]), strlen(str), f);
}

void bmp_write16BitInt(FILE *f, int16_t value)
{
    fwrite(&value, sizeof(value), 1, f);
}

void bmp_write32BitInt(FILE *f, uint32_t value)
{
    fwrite(&value, sizeof(value), 1, f);
}
