#pragma once

#include "games/Game.h"

#include "./Tetromino.h"
#include "./Playfield.h"
#include "util/Timer.h"

#include "shapes/AARectangle.h"
#include <cstddef>

#include <array>
#include <random>

class Tetris : public Game {
public:
    enum GameState {
        Playing,
        GameOver
    };

    static constexpr size_t FIELD_WIDTH = 10;
    static constexpr size_t FIELD_HEIGHT = 20;

    Tetris();

    void init(GameController& pController) override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;
    const std::string& getName() const override;

private:
    void resetGame();

    inline bool isGameOver() const { return m_state == GameOver; }
    bool canPlace(const Tetromino& tetromino) const;
    bool canMove(const Tetromino& tetromino, int dx, int dy) const;
    bool canRotate(const Tetromino& tetromino, bool clockwise = false) const;

    void placeTetromino(const Tetromino& tetromino);

    void nextTetromino();
    Tetromino dropTetromino(const Tetromino& tetromino) const; 

    Playfield m_playfield;
    Playfield m_nextField;

    Tetromino m_tetromino;
    Tetromino m_nextTetromino;

    std::array<Tetromino, 7> m_availableTetrominos;

    Timer m_fallTimer;
    Timer m_placeTimer;

    GameState m_state;
    uint32_t m_score;

    std::default_random_engine m_randomEngine;
    std::uniform_int_distribution<int> m_rand;
};
