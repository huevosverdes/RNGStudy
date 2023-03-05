#include "Color.h"

const Color Color::WHT(0xFF, 0xFF, 0xFF);
const Color Color::GRY(0x99, 0x99, 0x99);
const Color Color::BLK(0x00, 0x00, 0x00);
const Color Color::RED(0xFF, 0x00, 0x00);
const Color Color::ORG(0xFF, 0x99, 0x00);
const Color Color::YLW(0xFF, 0xFF, 0x00);
const Color Color::GRN(0x00, 0xFF, 0x00);
const Color Color::BLU(0x00, 0x00, 0xFF);
const Color Color::PUR(0x88, 0x00, 0x88);

Color::Color()
{
    m_color = 0xFF000000;
}

Color::Color(uint8_t red, uint8_t grn, uint8_t blu, uint8_t alpha)
{
    m_color = (alpha << 24) | (red << 16) | (grn << 8) | blu;
}

Color::Color(const Color &other)
{
    m_color = other.m_color;
}

Color::~Color()
{

}

Color &Color::operator=(const Color &other)
{
    m_color = other.m_color;
    return *this;
}

uint8_t Color::red() const
{
    return (m_color >> 16) & 0xFF;
}

uint8_t Color::grn() const
{
    return (m_color >> 8) & 0xFF;
}

uint8_t Color::blu() const
{
    return m_color & 0xFF;
}

uint8_t Color::alpha() const
{
    return (m_color >> 24) & 0xFF;
}

double Color::redF() const
{
    return red() / 255.0;
}

double Color::grnF() const
{
    return grn() / 255.0;
}

double Color::bluF() const
{
    return blu() / 255.0;
}

double Color::alphaF() const
{
    return alpha() / 255.0;
}

void Color::setRed(uint8_t value)
{
    m_color = (m_color & 0xFF00FFFF) | (value << 16);
}

void Color::setGrn(uint8_t value)
{
    m_color = (m_color & 0xFFFF00FF) | (value << 8);
}

void Color::setBlu(uint8_t value)
{
    m_color = (m_color & 0xFFFFFF00) | value;
}

void Color::setAlpha(uint8_t value)
{
    m_color = (m_color & 0x00FFFFFF) | (value << 24);
}

void Color::set(uint8_t red, uint8_t grn, uint8_t blu)
{
    m_color = (m_color & 0xFF000000) | (red << 16) | (grn << 8) | blu;
}

void Color::set(uint8_t red, uint8_t grn, uint8_t blu, uint8_t alpha)
{
    m_color = (alpha << 24) | (red << 16) | (grn << 8) | blu;
}

void Color::setRedF(double value)
{
    m_color = (m_color & 0xFF00FFFF) | (intify(value) << 16);
}

void Color::setGrnF(double value)
{
    m_color = (m_color & 0xFFFF00FF) | (intify(value) << 8);
}

void Color::setBluF(double value)
{
    m_color = (m_color & 0xFFFFFF00) | intify(value);
}

void Color::setAlphaF(double value)
{
    m_color = (m_color & 0x00FFFFFF) | (intify(value) << 24);
}

void Color::setF(double red, double grn, double blu, double alpha)
{
    m_color = (intify(alpha) << 24) | (intify(red) << 16) | (intify(grn) << 8) | intify(blu);
}

uint8_t Color::intify(double value)
{
    assert(0.0 <= value && value <= 1.0);
    return static_cast<uint8_t>(value * 255);
}
