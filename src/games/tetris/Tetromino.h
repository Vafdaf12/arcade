#pragma once

#include "games/tetris/FieldPosition.h"
#include "graphics/Color.h"
#include "shapes/AARectangle.h"

#include "./Cell.h"

#include <array>

class Screen;
class Playfield;

class Tetromino {
public:
    Tetromino() = default;
    Tetromino(const std::array<FieldPosition, 4>& cells,
        const Vector2& rotationCenter,
        const Color& color,
        const FieldPosition& offset = {0, 0});

    void rotate(bool clockwise = false);
    void draw(Screen& screen, const Playfield& field) const;

    std::array<FieldPosition, 4> getCells() const;

private:

    std::array<FieldPosition, 4> m_cells;
    Vector2 m_rotationCenter;
    FieldPosition m_offset;

    Color m_color;
};
