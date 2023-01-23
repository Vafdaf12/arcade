#include "Color.h"
#include "SDL_pixels.h"

const SDL_PixelFormat* Color::s_pFormat = nullptr;
void Color::setColorFormat(const SDL_PixelFormat* pFormat) {
    s_pFormat = pFormat;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SetRGBA(r, g, b, a);
}

void Color::SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    m_color = SDL_MapRGBA(s_pFormat, r, g, b, a);
}

void Color::setRed(uint8_t red) {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, s_pFormat, &r, &g, &b, &a);
    SetRGBA(red, g, b, a);
}
void Color::setGreen(uint8_t green) {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, s_pFormat, &r, &g, &b, &a);
    SetRGBA(r, green, b, a);
}
void Color::setBlue(uint8_t blue) {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, s_pFormat, &r, &g, &b, &a);
    SetRGBA(r, g, blue, a);
}
void Color::setAlpha(uint8_t alpha) {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, s_pFormat, &r, &g, &b, &a);
    SetRGBA(r, g, b, alpha);
}

uint8_t Color::red() const {
    uint8_t r, g, b, a;
    SDL_GetRGBA(m_color, s_pFormat, &r, &g, &b, &a);
    return r;
}
uint8_t Color::green() const {
    uint8_t r, g, b, a;
    SDL_GetRGBA(m_color, s_pFormat, &r, &g, &b, &a);
    return g;
}
uint8_t Color::blue() const {
    uint8_t r, g, b, a;
    SDL_GetRGBA(m_color, s_pFormat, &r, &g, &b, &a);
    return b;
}
uint8_t Color::alpha() const {
    uint8_t r, g, b, a;
    SDL_GetRGBA(m_color, s_pFormat, &r, &g, &b, &a);
    return a;
}
