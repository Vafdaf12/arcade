#pragma once

#include <stdint.h>

struct SDL_PixelFormat;

class Color {
public:
    static void setColorFormat(const SDL_PixelFormat* pFormat);
    static Color blendColors(const Color& src, const Color& dst);

    Color() : m_red(0), m_green(0), m_blue(0), m_alpha(0) {}
    Color(uint32_t color);

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    bool operator==(const Color& c) const;
    inline bool operator!=(const Color& c) const { return !(*this == c); }

    inline operator uint32_t() const { return getColor(); }
    uint32_t getColor() const;

    void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    inline void setRed(uint8_t red) { m_red = red; }
    inline void setGreen(uint8_t green) { m_green = green; }
    inline void setBlue(uint8_t blue) { m_blue = blue; }
    inline void setAlpha(uint8_t alpha) { m_alpha = alpha; }

    uint8_t red() const { return m_red; }
    uint8_t green() const { return m_green; }
    uint8_t blue() const { return m_blue; }
    uint8_t alpha() const { return m_alpha; }

    static Color Black() { return Color(0, 0, 0); }
    static Color White() { return Color(255, 255, 255); }

    static Color Red() { return Color(255, 0, 0); }
    static Color Green() { return Color(0, 255, 0); }
    static Color Blue() { return Color(0, 0, 255); }

    static Color Yellow() { return Color(255, 255, 0); }
    static Color Magenta() { return Color(255, 0, 255); }
    static Color Cyan() { return Color(37, 240, 217); }
    static Color Pink() { return Color(252, 197, 224); }
    static Color Orange() { return Color(245, 190, 100); }

private:
    static const SDL_PixelFormat* s_pFormat;
    uint8_t m_red, m_green, m_blue, m_alpha;
};
