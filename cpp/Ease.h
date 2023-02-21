#ifndef __EASE__
#define __EASE__

#include <cassert>
#include <cmath>

class Ease
{
    // Pure static class to provide easing curves
    // https://github.com/warrenm/AHEasing/blob/master/AHEasing/easing.c
    // https://easings.net/en

    // - In debug build, `t` is asserted to be in interval: [0.0, 1.0]
    // - Results are NOT always in closed interval: [0.0, 1.0]
public:
    enum class EasingMethod {
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
    };

    static double ease(double t, EasingMethod method);
    static double linear(double t);
    static double quadIn(double t);
    static double quadOut(double t);
    static double quadInOut(double t);
    static double cubeIn(double t);
    static double cubeOut(double t);
    static double cubeInOut(double t);
    static double quartIn(double t);
    static double quartOut(double t);
    static double quartInOut(double t);
    static double quintIn(double t);
    static double quintOut(double t);
    static double quintInOut(double t);
    static double sinIn(double t);
    static double sinOut(double t);
    static double sinInOut(double t);
    static double circleIn(double t);
    static double circleOut(double t);
    static double circleInOut(double t);
    static double expIn(double t);
    static double expOut(double t);
    static double expInOut(double t);
    static double elasticIn(double t);
    static double elasticOut(double t);
    static double elasticInOut(double t);
    static double backIn(double t);
    static double backOut(double t);
    static double backInOut(double t);
    static double bounceIn(double t);
    static double bounceOut(double t);
    static double bounceInOut(double t);
    static double square(double t);
    static double smoothstep(double t);
    static double smootherstep(double t);
};

#endif /* #ifndef __EASE__ */
