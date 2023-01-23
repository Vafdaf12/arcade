#pragma once

#include "../util/Vector2.h"

class Line2D {
public:
    Line2D();
    Line2D(float x0, float y0, float x1, float y1);
    Line2D(const Vector2& v0, const Vector2& v1);

    inline const Vector2& v0() const { return m_v0; }
    inline const Vector2& v1() const { return m_v1; }

    bool operator==(const Line2D& line) const;

    float minDistanceTo(const Vector2& point, bool segment = false) const;
    Vector2 closestPointTo(const Vector2& point, bool segment = false) const;

    Vector2 midpoint() const;
    float slope() const;
    float length() const;

private:
    Vector2 m_v0, m_v1;
};
