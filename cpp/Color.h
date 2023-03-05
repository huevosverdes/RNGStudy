#ifndef __COLOR_H__
#define __COLOR_H__

#include <cstdint>
#include <cassert>

class Color
{

public:
    static const Color WHT;
    static const Color GRY;
    static const Color BLK;
    static const Color RED;
    static const Color ORG;
    static const Color YLW;
    static const Color GRN;
    static const Color BLU;
    static const Color PUR;

    Color();
    Color(uint8_t red, uint8_t grn, uint8_t blu, uint8_t alpha=255);
    Color(const Color &other);
    ~Color();

    Color &operator=(const Color &other);

    uint8_t red() const;
    uint8_t grn() const;
    uint8_t blu() const;
    uint8_t alpha() const;

    double redF() const;
    double grnF() const;
    double bluF() const;
    double alphaF() const;

    void setRed(uint8_t value);
    void setGrn(uint8_t value);
    void setBlu(uint8_t value);
    void setAlpha(uint8_t value);
    void set(uint8_t red, uint8_t grn, uint8_t blu);
    void set(uint8_t red, uint8_t grn, uint8_t blu, uint8_t alpha);

    void setRedF(double value);
    void setGrnF(double value);
    void setBluF(double value);
    void setAlphaF(double value);
    void setF(double red, double grn, double blu, double alpha=1.0);

private:
    uint32_t m_color;

    static uint8_t intify(double value);
};

#endif /* #ifndef __COLOR_H__ */
