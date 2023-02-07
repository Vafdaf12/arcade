#include "Color.h"
#include "SDL_pixels.h"

Color Color::BLACK(0, 0, 0);
Color Color::WHITE(255, 255, 255);

Color Color::RED(255, 0, 0);
Color Color::GREEN(0, 255, 0);
Color Color::BLUE(0, 0, 255);

Color Color::YELLOW(255, 255, 0);
Color Color::MAGENTA(255, 0, 255);
Color Color::CYAN(37, 240, 217);
Color Color::PINK(252, 197, 224);
Color Color::ORANGE(245, 190, 100);

Color Color::Black() { return Color(0, 0, 0); }
Color Color::White() { return Color(255, 255, 255); }

Color Color::Red() { return Color(255, 0, 0); }
Color Color::Green() { return Color(0, 255, 0); }
Color Color::Blue() { return Color(0, 0, 255); }

Color Color::Yellow() { return Color(255, 255, 0); }
Color Color::Magenta() { return Color(255, 0, 255); }
Color Color::Cyan() { return Color(37, 240, 217); }
Color Color::Pink() { return Color(252, 197, 224); }
Color Color::Orange() { return Color(245, 190, 100); }

Color Color::blendColors(const Color& src, const Color& dst) {
    uint8_t alpha = src.alpha;

    float srcAlpha = float(alpha) / 255.0f;
    float dstAlpha = 1.0f - srcAlpha;

    Color out;
    out.alpha = 255;
    out.red = float(src.red) * srcAlpha + dst.red * dstAlpha;
    out.green = float(src.green) * srcAlpha + dst.green * dstAlpha;
    out.blue = float(src.blue) * srcAlpha + dst.blue * dstAlpha;

    return out;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : red(r), green(g), blue(b), alpha(a) {}

void Color::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

bool Color::operator==(const Color& c) const {
    if (red != c.red) return false;
    if (green != c.green) return false;
    if (blue != c.blue) return false;
    if (alpha != c.alpha) return false;
    return true;
}
uint32_t Color::mapToFormat(SDL_PixelFormat* pFormat) const {
    return SDL_MapRGBA(pFormat, red, green, blue, alpha);
}
Color::Color(uint32_t color, SDL_PixelFormat* pFormat) {
    SDL_GetRGBA(color, pFormat, &red, &green, &blue, &alpha);
}
