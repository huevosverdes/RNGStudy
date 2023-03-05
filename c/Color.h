#ifndef __COLOR_H__
#define __COLOR_H__

#include <stdint.h>
#include <assert.h>

typedef union {
    uint32_t value;
    uint8_t bytes[4];
} Color;

extern const int RED_BYTE;
extern const int GRN_BYTE;
extern const int BLU_BYTE;
extern const int ALPHA_BYTE;

extern const Color COLOR_WHT;
extern const Color COLOR_GRY;
extern const Color COLOR_BLK;
extern const Color COLOR_RED;
extern const Color COLOR_ORG;
extern const Color COLOR_YLW;
extern const Color COLOR_GRN;
extern const Color COLOR_BLU;
extern const Color COLOR_PUR;

/* uint8_t color_red(const Color *c); */
/* uint8_t color_grn(const Color *c); */
/* uint8_t color_blu(const Color *c); */
/* uint8_t color_alpha(const Color *c); */

double color_redF(const Color *c);
double color_grnF(const Color *c);
double color_bluF(const Color *c);
double color_alphaF(const Color *c);

/* void color_setRed(Color *c, uint8_t value); */
/* void color_setGrn(Color *c, uint8_t value); */
/* void color_setBlu(Color *c, uint8_t value); */
/* void color_setAlpha(Color *c, uint8_t value); */
void color_set(Color *c, uint8_t red, uint8_t grn, uint8_t blu, uint8_t alpha);

void color_setRedF(Color *c, double value);
void color_setGrnF(Color *c, double value);
void color_setBluF(Color *c, double value);
void color_setAlphaF(Color *c, double value);
void color_setF(Color *c, double red, double grn, double blu, double alpha);

#endif /* #ifndef __COLOR_H__ */
