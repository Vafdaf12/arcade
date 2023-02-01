#pragma once

#include "Excluder.h"
#include "shapes/AARectangle.h"

#include <stdint.h>

class Screen;

class Paddle : public Excluder {
public:
    Paddle(const AARectangle& rect, const AARectangle& boundary);

    enum Direction { Left = 1 << 0, Right = 1 << 1, None = 0 };

    void update(uint32_t dt);
    void draw(Screen& screen);

    inline bool isMovingLeft() const { return m_direction == Left; }
    inline bool isMovingRight() const { return m_direction == Right; }

    inline void setMovementDirection(Direction dir) { m_direction |= dir; }
    inline void unsetMovementDirection(Direction dir) { m_direction &= ~dir; }
    inline void stopMovement() { m_direction = 0; }

    static constexpr float WIDTH = 50;
    static constexpr float HEIGHT = 10;

private:
    uint8_t m_direction;
    AARectangle m_boundary;

    static constexpr float SPEED = 100;
};
