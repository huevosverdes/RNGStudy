#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "RNG31Core/AbstractRNG31Core.h"
#include "RNG31Core/RNG31Core_GBFlip.h"
#include "RNG31Core/RNG31Core_Isaac.h"
#include "RNG31Core/RNG31Core_LinearCongruential.h"
#include "RNG31Core/RNG31Core_MersenneTwister.h"
#include "RNG31Core/RNG31Core_R250.h"
#include "RNG31Core/RNG31Core_R250_R521.h"

#include "Image.h"
#include "BMPWriter.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif /* M_PI */

int getUserInt(int low, int high, const char *prompt, ...);
double getUserFlt(double low, double high, const char *prompt, ...);
AbstractRNG31Core *getRNGCore();
void message(double timeout, const char *msg, ...);

void addSamplePoint(Image *img, int x, int y);
void writeBMPImage(Image *img, char *fileNameFormat, ...);

#endif /* __UTILITIES_H__ */
