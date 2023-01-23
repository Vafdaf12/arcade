#include "Screen.h"

#include <SDL.h>
#include <cassert>

Screen::Screen()
    : m_width(0), m_height(0), m_pWindow(nullptr), m_pSurface(nullptr) {}

Screen::~Screen() {
    if (m_pWindow) {
        SDL_DestroyWindow(m_pWindow);
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

void Screen::clearScreen() {
    assert(m_pWindow);
    SDL_FillRect(m_pSurface, nullptr, m_clearColor.getColor());
}
