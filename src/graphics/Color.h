#pragma once

#include <stdint.h>

struct SDL_PixelFormat;

class Color {
public:
    static void setColorFormat(const SDL_PixelFormat* pFormat);

    Color() : m_color(0) {}
    Color(uint32_t color) : m_color(color) {}

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    inline bool operator==(const Color& c) const {
        return m_color == c.m_color;
    }
    inline bool operator!=(const Color& c) const { return !(*this == c); }

    inline operator uint32_t() const { return m_color; }
    inline uint32_t getColor() const { return m_color; }

    void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    void setRed(uint8_t red);
    void setGreen(uint8_t green);
    void setBlue(uint8_t blue);
    void setAlpha(uint8_t alpha);

    uint8_t red() const;
    uint8_t green() const;
    uint8_t blue() const;
    uint8_t alpha() const;

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
    uint32_t m_color;
};
