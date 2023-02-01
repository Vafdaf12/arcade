#include "Ball.h"

#include "graphics/Color.h"
#include "graphics/Screen.h"
#include "shapes/AARectangle.h"
#include "shapes/Circle.h"
#include "util/util.h"

#include "./BoundaryEdge.h"

Ball::Ball() : Ball(Vector2::ZERO, INIT_RADIUS) {}
Ball::Ball(const Vector2& pos, float radius) {
    m_rect = AARectangle(pos - Vector2::ONE * (radius / 2), radius*2, radius*2);
}
void Ball::draw(Screen& screen) {
    Circle circle(getPosition(), getRadius());
    screen.draw(circle, Color::RED, true, Color::RED);
}
void Ball::update(uint32_t dt) {
    float s = millisecondsToSeconds(dt);
    m_rect.move(m_velocity * s);
}
void Ball::makeFlushWithEdge(
    const BoundaryEdge& edge, Vector2& pointOnEdge, bool limitToEdge) {

    pointOnEdge = edge.edge.closestPointTo(getPosition(), limitToEdge);
    setPosition(pointOnEdge + edge.normal * getRadius());
}
