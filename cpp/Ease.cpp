#include "Ease.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif /* M_PI */

double Ease::ease(double t, EasingMethod method)
{
    assert(0.0 <= t && t <= 1.0);
    double result = 0.0;
    switch(method)
    {
    case Ease::EasingMethod::QUAD_IN        : result = Ease::quadIn(t);       break;
    case Ease::EasingMethod::QUAD_OUT       : result = Ease::quadOut(t);      break;
    case Ease::EasingMethod::QUAD_IN_OUT    : result = Ease::quadInOut(t);    break;
    case Ease::EasingMethod::CUBE_IN        : result = Ease::cubeIn(t);       break;
    case Ease::EasingMethod::CUBE_OUT       : result = Ease::cubeOut(t);      break;
    case Ease::EasingMethod::CUBE_IN_OUT    : result = Ease::cubeInOut(t);    break;
    case Ease::EasingMethod::QUART_IN       : result = Ease::quartIn(t);      break;
    case Ease::EasingMethod::QUART_OUT      : result = Ease::quartOut(t);     break;
    case Ease::EasingMethod::QUART_IN_OUT   : result = Ease::quartInOut(t);   break;
    case Ease::EasingMethod::QUINT_IN       : result = Ease::quintIn(t);      break;
    case Ease::EasingMethod::QUINT_OUT      : result = Ease::quintOut(t);     break;
    case Ease::EasingMethod::QUINT_IN_OUT   : result = Ease::quintInOut(t);   break;
    case Ease::EasingMethod::SIN_IN         : result = Ease::sinIn(t);        break;
    case Ease::EasingMethod::SIN_OUT        : result = Ease::sinOut(t);       break;
    case Ease::EasingMethod::SIN_IN_OUT     : result = Ease::sinInOut(t);     break;
    case Ease::EasingMethod::CIRCLE_IN      : result = Ease::circleIn(t);     break;
    case Ease::EasingMethod::CIRCLE_OUT     : result = Ease::circleOut(t);    break;
    case Ease::EasingMethod::CIRCLE_IN_OUT  : result = Ease::circleInOut(t);  break;
    case Ease::EasingMethod::EXP_IN         : result = Ease::expIn(t);        break;
    case Ease::EasingMethod::EXP_OUT        : result = Ease::expOut(t);       break;
    case Ease::EasingMethod::EXP_IN_OUT     : result = Ease::expInOut(t);     break;
    case Ease::EasingMethod::ELASTIC_IN     : result = Ease::elasticIn(t);    break;
    case Ease::EasingMethod::ELASTIC_OUT    : result = Ease::elasticOut(t);   break;
    case Ease::EasingMethod::ELASTIC_IN_OUT : result = Ease::elasticInOut(t); break;
    case Ease::EasingMethod::BACK_IN        : result = Ease::backIn(t);       break;
    case Ease::EasingMethod::BACK_OUT       : result = Ease::backOut(t);      break;
    case Ease::EasingMethod::BACK_IN_OUT    : result = Ease::backInOut(t);    break;
    case Ease::EasingMethod::BOUNCE_IN      : result = Ease::bounceIn(t);     break;
    case Ease::EasingMethod::BOUNCE_OUT     : result = Ease::bounceOut(t);    break;
    case Ease::EasingMethod::BOUNCE_IN_OUT  : result = Ease::bounceInOut(t);  break;
    case Ease::EasingMethod::SQUARE         : result = Ease::square(t);       break;
    case Ease::EasingMethod::SMOOTHSTEP     : result = Ease::smoothstep(t);   break;
    case Ease::EasingMethod::SMOOTHERSTEP   : result = Ease::smootherstep(t); break;
    default                                 : result = Ease::linear(t);       break;
    }
    return result;
}

double Ease::linear(double t)
{
    /* f(t) = t */
    assert(0.0 <= t && t <= 1.0);
    return t;
}

double Ease::quadIn(double t)
{
    /* f(t) = t^2 */
    assert(0.0 <= t && t <= 1.0);
    return t * t;
}

double Ease::quadOut(double t)
{
    /* f(t) = -t^2 + 2t */
    assert(0.0 <= t && t <= 1.0);
    return -(t * (t - 2.0));
}

double Ease::quadInOut(double t)
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

double Ease::cubeIn(double t)
{
    /* f(t) = t^3 */
    assert(0.0 <= t && t <= 1.0);
    return t * t * t;
}

double Ease::cubeOut(double t)
{
    /* f(t) = (t - 1)^3 + 1 */
    assert(0.0 <= t && t <= 1.0);
    double p = (t - 1.0);
    return p * p * p + 1.0;
}

double Ease::cubeInOut(double t)
{
    /* Piecewise cubic: */
    /* - [0.0, 0.5) : f(t) = 0.5 * ((2t)^3) */
    /* - [0.5, 1.0] : f(t) = 0.5 * ((2t-2)^3 + 2) */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5) {
        return 4.0 * t * t * t;
    } else {
        double p = ((2.0 * t) - 2.0);
        return (0.5 * p * p * p) + 1.0;
    }
}

