import math

class Ease:
    """
    Pure static class to provide easing curves
    - https://github.com/warrenm/AHEasing/blob/master/AHEasing/easing.c
    - https://easings.net/en

    - In debug build, `t` is asserted to be in interval: [0.0, 1.0]
    - Results are NOT always in closed interval: [0.0, 1.0]
    """

    LINEAR         =  0
    QUAD_IN        =  1
    QUAD_OUT       =  2
    QUAD_IN_OUT    =  3
    CUBE_IN        =  4
    CUBE_OUT       =  5
    CUBE_IN_OUT    =  6
    QUART_IN       =  7
    QUART_OUT      =  8
    QUART_IN_OUT   =  9
    QUINT_IN       = 10
    QUINT_OUT      = 11
    QUINT_IN_OUT   = 12
    SIN_IN         = 13
    SIN_OUT        = 14
    SIN_IN_OUT     = 15
    CIRCLE_IN      = 16
    CIRCLE_OUT     = 17
    CIRCLE_IN_OUT  = 18
    EXP_IN         = 19
    EXP_OUT        = 20
    EXP_IN_OUT     = 21
    ELASTIC_IN     = 22
    ELASTIC_OUT    = 23
    ELASTIC_IN_OUT = 24
    BACK_IN        = 25
    BACK_OUT       = 26
    BACK_IN_OUT    = 27
    BOUNCE_IN      = 28
    BOUNCE_OUT     = 29
    BOUNCE_IN_OUT  = 30
    SQUARE         = 31
    SMOOTHSTEP     = 32
    SMOOTHERSTEP   = 33

    def ease(t, method):
        """
        Convenience method to call any easing method from one place
        """
        result = 0.0

        if method == Ease.LINEAR:
            result = Ease.linear(t)
        elif method == Ease.QUAD_IN:
            result = Ease.quadIn(t)
        elif method == Ease.QUAD_OUT:
            result = Ease.quadOut(t)
        elif method == Ease.QUAD_IN_OUT:
            result = Ease.quadInOut(t)
        elif method == Ease.CUBE_IN:
            result = Ease.cubeIn(t)
        elif method == Ease.CUBE_OUT:
            result = Ease.cubeOut(t)
        elif method == Ease.CUBE_IN_OUT:
            result = Ease.cubeInOut(t)
        elif method == Ease.QUART_IN:
            result = Ease.quartIn(t)
        elif method == Ease.QUART_OUT:
            result = Ease.quartOut(t)
        elif method == Ease.QUART_IN_OUT:
            result = Ease.quartInOut(t)
        elif method == Ease.QUINT_IN:
            result = Ease.quintIn(t)
        elif method == Ease.QUINT_OUT:
            result = Ease.quintOut(t)
        elif method == Ease.QUINT_IN_OUT:
            result = Ease.quintInOut(t)
        elif method == Ease.SIN_IN:
            result = Ease.sinIn(t)
        elif method == Ease.SIN_OUT:
            result = Ease.sinOut(t)
        elif method == Ease.SIN_IN_OUT:
            result = Ease.sinInOut(t)
        elif method == Ease.CIRCLE_IN:
            result = Ease.circleIn(t)
        elif method == Ease.CIRCLE_OUT:
            result = Ease.circleOut(t)
        elif method == Ease.CIRCLE_IN_OUT:
            result = Ease.circleInOut(t)
        elif method == Ease.EXP_IN:
            result = Ease.expIn(t)
        elif method == Ease.EXP_OUT:
            result = Ease.expOut(t)
        elif method == Ease.EXP_IN_OUT:
            result = Ease.expInOut(t)
        elif method == Ease.ELASTIC_IN:
            result = Ease.elasticIn(t)
        elif method == Ease.ELASTIC_OUT:
            result = Ease.elasticOut(t)
        elif method == Ease.ELASTIC_IN_OUT:
            result = Ease.elasticInOut(t)
        elif method == Ease.BACK_IN:
            result = Ease.backIn(t)
        elif method == Ease.BACK_OUT:
            result = Ease.backOut(t)
        elif method == Ease.BACK_IN_OUT:
            result = Ease.backInOut(t)
        elif method == Ease.BOUNCE_IN:
            result = Ease.bounceIn(t)
        elif method == Ease.BOUNCE_OUT:
            result = Ease.bounceOut(t)
        elif method == Ease.BOUNCE_IN_OUT:
            result = Ease.bounceInOut(t)
        elif method == Ease.SQUARE:
            result = Ease.square(t)
        elif method == Ease.SMOOTHSTEP:
            result = Ease.smoothstep(t)
        elif method == Ease.SMOOTHERSTEP:
            result = Ease.smootherstep(t)
        else:
            result = Ease.linear(t)

        return result

    def linear(t):
        """
        y = x
        """
        assert 0.0 <= t and t <= 1.0
        return t

    @staticmethod
    def quadIn(t):
        """
        y = x^2
        """
        assert 0.0 <= t and t <= 1.0
        return t * t

    @staticmethod
    def quadOut(t):
        """
        y = -x^2 + 2x
        """
        assert 0.0 <= t and t <= 1.0
        return -(t * (t - 2.0))

    @staticmethod
    def quadInOut(t):
        """
        Piecewise quadratic:
        - [0.0, 0.5) : y = 0.5 * 2x^2
        - [0.5, 1.0] : y = -0.5 * ((2x - 1) * (2x - 3) - 1)
        """
        assert 0.0 <= t and t <= 1.0
        if t < 0.5:
            return 2.0 * t * t
        else:
            return (-2.0 * t * t) + (4.0 * t) - 1

    @staticmethod
    def cubeIn(t):
        """
        y = x^3
        """
        assert 0.0 <= t and t <= 1.0
        return t * t * t

    @staticmethod
    def cubeOut(t):
        """
        y = (x - 1)^3 + 1
        """
        assert 0.0 <= t and t <= 1.0
        p = (t - 1.0)
        return p * p * p + 1.0

    @staticmethod
    def cubeInOut(t):
        """
        Piecewise cubic:
        - [0.0, 0.5) : y = 0.5 * ((2x)^3)
        - [0.5, 1.0] : y = 0.5 * ((2x-2)^3 + 2)
        """
        assert 0.0 <= t and t <= 1.0
        if t < 0.5:
            return 4.0 * t * t * t
        else:
            p = ((2.0 * t) - 2.0)
            return (0.5 * p * p * p) + 1.0

    @staticmethod
    def quartIn(t):
        """
        y = x^4
        """
        assert 0.0 <= t and t <= 1.0
        return t * t * t * t

    @staticmethod
    def quartOut(t):
        """
        y = 1 - (x - 1)^4
        """
        assert 0.0 <= t and t <= 1.0
        p = t - 1.0
        return (p * p * p * (1.0 - t)) + 1.0

    @staticmethod
    def quartInOut(t):
        """
        Piecewise quartic:
        - [0.0, 0.5) : y = 0.5 * ((2x)^4)
        - [0.5, 1.0] : y = -0.5 * ((2x-2)^4 - 2)
        """
        assert 0.0 <= t and t <= 1.0
        if t < 0.5:
            return 8.0 * t * t * t * t
        else:
            p = (t - 1.0)
            return (-8.0 * p * p * p * p) + 1.0

    @staticmethod
    def quintIn(t):
        """
        y = x^5
        """
        assert 0.0 <= t and t <= 1.0
        return t * t * t * t * t

    @staticmethod
    def quintOut(t):
        """
        y = (x - 1)^5 + 1
        """
        assert 0.0 <= t and t <= 1.0
        p = t - 1.0
        return (p * p * p * p * p) + 1.0

    @staticmethod
    def quintInOut(t):
        """
        Piecewise quintic:
        - [0.0, 0.5) : y = 0.5 * ((2x)^5)
        - [0.5, 1.0] : y = 0.5 * ((2x-2)^5 + 2)
        """
        assert 0.0 <= t and t <= 1.0
        if t < 0.5:
            return 16.0 * t * t * t * t * t
        else:
            p = ((2.0 * t) - 2.0)
            return (0.5 * p * p * p * p * p) + 1.0

    @staticmethod
    def sinIn(t):
        """
        Quarter-cycle of sine wave
        """
        assert 0.0 <= t and t <= 1.0
        return math.sin((t - 1.0) * math.pi * 2.0) + 1

    @staticmethod
    def sinOut(t):
        """
        Quarter-cycle of sine wave (phase-shifted)
        """
        assert 0.0 <= t and t <= 1.0
        return math.sin(t * math.pi * 2.0)

    @staticmethod
    def sinInOut(t):
        """
        Half-cycle of sine wave (phase-shifted)
        """
        assert 0.0 <= t and t <= 1.0
        return 0.5 * (1.0 - math.cos(t * math.pi))

    @staticmethod
    def circleIn(t):
        """
        Unit circle: shifted quadrant IV
        """
        assert 0.0 <= t and t <= 1.0
        return 1.0 - math.sqrt(1.0 - (t * t))

    @staticmethod
    def circleOut(t):
        """
        Unit circle: shifted quadrant II
        """
        assert 0.0 <= t and t <= 1.0
        return math.sqrt((2.0 - t) * t)

    @staticmethod
    def circleInOut(t):
        """
        Piecewise circular:
        - [0.0, 0.5) : y = 0.5 * (1 - sqrt(1 - 4x^2))
        - [0.5, 1.0] : y = 0.5 * (sqrt(-(2x - 3) * (2x - 1)) + 1)
        """
        assert 0.0 <= t and t <= 1.0
        if t < 0.5:
            return 0.5 * (1.0 - math.sqrt(1.0 - (4.0 * (t * t))))
        else:
            return 0.5 * (math.sqrt(-((2.0 * t) - 3.0) * ((2.0 * t) - 1.0)) + 1.0)

    @staticmethod
    def expIn(t):
        """
        y = 2^(10(x - 1))
        """
        assert 0.0 <= t and t <= 1.0
        return (t if (t == 0.0) else math.pow(2.0, 10.0 * (t - 1.0)))

    @staticmethod
    def expOut(t):
        """
        y = -2^(-10x) + 1
        """
        assert 0.0 <= t and t <= 1.0
        return (t if t == 1.0 else 1.0 - math.pow(2.0, -10.0 * t))

    @staticmethod
    def expInOut(t):
        """
        Piecewise exponential:
        - [0.0, 0.5) : y = 0.5 * 2^(10(2x - 1))
        - [0.5, 1.0] : y = -0.5 * 2^(-10(2x - 1))) + 1
        """
        assert 0.0 <= t and t <= 1.0
        if t == 0.0 or t == 1.0:
            return t
        elif t < 0.5:
            return 0.5 * math.pow(2.0, (20.0 * t) - 10.0)
        else:
            return -0.5 * math.pow(2.0, (-20.0 * t) + 10.0) + 1.0

    @staticmethod
    def elasticIn(t):
        """
        Damped sine wave: y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
        """
        assert 0.0 <= t and t <= 1.0
        return (
            math.sin(13.0 * math.pi * 2.0 * t) *
            math.pow(2.0, 10.0 * (t - 1.0)))

    @staticmethod
    def elasticOut(t):
        """
        Damped sine wave: y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
        """
        assert 0.0 <= t and t <= 1.0
        return (
            math.sin(-13.0 * math.pi * 2.0 * (t + 1.0)) *
            math.pow(2.0, -10.0 * t)) + 1.0

    @staticmethod
    def elasticInOut(t):
        """
        Piecewise damped sine wave:
        - [0.0, 0.5) : y = 0.5 * sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))
        - [0.5, 1.0] : y = 0.5 * (sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2)
        """
        assert 0.0 <= t and t <= 1.0
        if t < 0.5:
            return (
                0.5 *
                math.sin(13.0 * math.pi * 2.0 * (2.0 * t)) *
                math.pow(2.0, 10.0 * ((2.0 * t) - 1.0)))
        else:
            return (
                0.5 * (
                    (math.sin(-13.0 * math.pi * 2.0 * ((2.0 * t - 1.0) + 1.0)) *
                     math.pow(2.0, -10.0 * (2.0 * t - 1.0))) +
                    2.0))

    @staticmethod
    def backIn(t):
        """
        Overshooting cubic: y = x^3-x*sin(x*pi)
        """
        assert 0.0 <= t and t <= 1.0
        return (t * t * t) - (t * math.sin(t * math.pi))

    @staticmethod
    def backOut(t):
        """
        Overshooting cubic: y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
        """
        assert 0.0 <= t and t <= 1.0
        p = (1.0 - t)
        return 1.0 - (
            (p * p * p) -
            (p * math.sin(p * math.pi)))

    @staticmethod
    def backInOut(t):
        """
        Piecewise overshooting cubic:
        - n[0.0, 0.5) : y = 0.5 * ((2x)^3-(2x)*sin(2*x*pi))
        - [0.5, 1.0] : y = 0.5 * (1-((1-x)^3-(1-x)*sin((1-x)*pi))+1)
        """
        assert 0.0 <= t and t <= 1.0
        if t < 0.5:
            p = 2.0 * t
            return 0.5 * ((p * p * p) - (p * math.sin(p * math.pi)))
        else:
            p = (1.0 - (2.0 * t - 1.0))
            return 0.5 * (1.0 - ((p * p * p) - (p * math.sin(p * math.pi)))) + 0.5

    @staticmethod
    def bounceIn(t):
        """
        Piecewise polynomial to simulate bouncing
        """
        assert 0.0 <= t and t <= 1.0
        return 1.0 - Ease.bounceOut(1.0 - t)

    @staticmethod
    def bounceOut(t):
        """
        Piecewise polynomial to simulate bouncing
        """
        assert 0.0 <= t and t <= 1.0
        if t < 4.0 / 11.0:
            return (121.0 * t * t) / 16.0
        elif t < 8.0 / 11.0:
            return (
                (363.0 / 40.0 * t * t) -
                (99.0 / 10.0 * t) +
                (17.0 / 5.0))
        elif t < 9.0 / 10.0:
            return (
                (4356.0 / 361.0 * t * t) -
                (35442.0 / 1805.0 * t) +
                (16061.0 / 1805.0))
        else:
            return (
                (54.0 / 5.0 * t * t) -
                (513.0 / 25.0 * t) +
                (268.0 / 25.0))

    @staticmethod
    def bounceInOut(t):
        """
        Piecewise polynomial to simulate bouncing
        """
        assert 0.0 <= t and t <= 1.0
        if t < 0.5:
            return 0.5 * Ease.bounceIn(t * 2.0)
        else:
            return 0.5 * Ease.bounceOut(t * 2.0 - 1.0) + 0.5

    @staticmethod
    def square(t):
        """
        - [0.0, 0.5) : 0.0
        - [0.5: 1.0] : 1.0
        """
        assert 0.0 <= t and t <= 1.0
        return 0.0 if t < 0.5 else 1.0

    @staticmethod
    def smoothstep(t):
        """
        https://en.wikipedia.org/wiki/Smoothstep
        """
        assert 0.0 <= t and t <= 1.0
        return (3.0 - (2.0 * t)) * t * t

    @staticmethod
    def smootherstep(t):
        """
        https://en.wikipedia.org/wiki/Smoothstep
        """
        assert 0.0 <= t and t <= 1.0
        return t * t * t * (t * (t * 6.0 - 15.0) + 10.0)
