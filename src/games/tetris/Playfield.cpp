#include "Playfield.h"

#include "graphics/Screen.h"

Playfield::Playfield(const AARectangle& rect, size_t width, size_t height)
    : m_boundary(rect), m_width(width), m_height(height) {
    m_cells.reserve(width * height);

    AARectangle cellRect(
        rect.getTopLeft(), rect.getWidth() / width, rect.getHeight() / height);
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t i = y * m_width + x;

            m_cells.emplace_back(cellRect, Color::WHITE);
            m_cells.back().setActive(false);

            cellRect.move({cellRect.getWidth(), 0});
        }

        cellRect.move({0, cellRect.getHeight()});
        cellRect.setPosition({rect.getTopLeft().x, cellRect.getTopLeft().y});
    }
}

void Playfield::draw(Screen& screen) const {
    for (const auto& cell : m_cells)
        cell.draw(screen);
    screen.draw(m_boundary, Color::WHITE);
}

void Playfield::place(int x, int y, const Color& color) {
    size_t i = index(x, y);
    m_cells[i].setActive(true);
    m_cells[i].setColor(color);
}
bool Playfield::canPlace(int x, int y) const {
    return m_cells[index(x, y)].isActive();
}
size_t Playfield::index(int x, int y) const {
    assert(x >= 0 && y >= 0);
    assert(x < m_width && y < m_height);
    return (m_height - y - 1) * m_width + x;
}

uint32_t Playfield::clearLines() {
    uint32_t count = 0;
    for (size_t y = 0; y < m_height; y++) {
        while (isRowComplete(y)) {
            clearLineAt(y);
            count++;
        }
    }

    return count;
}

bool Playfield::isRowComplete(int y) const {
    for (size_t x = 0; x < m_width; x++) {
        size_t i = index(x, y);
        if (!m_cells[i].isActive()) return false;
    }
    return true;
}

void Playfield::clearLineAt(int y) {
    for (size_t yCur = y; yCur < m_height - 1; yCur++) {
        for (size_t x = 0; x < m_width; x++) {
            Cell& cur = m_cells[index(x, yCur)];
            Cell& above = m_cells[index(x, yCur + 1)];

            cur.setColor(above.getColor());
            cur.setActive(above.isActive());
        }
    }
}

const AARectangle& Playfield::getCell(int x, int y) const {
    size_t i = index(x, y);
    return m_cells[i].getRect();
}
