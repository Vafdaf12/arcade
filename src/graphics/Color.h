#pragma once

#include <stdint.h>

struct SDL_PixelFormat;

class Color {
public:
    static Color blendColors(const Color& src, const Color& dst);

    Color() : red(0), green(0), blue(0), alpha(0) {}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    Color(uint32_t color, SDL_PixelFormat* pFormat);

    bool operator==(const Color& c) const;
    inline bool operator!=(const Color& c) const { return !(*this == c); }

    uint32_t mapToFormat(SDL_PixelFormat* pFormat) const;

    void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    uint8_t red, green, blue, alpha;

    static Color BLACK;
    static Color WHITE;

    static Color RED;
    static Color GREEN;
    static Color BLUE;

    static Color YELLOW;
    static Color MAGENTA;
    static Color CYAN;
    static Color PINK;
    static Color ORANGE;
};
