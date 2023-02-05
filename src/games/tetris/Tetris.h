#pragma once

#include "games/Game.h"

#include "./Tetromino.h"
#include "shapes/AARectangle.h"

class Tetris : public Game {
public:
    Tetris() = default;

    void init(GameController& pController) override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;
    const std::string& getName() const override;

private:
    Tetromino m_activeTetromino;
    AARectangle m_boundary;
    std::vector<Tetromino> m_availableTetrominos;
};
