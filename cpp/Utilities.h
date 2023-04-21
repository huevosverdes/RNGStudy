#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <cstdio>
#include <cstdarg>
#include <cstring>

#include <chrono>
#include <thread>

#include "RNG31Core/AbstractRNGCore.h"
#include "RNG31Core/GBFlip.h"
#include "RNG31Core/Isaac.h"
#include "RNG31Core/LinearCongruential.h"
#include "RNG31Core/MersenneTwister.h"
#include "RNG31Core/R250.h"
#include "RNG31Core/R250_R521.h"

#include "Image.h"
#include "BMPWriter.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif /* M_PI */

int getUserInt(int low, int high, const char *prompt, ...);
double getUserFlt(double low, double high, const char *prompt, ...);
RNG31::AbstractRNGCore *getRNGCore();
void message(double timeout, const char *msg, ...);

void addSamplePoint(Image *img, int x, int y);
void writeBMPImage(Image *img, char *fileNameFormat, ...);

#endif /* __UTILITIES_H__ */
