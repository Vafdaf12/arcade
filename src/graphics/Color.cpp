#include "Color.h"
#include "SDL_pixels.h"

const SDL_PixelFormat* Color::s_pFormat = nullptr;
void Color::setColorFormat(const SDL_PixelFormat* pFormat) {
    s_pFormat = pFormat;
}

Color Color::blendColors(const Color& src, const Color& dst) {
    uint8_t alpha = src.alpha();

    float srcAlpha = float(alpha) / 255.0f;
    float dstAlpha = 1.0f - srcAlpha;

    Color out;
    out.setAlpha(255);
    out.setRed(float(src.red()) * srcAlpha + dst.red() * dstAlpha);
    out.setGreen(float(src.green()) * srcAlpha + dst.green() * dstAlpha);
    out.setBlue(float(src.blue()) * srcAlpha + dst.blue() * dstAlpha);

    return out;
}
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SetRGBA(r, g, b, a);
}

void Color::SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    m_red = r;
    m_green = g;
    m_blue = b;
    m_alpha = a;
}

bool Color::operator==(const Color& c) const {
    if (m_red != c.m_red) return false;
    if (m_green != c.m_green) return false;
    if (m_blue != c.m_blue) return false;
    if (m_alpha != c.m_alpha) return false;
    return true;
}
uint32_t Color::getColor() const {
    return SDL_MapRGBA(s_pFormat, m_red, m_green, m_blue, m_alpha);
}

Color::Color(uint32_t color) {
    SDL_GetRGBA(color, s_pFormat, &m_red, &m_green, &m_blue, &m_alpha);
}
