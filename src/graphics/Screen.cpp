#include "Screen.h"
#include "../shapes/Line2D.h"
#include "../util/Vector2.h"
#include "SDL_render.h"

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

        Color::setColorFormat(pPixelFormat);
        m_clearColor = Color::Black();

        m_backBuffer.init(pPixelFormat->format, m_width, m_height);
        m_backBuffer.clear(m_clearColor);
    }
    return m_pWindow;
}

void Screen::swapBuffers() {
    assert(m_pWindow);

    clearScreen();

    SDL_BlitScaled(m_backBuffer.getSurface(), nullptr, m_pSurface, nullptr);
    SDL_UpdateWindowSurface(m_pWindow);

    m_backBuffer.clear(m_clearColor);
}

void Screen::draw(int x, int y, const Color& color) {
    assert(m_backBuffer);
    m_backBuffer.setPixel(color, x, y);
}
void Screen::draw(const Vector2& p, const Color& color) {
    assert(m_backBuffer);
    m_backBuffer.setPixel(color, p.x, p.y);
}
void Screen::draw(const Line2D& line, const Color& color) {
    assert(m_backBuffer);

    int dx, dy;

    int x0 = std::roundf(line.v0().x);
    int y0 = std::roundf(line.v0().y);

    int x1 = std::roundf(line.v1().x);
    int y1 = std::roundf(line.v1().y);

    dx = x1 - x0;
    dy = y1 - y0;

    const char ix((dx > 0) - (dx < 0));
    const char iy((dy > 0) - (dy < 0));

    dx = std::abs(dx);
    dy = std::abs(dy);

    m_backBuffer.setPixel(color, x0, y0);
    if (dx >= dy) {
        int p = 2 * dy - dx;

        while(x0 != x1) {
            if (p >= 0) {
                y0 += iy;
                p -= 2 * dx;
            }
            p += 2 * dy;
            x0 += ix;

            m_backBuffer.setPixel(color, x0, y0);
        }
    }
    else {
        int p = 2 * dx - dy;

        while(y0 != y1) {
            if (p >= 0) {
                x0 += ix;
                p -= 2 * dy;
            }
            p += 2 * dx;
            y0 += iy;

            m_backBuffer.setPixel(color, x0, y0);
        }
    }
}

void Screen::draw(const Shape& shape, const Color& color) {
    std::vector<Vector2> points = shape.getPoints();
    points.push_back(points[0]);
    for (size_t i = 0; i < points.size() - 1; i++) {
        draw({points[i], points[i + 1]}, color);
    }
}

void Screen::clearScreen() {
    assert(m_pWindow);
    SDL_FillRect(m_pSurface, nullptr, m_clearColor.getColor());
}
