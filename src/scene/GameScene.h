#pragma once

#include "Scene.h"
#include "games/Game.h"

#include <memory>

class GameScene : public Scene {
public:
    GameScene(std::unique_ptr<Game> pGame);
    virtual ~GameScene() {}

    void init() override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;

    const std::string& getName() const override;

private:
    std::unique_ptr<Game> m_pGame;
};
