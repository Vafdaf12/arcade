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

    inline const Color& getColor() const { return m_color; }

    inline void move(int x, int y) { m_offset += {x, y}; }
    inline void setOffset(int x, int y) { m_offset = {x, y}; }

    std::array<FieldPosition, 4> getCells() const;

    int width() const;
    int height() const;

    static Tetromino SHAPE_I;
    static Tetromino SHAPE_J;
    static Tetromino SHAPE_L;
    static Tetromino SHAPE_O;
    static Tetromino SHAPE_Z;
    static Tetromino SHAPE_S;
    static Tetromino SHAPE_T;

private:

    std::array<FieldPosition, 4> m_cells;
    Vector2 m_rotationCenter;
    FieldPosition m_offset;

    Color m_color;
};
