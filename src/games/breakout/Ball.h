#pragma once

#include "shapes/AARectangle.h"
#include "util/Vector2.h"

class Screen;
struct BoundaryEdge;

class Ball {
public:
    Ball();
    Ball(const Vector2& pos, float radius);

    void draw(Screen& screen);
    void update(uint32_t dt);

    void makeFlushWithEdge(
        const BoundaryEdge& edge, Vector2& pointOnEdge, bool limitToEdge);

    void bounce(const BoundaryEdge& edge);
    inline void stop() { m_velocity = Vector2::ZERO; }

    inline const AARectangle& getBoundingBox() const { return m_rect; }

    inline void setVelocity(const Vector2& vel) { m_velocity = vel; }
    inline Vector2 getVelocity() const { return m_velocity; }

    inline float getRadius() const { return m_rect.getWidth() / 2.0f; }

    inline void setPosition(const Vector2& pos) {
        m_rect.moveTo(pos - Vector2::ONE * (getRadius()-1));
    }
    inline Vector2 getPosition() const { return m_rect.getCenterPoint(); }

private:
    AARectangle m_rect;
    Vector2 m_velocity;

    static constexpr float INIT_RADIUS = 5.0f;
};
