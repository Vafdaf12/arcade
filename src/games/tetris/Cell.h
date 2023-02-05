#pragma once

#include "graphics/Color.h"
#include "shapes/AARectangle.h"

class Screen;

class Cell {
public:
    static constexpr float WIDTH = 10;
    
    Cell(const AARectangle& rect, const Color& color);
    void draw(Screen& screen) const;

    inline const AARectangle& getRect() const { return m_rect;}

    inline void move(const Vector2& delta) { m_rect.move(delta); }
    inline void setPosition(const Vector2& pos) { m_rect.setPosition(pos); }

    static Cell createDefaultCell(const Vector2& pos, const Color& color);

private:
    AARectangle m_rect;
    Color m_color;

};
