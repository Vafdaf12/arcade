#include "Tetromino.h"

#include "./FieldPosition.h"
#include "./Playfield.h"

#include "graphics/Color.h"
#include "graphics/Screen.h"

#include <algorithm>
#include <utility>

Tetromino::Tetromino(const std::array<FieldPosition, 4>& cells,
    const Vector2& rotationCenter,
    const Color& color,
    const FieldPosition& offset)
    : m_cells(cells), m_rotationCenter(rotationCenter), m_offset(offset),
      m_color(color) {}

void Tetromino::rotate(bool clockwise) {
    for (auto& cell : m_cells) {
        Vector2 relative = Vector2(cell.x, cell.y) - m_rotationCenter;
        std::swap(relative.x, relative.y);

        if (clockwise) relative.y = -relative.y;
        else relative.x = -relative.x;
        relative += m_rotationCenter;
        cell = {static_cast<int>(relative.x), static_cast<int>(relative.y)};
    }
}

void Tetromino::draw(Screen& screen, const Playfield& field) const {
    for (const auto& cell : m_cells) {
        FieldPosition absolute = cell + m_offset;
        AARectangle rect = field.getCell(absolute.x, absolute.y);
        screen.draw(rect, m_color, true, m_color);
    }
}

std::array<FieldPosition, 4> Tetromino::getCells() const {
    std::array<FieldPosition, 4> cells;
    std::transform(m_cells.begin(),
        m_cells.end(),
        cells.begin(),
        [this](const FieldPosition& pos) { return pos + m_offset; });
    return cells;
}
Tetromino Tetromino::SHAPE_I({
    FieldPosition(0, 0),
    FieldPosition(1, 0),
    FieldPosition(2, 0),
    FieldPosition(3, 0)},
    {1.5f, -0.5f},
    Color::Cyan());

Tetromino Tetromino::SHAPE_J({
    FieldPosition(0, 0),
    FieldPosition(1, 0),
    FieldPosition(2, 0),
    FieldPosition(0, 1)},
    {1, 0},
    Color::Blue());

Tetromino Tetromino::SHAPE_L({
    FieldPosition(0, 0),
    FieldPosition(1, 0),
    FieldPosition(2, 0),
    FieldPosition(2, 1)},
    {1, 0},
    Color::Orange());

Tetromino Tetromino::SHAPE_O({
    FieldPosition(0, 0),
    FieldPosition(1, 0),
    FieldPosition(1, 1),
    FieldPosition(0, 1)},
    {1.5f, 0.5f},
    Color::Yellow());

Tetromino Tetromino::SHAPE_S({
    FieldPosition(0, 0),
    FieldPosition(1, 0),
    FieldPosition(1, 1),
    FieldPosition(2, 1)},
    {1, 0},
    Color::Green());

Tetromino Tetromino::SHAPE_T({
    FieldPosition(0, 0),
    FieldPosition(1, 0),
    FieldPosition(2, 0),
    FieldPosition(1, 1)},
    {1, 0},
    Color::Magenta());

Tetromino Tetromino::SHAPE_Z({
    FieldPosition(0, 1),
    FieldPosition(1, 1),
    FieldPosition(1, 0),
    FieldPosition(2, 0)},
    {1, 0},
    Color::Red());
