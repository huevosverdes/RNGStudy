#include "Ease.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif /* M_PI */

double ease(double t, EasingMethod method)
{
    assert(0.0 <= t && t <= 1.0);
    double result = 0.0;
    switch(method)
    {
    case QUAD_IN        : result = easeQuadIn(t);       break;
    case QUAD_OUT       : result = easeQuadOut(t);      break;
    case QUAD_IN_OUT    : result = easeQuadInOut(t);    break;
    case CUBE_IN        : result = easeCubeIn(t);       break;
    case CUBE_OUT       : result = easeCubeOut(t);      break;
    case CUBE_IN_OUT    : result = easeCubeInOut(t);    break;
    case QUART_IN       : result = easeQuartIn(t);      break;
    case QUART_OUT      : result = easeQuartOut(t);     break;
    case QUART_IN_OUT   : result = easeQuartInOut(t);   break;
    case QUINT_IN       : result = easeQuintIn(t);      break;
    case QUINT_OUT      : result = easeQuintOut(t);     break;
    case QUINT_IN_OUT   : result = easeQuintInOut(t);   break;
    case SIN_IN         : result = easeSinIn(t);        break;
    case SIN_OUT        : result = easeSinOut(t);       break;
    case SIN_IN_OUT     : result = easeSinInOut(t);     break;
    case CIRCLE_IN      : result = easeCircleIn(t);     break;
    case CIRCLE_OUT     : result = easeCircleOut(t);    break;
    case CIRCLE_IN_OUT  : result = easeCircleInOut(t);  break;
    case EXP_IN         : result = easeExpIn(t);        break;
    case EXP_OUT        : result = easeExpOut(t);       break;
    case EXP_IN_OUT     : result = easeExpInOut(t);     break;
    case ELASTIC_IN     : result = easeElasticIn(t);    break;
    case ELASTIC_OUT    : result = easeElasticOut(t);   break;
    case ELASTIC_IN_OUT : result = easeElasticInOut(t); break;
    case BACK_IN        : result = easeBackIn(t);       break;
    case BACK_OUT       : result = easeBackOut(t);      break;
    case BACK_IN_OUT    : result = easeBackInOut(t);    break;
    case BOUNCE_IN      : result = easeBounceIn(t);     break;
    case BOUNCE_OUT     : result = easeBounceOut(t);    break;
    case BOUNCE_IN_OUT  : result = easeBounceInOut(t);  break;
    case SQUARE         : result = easeSquare(t);       break;
    case SMOOTHSTEP     : result = easeSmoothstep(t);   break;
    case SMOOTHERSTEP   : result = easeSmootherstep(t); break;
    default             : result = easeLinear(t);       break;
    }
    return result;
}

double easeLinear(double t)
{
    /* f(t) = t */
    assert(0.0 <= t && t <= 1.0);
    return t;
}

double easeQuadIn(double t)
{
    /* f(t) = t^2 */
    assert(0.0 <= t && t <= 1.0);
    return t * t;
}

double easeQuadOut(double t)
{
    /* f(t) = -t^2 + 2t */
    assert(0.0 <= t && t <= 1.0);
    return -(t * (t - 2.0));
}

double easeQuadInOut(double t)
{
    /* Piecewise quadratic: */
    /* - [0.0, 0.5) : f(t) = 0.5 * 2t^2 */
    /* - [0.5, 1.0] : f(t) = -0.5 * ((2t - 1) * (2t - 3) - 1) */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5)
        return 2.0 * t * t;
    else
        return (-2.0 * t * t) + (4.0 * t) - 1;
}

double easeCubeIn(double t)
{
    /* f(t) = t^3 */
    assert(0.0 <= t && t <= 1.0);
    return t * t * t;
}

double easeCubeOut(double t)
{
    /* f(t) = (t - 1)^3 + 1 */
    assert(0.0 <= t && t <= 1.0);
    double p = (t - 1.0);
    return p * p * p + 1.0;
}

double easeCubeInOut(double t)
{
    /* Piecewise cubic: */
    /* - [0.0, 0.5) : f(t) = 0.5 * ((2t)^3) */
    /* - [0.5, 1.0] : f(t) = 0.5 * ((2t-2)^3 + 2) */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5)
        return 4.0 * t * t * t;
    else
    {
        double p = ((2.0 * t) - 2.0);
        return (0.5 * p * p * p) + 1.0;
    }
}

