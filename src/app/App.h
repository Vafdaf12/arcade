#pragma once

#include "graphics/Screen.h"
#include "scene/Scene.h"

#include <memory>
#include <stdint.h>
#include <vector>

struct SDL_Window;

class Scene;

class App {
public:
    static App& Singleton();

    bool init(uint32_t width, uint32_t height, uint32_t mag);

    void run();
    inline uint32_t width() const { return m_screen.width(); }
    inline uint32_t height() const { return m_screen.height(); }

    void pushScene(std::unique_ptr<Scene> scene);
    void popScene();
    Scene* topScene();

private:
    Screen m_screen;
    SDL_Window* m_pWindow;

    std::vector<std::unique_ptr<Scene>> m_sceneStack;
};
