#include "Screen.h"
#include "../shapes/Line2D.h"
#include "../util/Vector2.h"
#include "SDL_render.h"

#include <SDL.h>
#include <algorithm>
#include <cassert>
#include <vector>

Screen::Screen()
    : m_width(0), m_height(0), m_pWindow(nullptr), m_pSurface(nullptr),
      m_pRenderer(nullptr) {}

Screen::~Screen() {
    if (m_pWindow) {
        SDL_DestroyWindow(m_pWindow);
        SDL_DestroyRenderer(m_pRenderer);
        m_pWindow = nullptr;
    }
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

        m_pRenderer = SDL_CreateSoftwareRenderer(m_backBuffer.getSurface());
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
    assert(m_pRenderer);
    SDL_SetRenderDrawColor(
        m_pRenderer, color.red(), color.green(), color.blue(), color.alpha());
    SDL_RenderDrawPoint(m_pRenderer, x, y);
}
void Screen::draw(const Vector2& p, const Color& color) {
    assert(m_pRenderer);
    SDL_SetRenderDrawColor(
        m_pRenderer, color.red(), color.green(), color.blue(), color.alpha());
    SDL_RenderDrawPoint(m_pRenderer, p.x, p.y);
}
void Screen::draw(const Line2D& line, const Color& color) {
    assert(m_pRenderer);
    auto v0 = line.v0();
    auto v1 = line.v1();
    SDL_SetRenderDrawColor(
        m_pRenderer, color.red(), color.green(), color.blue(), color.alpha());
    SDL_RenderDrawLine(m_pRenderer, v0.x, v0.y, v1.x, v1.y);
}

SDL_Point toPoint(const Vector2& p) {
    return { static_cast<int>(p.x), static_cast<int>(p.y) };
}

void Screen::draw(const Shape& shape, const Color& color) {
    assert(m_pRenderer);

    std::vector<Vector2> shapePoints = shape.getPoints();
    std::vector<SDL_Point> points(shape.getPoints().size());

    std::transform(shapePoints.begin(), shapePoints.end(), points.begin(), toPoint);
    points.push_back(points[0]);

    SDL_SetRenderDrawColor(
        m_pRenderer, color.red(), color.green(), color.blue(), color.alpha());
    SDL_RenderDrawLines(m_pRenderer, points.data(), points.size());
}

void Screen::clearScreen() {
    assert(m_pWindow);
    SDL_FillRect(m_pSurface, nullptr, m_clearColor.getColor());
}
