#include "App.h"

#include <SDL.h>
#include <cassert>
#include <memory>

#include "SDL_timer.h"
#include "scene/ArcadeScene.h"
#include "scene/GameScene.h"
#include "shapes/AARectangle.h"
#include "shapes/Circle.h"
#include "shapes/Line2D.h"
#include "shapes/Triangle.h"

#include "games/Game.h"
#include "games/tetris/Tetris.h"

App& App::Singleton() {
    static App app;
    return app;
}

bool App::init(uint32_t width, uint32_t height, uint32_t mag) {
    m_pWindow = m_screen.init(width, height, mag);

    std::string basePath =getBasePath() + "../assets/";
    m_font.loadFromFile(basePath + "ArcadeFont.bmp", basePath + "ArcadeFont.txt");

    auto arcade = std::make_unique<ArcadeScene>();
    pushScene(std::move(arcade));

    // TEMP
    /*{
        auto breakout = std::make_unique<Tetris>();
        auto breakoutScene = std::make_unique<GameScene>(std::move(breakout));
        pushScene(std::move(breakoutScene));
    }*/

    return m_pWindow;
}

void App::run() {
    assert(m_screen);

    SDL_Event event;
    bool running = true;

    static constexpr uint32_t FRAME_TIME = 1000 / 60;

    m_inputController.init(
        [&running](uint32_t, InputState) { running = false; });

    uint32_t lastTick = SDL_GetTicks();
    while (running) {
        uint32_t dt = SDL_GetTicks() - lastTick;
        lastTick += dt;

        // Input
        m_inputController.update(dt);

        Scene* currentScene = topScene();
        assert(currentScene);

        if (currentScene) {
            // Update
            currentScene->update(dt);

            // Render
            currentScene->draw(m_screen);
        }
        m_screen.swapBuffers();

        uint32_t drawTime = SDL_GetTicks() - lastTick;
        if (drawTime > FRAME_TIME) continue;

        SDL_Delay(FRAME_TIME - drawTime);
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

    const std::string& App::getBasePath() {
        static char* base = SDL_GetBasePath();
        static std::string basePath = base;
        return basePath;
    }
