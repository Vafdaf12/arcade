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

    Playfield m_playfield;
    Tetromino m_tetromino;
};
