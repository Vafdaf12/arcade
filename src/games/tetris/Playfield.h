#pragma once

#include "./Cell.h"
#include "shapes/AARectangle.h"


#include <stdint.h>
#include <vector>

class Screen;

class Playfield {
public:
    static constexpr float CELL_WIDTH = 10;

    Playfield(const AARectangle& rect, size_t width, size_t height);

    void draw(Screen& screen) const;
    void update(uint32_t dt) const;

    void place(int x, int y, const Color& color);
    void clear();

    bool canPlace(int x, int y) const;

    const AARectangle& getCell(int x, int y) const;

    uint32_t clearLines();

    inline const AARectangle& getBoundingBox() const { return m_boundary; }

    inline size_t width() const { return m_width; }
    inline size_t height() const { return m_height; }

private:
    bool isRowComplete(int y) const;
    size_t index(int x, int y) const;
    void clearLineAt(int y);


    size_t m_width, m_height;

    std::vector<Cell> m_cells;
    AARectangle m_boundary;
};
