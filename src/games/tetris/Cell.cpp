#include "Cell.h"

#include "graphics/Screen.h"

Cell::Cell(const AARectangle& rect, const Color& color)
    : m_rect(rect), m_color(color) {}

void Cell::draw(Screen& screen) const {
    screen.draw(m_rect, m_color, true, m_color);
}
    Cell Cell::createDefaultCell(const Vector2& pos, const Color& color) {
        return Cell(AARectangle(pos, WIDTH, WIDTH), color);
    }
