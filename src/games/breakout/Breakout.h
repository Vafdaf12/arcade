#pragma once

#include "games/Game.h"
#include "./Paddle.h"
#include "./Ball.h"
#include "./LevelBoundary.h"

class Breakout : public Game {
public:
    Breakout();
    void init(GameController& controller) override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;
    const std::string& getName() const override;

private:
    void resetGame();

    static const Vector2 BALL_INIT_VELOCITY;

    Paddle m_paddle;
    Ball m_ball;
    LevelBoundary m_boundary;
};
