#include "Line2D.h"
#include "util/util.h"

#include <cmath>

Line2D::Line2D() : Line2D(Vector2::ZERO, Vector2::ZERO) {}
Line2D::Line2D(float x0, float y0, float x1, float y1)
    : m_v0(x0, y0), m_v1(x1, y1) {}
Line2D::Line2D(const Vector2& v0, const Vector2& v1) : m_v0(v0), m_v1(v1) {}

bool Line2D::operator==(const Line2D& line) const {
    if (m_v0 != line.m_v0) return false;
    if (m_v1 != line.m_v1) return false;
    return true;
}

float Line2D::minDistanceTo(const Vector2& point, bool segment) const {
    return point.distance(closestPointTo(point, segment));
}

Vector2 Line2D::closestPointTo(const Vector2& point, bool segment) const {
    auto v0ToPoint = point - m_v0;
    auto v0Tov1 = m_v1 - m_v0;

    float l2 = v0Tov1.sqrMagnitude();
    float dot = v0ToPoint.dot(v0Tov1);

    float t = dot / l2;

    if (segment) t = std::fmax(0, std::fmin(1.0f, t));

    return m_v0 + v0Tov1 * t;
}

float Line2D::slope() const {
    auto delta = m_v1 - m_v0;
    if (std::fabs(delta.x) < EPSILON) return 0;

    return delta.y / delta.x;
}

Vector2 Line2D::midpoint() const { return (m_v0 + m_v1) / 2; }
float Line2D::length() const { return m_v0.distance(m_v1); }
