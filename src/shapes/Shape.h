#pragma once

#include "../util/Vector2.h"

#include <vector>

class Shape {
public:
    virtual ~Shape() {}

    virtual Vector2 getCenterPoint() const = 0;
    inline virtual std::vector<Vector2> getPoints() const { return m_points; }

    void move(const Vector2& delta);

protected:
    std::vector<Vector2> m_points;
};
