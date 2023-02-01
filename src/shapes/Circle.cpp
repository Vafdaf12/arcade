#include "Circle.h"

#include <cmath>

const float CIRCLE_DIST = 2.0f;


Circle::Circle() : Circle(Vector2::ZERO, 0) {}
Circle::Circle(const Vector2& center, float radius) {
    m_points.push_back(center);
    m_radius = radius;
}

bool Circle::intersects(const Circle& circle) const { 
    float threshold = circle.m_radius + m_radius;
    return m_points[0].distance(circle.getCenterPoint()) <= threshold;
}
bool Circle::containsPoint(const Vector2& point) const { 
    return getCenterPoint().distance(point) <= m_radius;

}
std::vector<Vector2> Circle::getPoints() const { 
    static unsigned int NUM_SEGMENTS = 30;

    std::vector<Vector2> points;
    float da = 2 * M_PI / NUM_SEGMENTS;

    Vector2 delta = Vector2::POS_X * m_radius;

    for(int i = 0; i < NUM_SEGMENTS; i++) {
        points.push_back(getCenterPoint() + delta);
        delta = delta.rotate(da);
    }

    return points;
}
