class Color:
    WHT = None
    GRY = None
    BLK = None
    RED = None
    ORG = None
    YLW = None
    GRN = None
    BLU = None
    PUR = None

    def __init__(self, red=0, grn=0, blu=0, alpha=255):
        self._color = (alpha << 24) | (red << 16) | (grn << 8) | blu

    def red(self):
        return (self._color >> 16) & 0xFF

    def grn(self):
        return (self._color >> 8) & 0xFF

    def blu(self):
        return self._color & 0xFF

    def alpha(self):
        return (self._color >> 24) & 0xFF

    def redF(self):
        return red() / 255.0

    def grnF(self):
        return grn() / 255.0

    def bluF(self):
        return blu() / 255.0

    def alphaF(self):
        return alpha() / 255.0

    def setRed(self, value):
        assert(0 <= value and value <= 255)
        self._color = (self._color & 0xFF00FFFF) | (value << 16)

    def setGrn(self, value):
        assert(0 <= value and value <= 255)
        self._color = (self._color & 0xFFFF00FF) | (value << 8)

    def setBlu(self, value):
        assert(0 <= value and value <= 255)
        self._color = (self._color & 0xFFFFFF00) | value

    def setAlpha(self, value):
        assert(0 <= value and value <= 255)
        self._color = (self._color & 0x00FFFFFF) | (value << 24)

    def set(self, red, grn, blu, alpha=255):
        assert(0 <= red and red <= 255)
        assert(0 <= grn and grn <= 255)
        assert(0 <= blu and blu <= 255)
        assert(0 <= alpha and alpha <= 255)
        self._color = (alpha << 24) | (red << 16) | (grn << 8) | blu

    def setRedF(self, value):
        assert(0.0 <= value and value <= 1.0)
        self._color = (self._color & 0xFF00FFFF) | (Color.__intify(value) << 16)

    def setGrnF(self, value):
        assert(0.0 <= value and value <= 1.0)
        self._color = (self._color & 0xFFFF00FF) | (Color.__intify(value) << 8)

    def setBluF(self, value):
        assert(0.0 <= value and value <= 1.0)
        self._color = (self._color & 0xFFFFFF00) | Color.__intify(value)

    def setAlphaF(self, value):
        assert(0.0 <= value and value <= 1.0)
        self._color = (self._color & 0x00FFFFFF) | (Color.__intify(value) << 24)

    def setF(self, red, grn, blu, alpha=1.0):
        assert(0.0 <= red and red <= 1.0)
        assert(0.0 <= grn and grn <= 1.0)
        assert(0.0 <= blu and blu <= 1.0)
        assert(0.0 <= alpha and alpha <= 1.0)
        self._color = ((Color.__intify(alpha) << 24) |
                       (Color.__intify(red) << 16) |
                       (Color.__intify(grn) << 8) |
                       Color.__intify(blu))

    @staticmethod
    def __intify(value):
        assert(0.0 <= value and value <= 1.0)
        return int(value * 255)

Color.WHT = Color(0xFF, 0xFF, 0xFF)
Color.GRY = Color(0x99, 0x99, 0x99)
Color.BLK = Color(0x00, 0x00, 0x00)
Color.RED = Color(0xFF, 0x00, 0x00)
Color.ORG = Color(0xFF, 0x99, 0x00)
Color.YLW = Color(0xFF, 0xFF, 0x00)
Color.GRN = Color(0x00, 0xFF, 0x00)
Color.BLU = Color(0x00, 0x00, 0xFF)
Color.PUR = Color(0x88, 0x00, 0x88)
