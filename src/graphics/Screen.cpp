#include "Screen.h"
#include "./BMPImage.h"
#include "shapes/Line2D.h"
#include "util/Vector2.h"

#include <SDL.h>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

Screen::Screen()
    : m_width(0), m_height(0), m_pWindow(nullptr), m_pSurface(nullptr) {}

Screen::~Screen() {
    if (m_pWindow) SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

SDL_Window* Screen::init(uint32_t w, uint32_t h, uint32_t mag) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "failed to initialize SDL\n";
        return nullptr;
    }

    m_width = w;
    m_height = h;
    m_pWindow = SDL_CreateWindow("Arcade",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w * mag,
        h * mag,
        0);

    if (m_pWindow) {
        m_pSurface = SDL_GetWindowSurface(m_pWindow);
        SDL_PixelFormat* pPixelFormat = m_pSurface->format;

        m_clearColor = Color::BLACK;

        m_backBuffer.init(pPixelFormat->format, m_width, m_height);

        m_renderer = SoftwareRenderer(&m_backBuffer);
        m_renderer.clear(m_clearColor);
    }
    return m_pWindow;
}

void Screen::swapBuffers() {
    assert(m_pWindow);

    SDL_FillRect(
        m_pSurface, nullptr, m_clearColor.mapToFormat(m_pSurface->format));

    SDL_BlitScaled(m_backBuffer.getSurface(), nullptr, m_pSurface, nullptr);
    SDL_UpdateWindowSurface(m_pWindow);

    m_renderer.clear(m_clearColor);
}

void Screen::draw(int x, int y, const Color& color) {
    m_renderer.drawPoint(Vector2(x, y), color);
}
void Screen::draw(const Vector2& p, const Color& color) {
    m_renderer.drawPoint(p, color);
}
void Screen::draw(const Line2D& line, const Color& color) {
    m_renderer.drawLine(line.v0(), line.v1(), color);
}

void Screen::draw(
    const Shape& shape, const Color& color, bool fill, const Color& fillColor) {
    if (fill) m_renderer.fillPolygon(shape.getPoints(), fillColor);
    m_renderer.drawPolygon(shape.getPoints(), color);
}

void Screen::draw(
    const BMPImage& image, const Sprite& sprite, const Vector2& pos, const Color& tint) {
    m_renderer.drawSprite(image, sprite, pos, tint);
}
void Screen::draw(const BMPImage& image, const Vector2& pos, const Color& tint ) {
    m_renderer.drawImage(image, pos, tint);
}
void Screen::draw(const std::string& text,
    const BitmapFont& font,
    const AARectangle& boundingBox,
    BitmapFont::FontAlignment alignment, const Color& tint) {

    m_renderer.drawText(text, font, boundingBox, alignment, tint);
}
