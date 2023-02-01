#pragma once

#include "games/Game.h"
#include "./Paddle.h"
#include "games/breakout/Ball.h"

class Breakout : public Game {
public:
    Breakout();
    void init(GameController& controller) override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;
    const std::string& getName() const override;

private:
    void resetGame();

    Paddle m_paddle;
    Ball m_ball;
};
