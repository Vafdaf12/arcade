#include "App.h"
#include <SDL.h>
#include <cassert>
#include <memory>

#include "SDL_timer.h"
#include "scene/ArcadeScene.h"
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

    auto arcade = std::make_unique<ArcadeScene>();
    arcade->init();

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
            arcade->update(dt);
            acc -= dt;
        }

        // Render
        arcade->draw(m_screen);
        m_screen.swapBuffers();
    }
}
