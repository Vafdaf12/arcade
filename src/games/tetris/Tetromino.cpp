#include "Tetromino.h"

#include "graphics/Color.h"
#include "graphics/Screen.h"
#include <cmath>

Tetromino::Tetromino(const std::vector<Cell>& cells,
    const Vector2& center,
    const AARectangle& boundary)
    : m_cells(cells), m_center(center), m_boundary(boundary) {}

void Tetromino::move(const Vector2& delta) {
    float xl = getBoundingBox().getTopLeft().x;
    float xr = getBoundingBox().getBottomRight().x;

    float dx = delta.x;

    float xMin = m_boundary.getTopLeft().x;
    float xMax = m_boundary.getBottomRight().x;

    if (xl + dx < xMin) return;
    if (xr + dx > xMax) return;

    for (auto& cell : m_cells) {
        cell.move(delta);
    }
    m_center += delta;
}
void Tetromino::setPosition(const Vector2& position) {
    move(position - getBoundingBox().getTopLeft());
}

void Tetromino::rotate(bool clockwise) {
    for (auto& cell : m_cells) {
        Vector2 topLeft = cell.getRect().getTopLeft();
        if (clockwise) {
            topLeft.y += cell.getRect().getHeight();
            topLeft = topLeft.rotate(M_PI_2, m_center);
        } else {
            topLeft.x += cell.getRect().getWidth();
            topLeft = topLeft.rotate(-M_PI_2, m_center);
        }
        cell.setPosition(topLeft);
    }
}

void Tetromino::draw(Screen& screen) const {
    for (const auto& cell : m_cells) {
        cell.draw(screen);
    }
}
AARectangle Tetromino::getBoundingBox() const {
    float top = m_cells[0].getRect().getTopLeft().y;
    float left = m_cells[0].getRect().getTopLeft().x;
    float bottom = m_cells[0].getRect().getBottomRight().y;
    float right = m_cells[0].getRect().getBottomRight().x;

    for (size_t i = 1; i < m_cells.size(); i++) {

        Vector2 tl = m_cells[i].getRect().getTopLeft();
        Vector2 br = m_cells[i].getRect().getBottomRight();
        if (tl.x < left) left = tl.x;
        if (tl.y < top) top = tl.y;

        if (br.x > right) right = br.x;
        if (br.y > bottom) bottom = br.y;
    }
    return AARectangle({left, top}, {right, bottom});
}

