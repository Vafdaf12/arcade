#include "AARectangle.h"

#include <numeric>

AARectangle::AARectangle() : AARectangle(Vector2::ZERO, Vector2::ZERO) {}

AARectangle::AARectangle(
    const Vector2& topLeft, unsigned int width, unsigned int height) {
    m_points.push_back(topLeft);
    Vector2 delta(width - 1, height - 1);

    m_points.push_back(topLeft + delta);
}

AARectangle::AARectangle(const Vector2& topLeft, const Vector2& bottomRight) {
    m_points.push_back(topLeft);
    m_points.push_back(bottomRight);
}

Vector2 AARectangle::getCenterPoint() const {
    Vector2 total =
        std::accumulate(m_points.begin(), m_points.end(), Vector2::ZERO);
    return total / m_points.size();
}

std::vector<Vector2> AARectangle::getPoints() const {
    std::vector<Vector2> points;
    points.push_back(m_points[0]);
    points.push_back(m_points[0] + Vector2::POS_X * getWidth());
    points.push_back(m_points[1] + Vector2::ONE);
    points.push_back(m_points[0] + Vector2::POS_Y * getHeight());

    return points;
}

void AARectangle::moveTo(const Vector2& newPos) {
    Vector2 delta(getWidth()-1, getHeight()-1);
    m_points[0] = newPos;
    m_points[1] = newPos + delta;
}

bool AARectangle::intersects(const AARectangle& other) const {
    if (m_points[1].x < other.m_points[0].x) return false;
    if (m_points[0].x > other.m_points[1].x) return false;

    if (m_points[1].y < other.m_points[0].y) return false;
    if (m_points[0].y > other.m_points[1].y) return false;

    return true;
}
bool AARectangle::containsPoint(const Vector2& point) const {
    if (point.x < m_points[0].x) return false;
    if (point.y < m_points[0].y) return false;

    if (point.x > m_points[1].x) return false;
    if (point.y > m_points[1].y) return false;

    return true;
}
AARectangle AARectangle::inset(const AARectangle& rect, const Vector2& amt) {
    return AARectangle(rect.getTopLeft() + amt, rect.getBottomRight() - amt);
}
