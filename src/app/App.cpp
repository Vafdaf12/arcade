#include "App.h"
#include <SDL.h>
#include <cassert>

#include "SDL_timer.h"
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

    Triangle triangle({2, 2}, {50, 30}, {20, 60});

    AARectangle rect({50, 50}, {100, 100});

    Color color = Color::BLUE;
    color.alpha = 128;
    Circle circle({100, 100}, 30);

    m_screen.swapBuffers();

    SDL_Event event;
    bool running = true;

    uint32_t lastTick = SDL_GetTicks();

    uint32_t dt = 10;
    uint32_t acc = 0;
    while (running) {
        uint32_t frameTime = SDL_GetTicks() - lastTick;
        frameTime = frameTime > 300 ? 300 : frameTime;

        lastTick += frameTime;
        acc += frameTime;

        // Input
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: running = false; break;
            }
        }

        // Update
        while (acc >= dt) {
            acc -= dt;
        }

        // Render
        m_screen.draw(line, Color::WHITE);
        m_screen.draw(triangle, Color::CYAN);
        m_screen.draw(rect, Color::RED);
        m_screen.draw(circle, Color::CYAN, true, color);
        m_screen.swapBuffers();
    }
}
