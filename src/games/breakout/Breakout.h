#pragma once

#include "./Ball.h"
#include "./BreakoutLevel.h"
#include "./LevelBoundary.h"
#include "./Paddle.h"
#include "games/Game.h"
#include "./HighscoreTable.h"

#include <vector>

class Breakout : public Game {
public:
    Breakout();

    void init(GameController& controller) override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;

    const std::string& getName() const override;

    enum GameState { Play, Serve, GameOver };

private:
    void resetGame(size_t level = 0);
    inline BreakoutLevel& getCurrentLevel() { return m_levels[m_currentLevel]; }
    void setToServeState();

    bool isBallOutOfBounds() const;
    void reduceLife(int amount = 1);
    inline bool isGameOver() const { return m_lives < 0; }

    static constexpr int NUM_LIVES = 3;

    Paddle m_paddle;
    Ball m_ball;
    LevelBoundary m_boundary;

    std::vector<BreakoutLevel> m_levels;
    size_t m_currentLevel;
    GameState m_state;
    int m_lives;
    float m_thresholdY;

    int m_score;
    HighscoreTable m_highscores;
    std::string m_playerName;

};
