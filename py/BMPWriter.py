import struct

from Image import Image

BMP_HEADER_SIZE = 14
DIB_HEADER_SIZE = 108

COMPRESSION_BI_RGB            = 0  # none                          : Most common
COMPRESSION_BI_RLE8           = 1  # RLE 8-bit/pixel               : Can be used only with 8-bit/pixel bitmaps
COMPRESSION_BI_RLE4           = 2  # RLE 4-bit/pixel               : Can be used only with 4-bit/pixel bitmaps
COMPRESSION_BI_BITFIELDS      = 3  # OS22XBITMAPHEADER: Huffman 1D : BITMAPV2INFOHEADER: RGB bit field masks, BITMAPV3INFOHEADER+: RGBA
COMPRESSION_BI_JPEG           = 4  # OS22XBITMAPHEADER: RLE-24     : BITMAPV4INFOHEADER+: JPEG image for printing[14]
COMPRESSION_BI_PNG            = 5  # PNG                           : BITMAPV4INFOHEADER+: PNG image for printing[14]
COMPRESSION_BI_ALPHABITFIELDS = 6  # RGBA bit field masks          : only Windows CE 5.0 with .NET 4.0 or later
COMPRESSION_BI_CMYK           = 11 # none                          : only Windows Metafile CMYK[4]
COMPRESSION_BI_CMYKRLE8       = 12 # RLE-8                         : only Windows Metafile CMYK
COMPRESSION_BI_CMYKRLE4       = 13 # RLE-4                         : only Windows Metafile CMYK


class BMPWriter:
    # https://en.wikipedia.org/wiki/BMP_file_format

    @staticmethod
    def write(fileName, image):
        with open(fileName, "wb") as outFile:
            # BMP Header
            BMPWriter.__writeStr(outFile, "BM") # Magic Number
            # BMP File Size (bytes)
            BMPWriter.__write32BitInt(outFile, BMP_HEADER_SIZE + DIB_HEADER_SIZE + (image.width() * 4 * image.height() * 4))
            BMPWriter.__write16BitInt(outFile, 0) # Reserved
            BMPWriter.__write16BitInt(outFile, 0) # Reserved
            BMPWriter.__write32BitInt(outFile, BMP_HEADER_SIZE + DIB_HEADER_SIZE) # Address of Pixel Data (bytes)

            # DIB Header (BITMAPV4HEADER)
            BMPWriter.__write32BitInt(outFile, DIB_HEADER_SIZE) # DIB Header Size
            BMPWriter.__write32BitInt(outFile, image.width()) # Pixel Width
            BMPWriter.__write32BitInt(outFile, image.height()) # Pixel Height
            BMPWriter.__write16BitInt(outFile, 1) # Number of Color Planes
            BMPWriter.__write16BitInt(outFile, 32) # Bits per Pixel
            BMPWriter.__write32BitInt(outFile, COMPRESSION_BI_BITFIELDS) # Compression (None)
            BMPWriter.__write32BitInt(outFile, image.width() * 4 * image.height() * 4) # Bitmap Size (w*h in bytes)
            BMPWriter.__write32BitInt(outFile, 2835) # Print Resolution: Pixels/Meter Horizontal
            BMPWriter.__write32BitInt(outFile, 2835) # Print Resolution: Pixels/Meter Vertical
            BMPWriter.__write32BitInt(outFile, 0) # Number of colors in Palette
            BMPWriter.__write32BitInt(outFile, 0) # Number of important colors
            BMPWriter.__write32BitInt(outFile, 0x00FF0000) # Red channel bit mask
            BMPWriter.__write32BitInt(outFile, 0x0000FF00) # Grn channel bit mask
            BMPWriter.__write32BitInt(outFile, 0x000000FF) # Blu channel bit mask
            BMPWriter.__write32BitInt(outFile, 0xFF000000) # Alpha channel bit mask
            BMPWriter.__writeStr(outFile, "sRGB") # Color Space
            BMPWriter.__write32BitInt(outFile, 0) # (36 bytes) Color Space Endpoints, unused for sRGB
            BMPWriter.__write32BitInt(outFile, 0)
            BMPWriter.__write32BitInt(outFile, 0)
            BMPWriter.__write32BitInt(outFile, 0)
            BMPWriter.__write32BitInt(outFile, 0)
            BMPWriter.__write32BitInt(outFile, 0)
            BMPWriter.__write32BitInt(outFile, 0)
            BMPWriter.__write32BitInt(outFile, 0)
            BMPWriter.__write32BitInt(outFile, 0)
            BMPWriter.__write32BitInt(outFile, 0) # Red Gamma Correction, unused for sRGB
            BMPWriter.__write32BitInt(outFile, 0) # Grn Gamma Correction, unused for sRGB
            BMPWriter.__write32BitInt(outFile, 0) # Blu Gamma Correction, unused for sRGB

            image.write(outFile)

    @staticmethod
    def __writeStr(outFile, text):
        outFile.write(bytes(text, encoding="latin_1"))

    @staticmethod
    def __write16BitInt(outFile, value):
        outFile.write(struct.pack("<H", value))

    @staticmethod
    def __write32BitInt(outFile, value):
        outFile.write(struct.pack("<I", value))