double easeQuartIn(double t)
{
    /* f(t) = t^4 */
    assert(0.0 <= t && t <= 1.0);
    return t * t * t * t;
}

double easeQuartOut(double t)
{
    /* f(t) = 1 - (t - 1)^4 */
    assert(0.0 <= t && t <= 1.0);
    double p = t - 1.0;
    return (p * p * p * (1.0 - t)) + 1.0;
}

double easeQuartInOut(double t)
{
    /* Piecewise quartic: */
    /* - [0.0, 0.5) : f(t) = 0.5 * ((2t)^4) */
    /* - [0.5, 1.0] : f(t) = -0.5 * ((2t-2)^4 - 2) */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5) {
        return 8.0 * t * t * t * t;
    } else {
        double p = (t - 1.0);
        return (-8.0 * p * p * p * p) + 1.0;
    }
}

double easeQuintIn(double t)
{
    /* f(t) = t^5 */
    assert(0.0 <= t && t <= 1.0);
    return t * t * t * t * t;
}

double easeQuintOut(double t)
{
    /* f(t) = (t - 1)^5 + 1 */
    assert(0.0 <= t && t <= 1.0);
    double p = t - 1.0;
    return (p * p * p * p * p) + 1.0;
}

double easeQuintInOut(double t)
{
    /* Piecewise quintic: */
    /* - [0.0, 0.5) : f(t) = 0.5 * ((2t)^5) */
    /* - [0.5, 1.0] : f(t) = 0.5 * ((2t-2)^5 + 2) */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5) {
        return 16.0 * t * t * t * t * t;
    } else {
        double p = ((2.0 * t) - 2.0);
        return (0.5 * p * p * p * p * p) + 1.0;
    }
}

double easeSinIn(double t)
{
    /* Quarter-cycle of sine wave */
    assert(0.0 <= t && t <= 1.0);
    return sin((t - 1.0) * M_PI * 2.0) + 1;
}

double easeSinOut(double t)
{
    /* Quarter-cycle of sine wave (phase-shifted) */
    assert(0.0 <= t && t <= 1.0);
    return sin(t * M_PI * 2.0);
}

double easeSinInOut(double t)
{
    /* Half-cycle of sine wave (phase-shifted) */
    assert(0.0 <= t && t <= 1.0);
    return 0.5 * (1.0 - cos(t * M_PI));
}

double easeCircleIn(double t)
{
    /* Unit circle: shifted quadrant IV */
    assert(0.0 <= t && t <= 1.0);
    return 1.0 - sqrt(1.0 - (t * t));
}

double easeCircleOut(double t)
{
    /* Unit circle: shifted quadrant II */
    assert(0.0 <= t && t <= 1.0);
    return sqrt((2.0 - t) * t);
}

double easeCircleInOut(double t)
{
    /* Piecewise circular: */
    /* - [0.0, 0.5) : f(t) = 0.5 * (1 - sqrt(1 - 4t^2)) */
    /* - [0.5, 1.0] : f(t) = 0.5 * (sqrt(-(2t - 3) * (2t - 1)) + 1) */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5)
        return 0.5 * (1.0 - sqrt(1.0 - (4.0 * (t * t))));
    else
        return 0.5 * (sqrt(-((2.0 * t) - 3.0) * ((2.0 * t) - 1.0)) + 1.0);
}

double easeExpIn(double t)
{
    /* f(t) = 2^(10(t - 1)) */
    assert(0.0 <= t && t <= 1.0);

    return (t == 0.0) ? t : pow(2.0, 10.0 * (t - 1.0));
}

double easeExpOut(double t)
{
    /* f(t) = -2^(-10t) + 1 */
    assert(0.0 <= t && t <= 1.0);
    return (t == 1.0) ? t : 1.0 - pow(2.0, -10.0 * t);
}

double easeExpInOut(double t)
{
    /* Piecewise exponential: */
    /* - [0.0, 0.5) : f(t) = 0.5 * 2^(10(2t - 1)) */
    /* - [0.5, 1.0] : f(t) = -0.5 * 2^(-10(2t - 1))) + 1 */
    assert(0.0 <= t && t <= 1.0);
    if(t == 0.0 || t == 1.0)
        return t;
    else if(t < 0.5)
        return 0.5 * pow(2.0, (20.0 * t) - 10.0);
    else
        return -0.5 * pow(2.0, (-20.0 * t) + 10.0) + 1.0;
}

