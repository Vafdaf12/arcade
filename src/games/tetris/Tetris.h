#pragma once

#include "games/Game.h"

#include "./Tetromino.h"
#include "./Playfield.h"
#include "util/Timer.h"

#include "shapes/AARectangle.h"
#include <cstddef>

class Tetris : public Game {
public:
    static constexpr size_t FIELD_WIDTH = 10;
    static constexpr size_t FIELD_HEIGHT = 20;

    Tetris();

    void init(GameController& pController) override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;
    const std::string& getName() const override;

private:
    bool canMove(const Tetromino& tetromino, int dx, int dy) const;
    bool canRotate(const Tetromino& tetromino, bool clockwise = false) const;
    void placeTetromino(const Tetromino& tetromino);
    void resetActiveTetromino();

    Playfield m_playfield;
    Tetromino m_tetromino;
    std::array<Tetromino, 7> m_availableTetrominos;

    Timer m_fallTimer;
};