#include "BMPWriter.h"

void BMPWriter::write(const char *fileName, Image *image)
{
    FILE *outFile = fopen(fileName, "wb");
    if(outFile == nullptr) {
        std::cerr << "ERROR: Could not open file \"" << fileName << "\" for writing." << std::endl;
    } else {
        // BMP Header
        writeStr(outFile, "BM"); // Magic Number
        // BMP File Size (bytes)
        write32BitInt(outFile, BMP_HEADER_SIZE + DIB_HEADER_SIZE + (image->width() * 4 * image->height() * 4));
        write16BitInt(outFile, 0); // Reserved
        write16BitInt(outFile, 0); // Reserved
        write32BitInt(outFile, BMP_HEADER_SIZE + DIB_HEADER_SIZE); // Address of Pixel Data (bytes)

        // DIB Header (BITMAPV4HEADER)
        write32BitInt(outFile, DIB_HEADER_SIZE); // DIB Header Size
        write32BitInt(outFile, image->width()); // Pixel Width
        write32BitInt(outFile, image->height()); // Pixel Height
        write16BitInt(outFile, 1); // Number of Color Planes
        write16BitInt(outFile, 32); // Bits per Pixel
        write32BitInt(outFile, BI_BITFIELDS); // Compression (None)
        write32BitInt(outFile, image->width() * 4 * image->height() * 4); // Bitmap Size (w*h in bytes)
        write32BitInt(outFile, 2835); // Print Resolution: Pixels/Meter Horizontal
        write32BitInt(outFile, 2835); // Print Resolution: Pixels/Meter Vertical
        write32BitInt(outFile, 0); // Number of colors in Palette
        write32BitInt(outFile, 0); // Number of important colors
        write32BitInt(outFile, 0x00FF0000); // Red channel bit mask
        write32BitInt(outFile, 0x0000FF00); // Grn channel bit mask
        write32BitInt(outFile, 0x000000FF); // Blu channel bit mask
        write32BitInt(outFile, 0xFF000000); // Alpha channel bit mask
        writeStr(outFile, "sRGB"); // Color Space
        write32BitInt(outFile, 0); // (36 bytes) Color Space Endpoints, unused for sRGB
        write32BitInt(outFile, 0);
        write32BitInt(outFile, 0);
        write32BitInt(outFile, 0);
        write32BitInt(outFile, 0);
        write32BitInt(outFile, 0);
        write32BitInt(outFile, 0);
        write32BitInt(outFile, 0);
        write32BitInt(outFile, 0);
        write32BitInt(outFile, 0); // Red Gamma Correction, unused for sRGB
        write32BitInt(outFile, 0); // Grn Gamma Correction, unused for sRGB
        write32BitInt(outFile, 0); // Blu Gamma Correction, unused for sRGB

        image->write(outFile);
        fflush(outFile);
        fclose(outFile);
    }
}

void BMPWriter::writeStr(FILE *f, const char *str)
{
    fwrite(str, sizeof(str[0]), strlen(str), f);
}

void BMPWriter::write16BitInt(FILE *f, int16_t value)
{
    fwrite(&value, sizeof(value), 1, f);
}

void BMPWriter::write32BitInt(FILE *f, uint32_t value)
{
    fwrite(&value, sizeof(value), 1, f);
}
