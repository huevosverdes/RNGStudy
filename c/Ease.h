#ifndef __EASE_H__
#define __EASE_H__

#include <assert.h>
#include <math.h>

/*
 https://github.com/warrenm/AHEasing/blob/master/AHEasing/easing.c
 https://easings.net/en

 - In debug build, `t` is asserted to be in interval: [0.0, 1.0]
 - Results are NOT always in closed interval: [0.0, 1.0]
 - Added Smoothstep and Smootherstep from Perlin Noise.
*/

typedef enum {
    LINEAR         = 0,
    QUAD_IN        = 1,
    QUAD_OUT       = 2,
    QUAD_IN_OUT    = 3,
    CUBE_IN        = 4,
    CUBE_OUT       = 5,
    CUBE_IN_OUT    = 6,
    QUART_IN       = 7,
    QUART_OUT      = 8,
    QUART_IN_OUT   = 9,
    QUINT_IN       = 10,
    QUINT_OUT      = 11,
    QUINT_IN_OUT   = 12,
    SIN_IN         = 13,
    SIN_OUT        = 14,
    SIN_IN_OUT     = 15,
    CIRCLE_IN      = 16,
    CIRCLE_OUT     = 17,
    CIRCLE_IN_OUT  = 18,
    EXP_IN         = 19,
    EXP_OUT        = 20,
    EXP_IN_OUT     = 21,
    ELASTIC_IN     = 22,
    ELASTIC_OUT    = 23,
    ELASTIC_IN_OUT = 24,
    BACK_IN        = 25,
    BACK_OUT       = 26,
    BACK_IN_OUT    = 27,
    BOUNCE_IN      = 28,
    BOUNCE_OUT     = 29,
    BOUNCE_IN_OUT  = 30,
    SQUARE         = 31,
    SMOOTHSTEP     = 35,
    SMOOTHERSTEP   = 36
} EasingMethod;

double ease(double t, EasingMethod method);
double easeLinear(double t);
double easeQuadIn(double t);
double easeQuadOut(double t);
double easeQuadInOut(double t);
double easeCubeIn(double t);
double easeCubeOut(double t);
double easeCubeInOut(double t);
double easeQuartIn(double t);
double easeQuartOut(double t);
double easeQuartInOut(double t);
double easeQuintIn(double t);
double easeQuintOut(double t);
double easeQuintInOut(double t);
double easeSinIn(double t);
double easeSinOut(double t);
double easeSinInOut(double t);
double easeCircleIn(double t);
double easeCircleOut(double t);
double easeCircleInOut(double t);
double easeExpIn(double t);
double easeExpOut(double t);
double easeExpInOut(double t);
double easeElasticIn(double t);
double easeElasticOut(double t);
double easeElasticInOut(double t);
double easeBackIn(double t);
double easeBackOut(double t);
double easeBackInOut(double t);
double easeBounceIn(double t);
double easeBounceOut(double t);
double easeBounceInOut(double t);
double easeSquare(double t);
double easeSmoothstep(double t);
double easeSmootherstep(double t);

#endif /* __EASE_H__ */
