#include "Triangle.h"

#include "util/util.h"

#include <cmath>
#include <numeric>

Triangle::Triangle() : Triangle(Vector2::ZERO, Vector2::ZERO, Vector2::ZERO) {}
Triangle::Triangle(const Vector2& p0, const Vector2& p1, const Vector2 p2) {
    m_points.push_back(p0);
    m_points.push_back(p1);
    m_points.push_back(p2);
}

Vector2 Triangle::getCenterPoint() const {
    Vector2 total =
        std::accumulate(m_points.begin(), m_points.end(), Vector2::ZERO);
    return total / m_points.size();
}

bool Triangle::containsPoint(const Vector2& point) const {
    float thisArea = area();

    float a1 = area(point, m_points[0], m_points[1]);
    float a2 = area(point, m_points[1], m_points[2]);
    float a3 = area(point, m_points[0], m_points[2]);

    return isEqual(thisArea, a1 + a2 + a3);
}
float Triangle::area() const { return area(getP0(), getP1(), getP2()); }
float Triangle::area(const Vector2& p0, const Vector2& p1, const Vector2& p2) {
    float sum =
        p0.y * (p1.x - p2.x) + p1.y * (p0.x + p2.x) + p2.y * (p0.x + p1.x);

    return std::fabs(sum / 2);
}
