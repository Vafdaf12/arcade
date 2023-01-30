#pragma once

#include "./Scene.h"

#include <memory>

class Screen;

enum class ArcadeGame { Tetris, Breakout, Asteroids, Pacman, GameList };

class ArcadeScene : public Scene {
public:
    ArcadeScene();

    virtual void init() override;
    virtual const std::string& getName() const override;

    virtual void update(uint32_t dt) override;
    virtual void draw(Screen& screen) override;
private:
    std::unique_ptr<Scene> getScene(ArcadeGame game);
};
