#ifndef __BMP_WRITER_H__
#define __BMP_WRITER_H__

#include <cstdio>
#include <cstring>

#include "Image.h"

class BMPWriter
{
    // https://en.wikipedia.org/wiki/BMP_file_format

public:
    static void write(const char *fileName, Image *image);

private:
    enum Compression {
        BI_RGB = 0,            // Compression: none                          Comments: Most common
        BI_RLE8 = 1,           // Compression: RLE 8-bit/pixel               Comments: Can be used only with 8-bit/pixel bitmaps
        BI_RLE4 = 2,           // Compression: RLE 4-bit/pixel               Comments: Can be used only with 4-bit/pixel bitmaps
        BI_BITFIELDS = 3,      // Compression: OS22XBITMAPHEADER: Huffman 1D Comments: BITMAPV2INFOHEADER: RGB bit field masks, BITMAPV3INFOHEADER+: RGBA
        BI_JPEG = 4,           // Compression: OS22XBITMAPHEADER: RLE-24     Comments: BITMAPV4INFOHEADER+: JPEG image for printing[14]
        BI_PNG = 5,            // Compression: PNG                           Comments: BITMAPV4INFOHEADER+: PNG image for printing[14]
        BI_ALPHABITFIELDS = 6, // Compression: RGBA bit field masks          Comments: only Windows CE 5.0 with .NET 4.0 or later
        BI_CMYK = 11,	       // Compression: none                          Comments: only Windows Metafile CMYK[4]
        BI_CMYKRLE8 = 12,      // Compression: RLE-8                         Comments: only Windows Metafile CMYK
        BI_CMYKRLE4 = 13       // Compression: RLE-4                         Comments: only Windows Metafile CMYK
    };

    static void writeStr(FILE *f, const char *str);
    static void write16BitInt(FILE *f, int16_t value);
    static void write32BitInt(FILE *f, uint32_t value);

    static const int BMP_HEADER_SIZE = 14;
    static const int DIB_HEADER_SIZE = 108;
};

#endif /* #ifndef __BMP_WRITER_H__ */