double easeElasticIn(double t)
{
    /* Damped sine wave: f(t) = sin(13pi/2*t)*pow(2, 10 * (t - 1)) */
    assert(0.0 <= t && t <= 1.0);
    return (
        sin(13.0 * M_PI * 2.0 * t) *
        pow(2.0, 10.0 * (t - 1.0)));
}

double easeElasticOut(double t)
{
    /* Damped sine wave: f(t) = sin(-13pi/2*(t + 1))*pow(2, -10t) + 1 */
    assert(0.0 <= t && t <= 1.0);
    return (
        sin(-13.0 * M_PI * 2.0 * (t + 1.0)) *
        pow(2.0, -10.0 * t)) + 1.0;
}

double easeElasticInOut(double t)
{
    /* Piecewise damped sine wave: */
    /* - [0.0, 0.5) : f(t) = 0.5 * sin(13pi/2*(2*t))*pow(2, 10 * ((2*t) - 1)) */
    /* - [0.5, 1.0] : f(t) = 0.5 * (sin(-13pi/2*((2t-1)+1))*pow(2,-10(2*t-1)) + 2) */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5)
        return (
            0.5 *
            sin(13.0 * M_PI * 2.0 * (2.0 * t)) *
            pow(2.0, 10.0 * ((2.0 * t) - 1.0)));
    else
        return (
            0.5 * (
                (sin(-13.0 * M_PI * 2.0 * ((2.0 * t - 1.0) + 1.0)) *
                 pow(2.0, -10.0 * (2.0 * t - 1.0))) +
                2.0));
}

double easeBackIn(double t)
{
    /* Overshooting cubic: f(t) = t^3-t*sin(t*pi) */
    assert(0.0 <= t && t <= 1.0);
    return (t * t * t) - (t * sin(t * M_PI));
}

double easeBackOut(double t)
{
    /* Overshooting cubic: f(t) = 1-((1-t)^3-(1-t)*sin((1-t)*pi)) */
    assert(0.0 <= t && t <= 1.0);
    double p = (1.0 - t);
    return 1.0 - (
        (p * p * p) -
        (p * sin(p * M_PI)));
}

double easeBackInOut(double t)
{
    /* Piecewise overshooting cubic: */
    /* - [0.0, 0.5) : f(t) = 0.5 * ((2t)^3-(2t)*sin(2*t*pi)) */
    /* - [0.5, 1.0] : f(t) = 0.5 * (1-((1-t)^3-(1-t)*sin((1-t)*pi))+1) */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5) {
        double p = 2.0 * t;
        return 0.5 * ((p * p * p) - (p * sin(p * M_PI)));
    } else {
        double p = (1.0 - (2.0 * t - 1.0));
        return 0.5 * (1.0 - ((p * p * p) - (p * sin(p * M_PI)))) + 0.5;
    }
}

double easeBounceIn(double t)
{
    /* Piecewise polynomial to simulate bouncing */
    assert(0.0 <= t && t <= 1.0);
    return 1.0 - easeBounceOut(1.0 - t);
}

double easeBounceOut(double t)
{
    /* Piecewise polynomial to simulate bouncing */
    assert(0.0 <= t && t <= 1.0);
    if(t < 4.0 / 11.0)
        return (121.0 * t * t) / 16.0;
    else if(t < 8.0 / 11.0)
        return (
            (363.0 / 40.0 * t * t) -
            (99.0 / 10.0 * t) +
            (17.0 / 5.0));
    else if(t < 9.0 / 10.0)
        return (
            (4356.0 / 361.0 * t * t) -
            (35442.0 / 1805.0 * t) +
            (16061.0 / 1805.0));
    else
        return (
            (54.0 / 5.0 * t * t) -
            (513.0 / 25.0 * t) +
            (268.0 / 25.0));
}

double easeBounceInOut(double t)
{
    /* Piecewise polynomial to simulate bouncing */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5)
        return 0.5 * easeBounceIn(t * 2.0);
    else
        return 0.5 * easeBounceOut(t * 2.0 - 1.0) + 0.5;
}

double easeSquare(double t)
{
    /* [0.0, 0.5) : 0.0 */
    /* [0.5: 1.0] : 1.0 */
    assert(0.0 <= t && t <= 1.0);
    return t < 0.5 ? 0.0 : 1.0;
}

double easeSmoothstep(double t)
{
    /* https://en.wikipedia.org/wiki/Smoothstep */
    return (3.0 - (2.0 * t)) * t * t;
}

double easeSmootherstep(double t)
{
    /* https://en.wikipedia.org/wiki/Smoothstep */
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}
