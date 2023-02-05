#pragma once

#include "graphics/Color.h"
#include "shapes/AARectangle.h"

#include "./Cell.h"

#include <array>

class Screen;

class Tetromino {
public:
    Tetromino() = default;
    Tetromino(const std::vector<Cell>& cells,
        const Vector2& center,
        const AARectangle& boundary = AARectangle());

    void move(const Vector2& delta);
    void setPosition(const Vector2& position);

    void rotate(bool clockwise = false);

    void draw(Screen& screen) const;

    AARectangle getBoundingBox() const;

private:
    std::vector<Cell> m_cells;
    Vector2 m_center;
    Color m_color;

    AARectangle m_boundary;
};
