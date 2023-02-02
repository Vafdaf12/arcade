#include "Paddle.h"

#include "graphics/Color.h"
#include "graphics/Screen.h"
#include "util/util.h"

#include "./Ball.h"

#include <cassert>
#include <cmath>

Paddle::Paddle(const AARectangle& rect, const AARectangle& boundary)
    : Excluder(rect), m_direction(None), m_boundary(boundary) {}

void Paddle::update(uint32_t dt, Ball& ball) {
    // Why does this need to be here?
    if (getRect().containsPoint(ball.getPosition())) {
        Vector2 p;
        ball.makeFlushWithEdge(getEdge(BoundaryEdge::Bottom), p, true);
    }

    if (m_direction == None) return;
    if ((m_direction & Right) && (m_direction & Left)) return;

    int dir = m_direction == Right ? 1 : -1;
    float dx = dir * SPEED * millisecondsToSeconds(dt);

    float xMin = m_boundary.getTopLeft().x;
    float xMax = m_boundary.getBottomRight().x;

    float xl = getRect().getTopLeft().x;
    float xr = getRect().getBottomRight().x;

    if (xl + dx < xMin) dx = xMin - xl;
    if (xr + dx > xMax) dx = xMax - xr;

    move(Vector2::POS_X * dx);
}

bool Paddle::bounce(Ball& ball) {
    BoundaryEdge edge;
    if (!hasCollided(ball.getBoundingBox(), edge)) return false;
    if (edge.edge != getEdge(BoundaryEdge::Top).edge) return false;

    Vector2 point;
    ball.makeFlushWithEdge(edge, point, true);

    float length = edge.edge.length();
    assert(!isEqual(length, 0));
    float tx = std::abs(point.x - edge.edge.v0().x) / length;

    bool onLeftEdge = tx < BOUNCE_PADDING;
    bool onRightEdge = tx > (1 - BOUNCE_PADDING);

    bool goingLeft = ball.getVelocity().x <= 0;
    bool goingRight = ball.getVelocity().x >= 0;

    if ((onLeftEdge && goingRight) || (onRightEdge && goingLeft)) {
        ball.setVelocity(-ball.getVelocity());
    } else ball.bounce(edge);
    return true;
}

void Paddle::draw(Screen& screen) {
    screen.draw(getRect(), Color::BLUE, true, Color::BLUE);
}
