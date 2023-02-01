#include "Paddle.h"

#include "graphics/Color.h"
#include "graphics/Screen.h"
#include "util/util.h"

Paddle::Paddle(const AARectangle& rect, const AARectangle& boundary)
    : Excluder(rect), m_direction(None), m_boundary(boundary) {}

void Paddle::update(uint32_t dt) {
    if (m_direction == None) return;
    if((m_direction & Right) && (m_direction & Left)) return;

    int dir = m_direction == Right ? 1 : -1;
    float dx = dir * SPEED * millisecondsToSeconds(dt);

    float xMin = m_boundary.getTopLeft().x;
    float xMax = m_boundary.getBottomRight().x;

    float xl = getRect().getTopLeft().x;
    float xr = getRect().getBottomRight().x;

    if(xl + dx < xMin) dx = xMin - xl;
    if(xr + dx > xMax) dx = xMax - xr;

    move(Vector2::POS_X * dx);
}

void Paddle::draw(Screen& screen) {
    screen.draw(getRect(), Color::BLUE, true, Color::BLUE);
}
