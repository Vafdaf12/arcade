#include "App.h"

#include <SDL.h>
#include <cassert>
#include <memory>

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

    auto arcade = std::make_unique<ArcadeScene>();
    pushScene(std::move(arcade));

    return m_pWindow;
}

void App::run() {
    assert(m_screen);

    SDL_Event event;
    bool running = true;

    uint32_t lastTick = SDL_GetTicks();

    uint32_t dt = 10;
    uint32_t acc = 0;

    m_inputController.init(
        [&running](uint32_t, InputState) { running = false; });

    while (running) {
        uint32_t frameTime = SDL_GetTicks() - lastTick;
        frameTime = frameTime > 300 ? 300 : frameTime;

        lastTick += frameTime;
        acc += frameTime;

        // Input
        m_inputController.update(dt);

        Scene* currentScene = topScene();
        assert(currentScene);

        if (currentScene) {
            // Update
            while (acc >= dt) {
                currentScene->update(dt);
                acc -= dt;
            }

            // Render
            currentScene->draw(m_screen);
        }
        m_screen.swapBuffers();
    }
}
void App::pushScene(std::unique_ptr<Scene> scene) {
    assert(scene);
    scene->init();
    m_inputController.setGameController(scene->getController());
    m_sceneStack.emplace_back(std::move(scene));
    SDL_SetWindowTitle(m_pWindow, topScene()->getName().c_str());
}
void App::popScene() {
    assert(!m_sceneStack.empty());
    if (m_sceneStack.empty()) return;
    m_sceneStack.pop_back();

    if (auto scene = topScene()) {
        m_inputController.setGameController(scene->getController());
        SDL_SetWindowTitle(m_pWindow, scene->getName().c_str());
    }
}
Scene* App::topScene() {
    if (m_sceneStack.empty()) return nullptr;
    return m_sceneStack.back().get();
}
