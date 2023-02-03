#pragma once

#include "games/Game.h"
#include "./Paddle.h"
#include "./Ball.h"
#include "./LevelBoundary.h"
#include "./BreakoutLevel.h"

#include <vector>

class Breakout : public Game {
public:
    Breakout();
    void init(GameController& controller) override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;
    const std::string& getName() const override;

    enum GameState {
        Play,
        Serve,
        GameOver
    };
private:
    void resetGame();
    inline BreakoutLevel& getCurrentLevel() { return m_levels[m_currentLevel]; }
    void setToServeState();

    Paddle m_paddle;
    Ball m_ball;
    LevelBoundary m_boundary;

    std::vector<BreakoutLevel> m_levels;
    size_t m_currentLevel;
    GameState m_state;

};
