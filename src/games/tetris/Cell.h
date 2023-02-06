#pragma once

#include "graphics/Color.h"
#include "shapes/AARectangle.h"

class Screen;

class Cell {
public:
    Cell();
    Cell(const AARectangle& rect, const Color& color);

    void draw(Screen& screen) const;

    inline const AARectangle& getRect() const { return m_rect; }

    inline void setColor(const Color& color) { m_color = color; }
    inline const Color& getColor() const { return m_color; }

    inline void move(const Vector2& delta) { m_rect.move(delta); }
    inline void setPosition(const Vector2& pos) { m_rect.setPosition(pos); }

    inline void setActive(bool active) { m_active = active; }
    inline bool isActive() const { return m_active; }

private:
    AARectangle m_rect;
    Color m_color;
    bool m_active;
};