double Ease::quartIn(double t)
{
    /* f(t) = t^4 */
    assert(0.0 <= t && t <= 1.0);
    return t * t * t * t;
}

double Ease::quartOut(double t)
{
    /* f(t) = 1 - (t - 1)^4 */
    assert(0.0 <= t && t <= 1.0);
    double p = t - 1.0;
    return (p * p * p * (1.0 - t)) + 1.0;
}

double Ease::quartInOut(double t)
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

double Ease::quintIn(double t)
{
    /* f(t) = t^5 */
    assert(0.0 <= t && t <= 1.0);
    return t * t * t * t * t;
}

double Ease::quintOut(double t)
{
    /* f(t) = (t - 1)^5 + 1 */
    assert(0.0 <= t && t <= 1.0);
    double p = t - 1.0;
    return (p * p * p * p * p) + 1.0;
}

double Ease::quintInOut(double t)
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

double Ease::sinIn(double t)
{
    /* Quarter-cycle of sine wave */
    assert(0.0 <= t && t <= 1.0);
    return sin((t - 1.0) * M_PI * 2.0) + 1;
}

double Ease::sinOut(double t)
{
    /* Quarter-cycle of sine wave (phase-shifted) */
    assert(0.0 <= t && t <= 1.0);
    return sin(t * M_PI * 2.0);
}

double Ease::sinInOut(double t)
{
    /* Half-cycle of sine wave (phase-shifted) */
    assert(0.0 <= t && t <= 1.0);
    return 0.5 * (1.0 - cos(t * M_PI));
}

double Ease::circleIn(double t)
{
    /* Unit circle: shifted quadrant IV */
    assert(0.0 <= t && t <= 1.0);
    return 1.0 - sqrt(1.0 - (t * t));
}

double Ease::circleOut(double t)
{
    /* Unit circle: shifted quadrant II */
    assert(0.0 <= t && t <= 1.0);
    return sqrt((2.0 - t) * t);
}

double Ease::circleInOut(double t)
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

double Ease::expIn(double t)
{
    /* f(t) = 2^(10(t - 1)) */
    assert(0.0 <= t && t <= 1.0);

    return (t == 0.0) ? t : pow(2.0, 10.0 * (t - 1.0));
}

double Ease::expOut(double t)
{
    /* f(t) = -2^(-10t) + 1 */
    assert(0.0 <= t && t <= 1.0);
    return (t == 1.0) ? t : 1.0 - pow(2.0, -10.0 * t);
}

double Ease::expInOut(double t)
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

double Ease::elasticIn(double t)
{
    /* Damped sine wave: f(t) = sin(13pi/2*t)*pow(2, 10 * (t - 1)) */
    assert(0.0 <= t && t <= 1.0);
    return (
        sin(13.0 * M_PI * 2.0 * t) *
        pow(2.0, 10.0 * (t - 1.0)));
}

double Ease::elasticOut(double t)
{
    /* Damped sine wave: f(t) = sin(-13pi/2*(t + 1))*pow(2, -10t) + 1 */
    assert(0.0 <= t && t <= 1.0);
    return (
        sin(-13.0 * M_PI * 2.0 * (t + 1.0)) *
        pow(2.0, -10.0 * t)) + 1.0;
}

double Ease::elasticInOut(double t)
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

double Ease::backIn(double t)
{
    /* Overshooting cubic: f(t) = t^3-t*sin(t*pi) */
    assert(0.0 <= t && t <= 1.0);
    return (t * t * t) - (t * sin(t * M_PI));
}

double Ease::backOut(double t)
{
    /* Overshooting cubic: f(t) = 1-((1-t)^3-(1-t)*sin((1-t)*pi)) */
    assert(0.0 <= t && t <= 1.0);
    double p = (1.0 - t);
    return 1.0 - (
        (p * p * p) -
        (p * sin(p * M_PI)));
}

double Ease::backInOut(double t)
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

double Ease::bounceIn(double t)
{
    /* Piecewise polynomial to simulate bouncing */
    assert(0.0 <= t && t <= 1.0);
    return 1.0 - Ease::bounceOut(1.0 - t);
}

double Ease::bounceOut(double t)
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

double Ease::bounceInOut(double t)
{
    /* Piecewise polynomial to simulate bouncing */
    assert(0.0 <= t && t <= 1.0);
    if(t < 0.5)
        return 0.5 * Ease::bounceIn(t * 2.0);
    else
        return 0.5 * Ease::bounceOut(t * 2.0 - 1.0) + 0.5;
}

double Ease::square(double t)
{
    /* [0.0, 0.5) : 0.0 */
    /* [0.5: 1.0] : 1.0 */
    assert(0.0 <= t && t <= 1.0);
    return t < 0.5 ? 0.0 : 1.0;
}

double Ease::smoothstep(double t)
{
    /* https://en.wikipedia.org/wiki/Smoothstep */
    return (3.0 - (2.0 * t)) * t * t;
}

double Ease::smootherstep(double t)
{
    /* https://en.wikipedia.org/wiki/Smoothstep */
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}
