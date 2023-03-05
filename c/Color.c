#include "Color.h"

const int RED_BYTE = 2;
const int GRN_BYTE = 1;
const int BLU_BYTE = 0;
const int ALPHA_BYTE = 3;

const Color COLOR_WHT = {0xFFFFFFFF};
const Color COLOR_GRY = {0xFF999999};
const Color COLOR_BLK = {0xFF000000};
const Color COLOR_RED = {0xFFFF0000};
const Color COLOR_ORG = {0xFFFF9900};
const Color COLOR_YLW = {0xFFFFFF00};
const Color COLOR_GRN = {0xFF00FF00};
const Color COLOR_BLU = {0xFF0000FF};
const Color COLOR_PUR = {0xFF880088};

uint8_t color_intify(double value);

double color_redF(const Color *c)
{
    return c->bytes[RED_BYTE] / 255.0;
}

double color_grnF(const Color *c)
{
    return c->bytes[GRN_BYTE] / 255.0;
}

double color_bluF(const Color *c)
{
    return c->bytes[BLU_BYTE] / 255.0;
}

double color_alphaF(const Color *c)
{
    return c->bytes[ALPHA_BYTE] / 255.0;
}

void color_set(Color *c, uint8_t red, uint8_t grn, uint8_t blu, uint8_t alpha)
{
    c->value = (alpha << 24) | (red << 16) | (grn << 8) | blu;
}

void color_setRedF(Color *c, double value)
{
    c->bytes[RED_BYTE] = color_intify(value) << 16;
}

void color_setGrnF(Color *c, double value)
{
    c->bytes[GRN_BYTE] = color_intify(value) << 8;
}

void color_setBluF(Color *c, double value)
{
    c->bytes[BLU_BYTE] = color_intify(value);
}

void color_setAlphaF(Color *c, double value)
{
    c->bytes[ALPHA_BYTE] = color_intify(value) << 24;
}

void color_setF(Color *c, double red, double grn, double blu, double alpha)
{
    c->value = (color_intify(alpha) << 24) | (color_intify(red) << 16) | (color_intify(grn) << 8) | color_intify(blu);
}

/* Not exposed in header */
uint8_t color_intify(double value)
{
    assert(0.0 <= value && value <= 1.0);
    return (uint8_t)(value * 255);
}
