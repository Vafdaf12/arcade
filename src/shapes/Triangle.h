#pragma once

#include "Shape.h"
#include "util/Vector2.h"

class Triangle : public Shape {
public:
    Triangle();
    Triangle(const Vector2& p0, const Vector2& p1, const Vector2 p2);

    inline void setP0(const Vector2& p0) { m_points[0] = p0; }
    inline void setP1(const Vector2& p1) { m_points[1] = p1; }
    inline void setP2(const Vector2& p2) { m_points[2] = p2; }

    inline Vector2 getP0() const { return m_points[0]; }
    inline Vector2 getP1() const { return m_points[1]; }
    inline Vector2 getP2() const { return m_points[2]; }

    virtual Vector2 getCenterPoint() const override;

    bool containsPoint(const Vector2& point) const;
    float area() const;
private:
    static float area(const Vector2& p0, const Vector2& p1, const Vector2& p2);

};
