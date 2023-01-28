#include "App.h"
#include <SDL.h>
#include <cassert>

#include "shapes/AARectangle.h"
#include "shapes/Circle.h"
#include "shapes/Line2D.h"
#include "shapes/Triangle.h"

App& App::Singleton() {
    static App app;
    return app;
}

bool App::init(uint32_t width, uint32_t height, uint32_t mag) {
    m_pWindow = m_screen.init(width, height, mag);
    return m_pWindow;
}

void App::run() {
    assert(m_screen);
    m_screen.draw(width() / 2, height() / 2, Color::ORANGE);

    Line2D line(
        {0, 0}, {static_cast<float>(width()), static_cast<float>(height())});
    m_screen.draw(line, Color::WHITE);

    Triangle triangle({2, 2}, {50, 30}, {20, 60});
    m_screen.draw(triangle, Color::CYAN);

    AARectangle rect({50, 50}, {100, 100});
    m_screen.draw(rect, Color::RED);

    Color color = Color::BLUE;
    color.alpha = 128;
    Circle circle({100, 100}, 30);
    m_screen.draw(circle, Color::CYAN, true, color);

    m_screen.swapBuffers();

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: running = false; break;
            }
        }
    }
}
