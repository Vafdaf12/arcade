#pragma once

#include "../graphics/Screen.h"
#include <stdint.h>

struct SDL_Window;

class App {
public:
    static App& Singleton();

    bool init(uint32_t width, uint32_t height, uint32_t mag);

    void run();
    inline uint32_t width() const { return m_screen.width(); }
    inline uint32_t height() const { return m_screen.height(); }

private:
    Screen m_screen;
    SDL_Window* m_pWindow;
};
