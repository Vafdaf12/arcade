#pragma once

#include "../util/Vector2.h"
#include "Color.h"
#include "ScreenBuffer.h"

#include <stdint.h>

struct SDL_Window;
struct SDL_Surface;

class Screen {
public:
    Screen();
    ~Screen();

    SDL_Window* init(uint32_t w, uint32_t h, uint32_t mag);
    void swapBuffers();

    inline void setClearColor(const Color& c) { m_clearColor = c; }

    inline uint32_t width() const { return m_width; }
    inline uint32_t height() const { return m_height; }

    inline operator bool() const { return m_pWindow; }

    // --- DRAW CALLS ---

    void draw(int x, int y, const Color& color);
    void draw(const Vector2& p, const Color& color);

private:
    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

    void clearScreen();

    uint32_t m_width, m_height;

    SDL_Window* m_pWindow;
    SDL_Surface* m_pSurface;

    ScreenBuffer m_backBuffer;
    Color m_clearColor;
};
