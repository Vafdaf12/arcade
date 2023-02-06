#include "Cell.h"

#include "graphics/Screen.h"

Cell::Cell() : Cell(AARectangle(), Color::WHITE) {}
Cell::Cell(const AARectangle& rect, const Color& color)
    : m_rect(rect), m_color(color), m_active(true) {}

void Cell::draw(Screen& screen) const {
    if(!m_active) return;
    screen.draw(m_rect, m_color, true, m_color);
}
