#include "./Block.h"

#include "./Ball.h"
#include "./BoundaryEdge.h"
#include "graphics/Screen.h"

Block::Block() : Block(AARectangle(), 1, Color::WHITE, Color::WHITE) {}
Block::Block(
    const AARectangle& rect, int hp, const Color& outline, const Color& fill)
    : Excluder(rect), m_health(hp), m_outline(outline), m_fill(fill) {}

void Block::draw(Screen& screen) {
    screen.draw(getRect(), m_outline, true, m_fill);
}
void Block::bounce(Ball& ball) {
    BoundaryEdge edge;
    if (!hasCollided(ball.getBoundingBox(), edge)) return;
    ball.bounce(edge);
}
void Block::reduceHealth() {
    if (m_health > 0) m_health--;
}
