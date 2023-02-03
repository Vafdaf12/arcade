#pragma once

#include "Shape.h"
#include "util/Vector2.h"

class AARectangle : public Shape {
public:
    AARectangle();
    AARectangle(const Vector2& topLeft, unsigned int width, unsigned int height);
    AARectangle(const Vector2& topLeft, const Vector2& bottomRight);

    virtual Vector2 getCenterPoint() const override;
    virtual std::vector<Vector2> getPoints() const override;

    inline void setTopLeft(const Vector2& topLeft) { m_points[0] = topLeft; }
    inline void setBottomRight(const Vector2& bottomRight) { m_points[1] = bottomRight; }

    inline Vector2 getTopLeft() const { return m_points[0]; }
    inline Vector2 getBottomRight() const { return m_points[1]; }

    inline float getWidth() const { return m_points[1].x - m_points[0].x + 1; }
    inline float getHeight() const { return m_points[1].y - m_points[0].y + 1; }

    void setPosition(const Vector2& newPos);
    bool intersects(const AARectangle& other) const;
    bool containsPoint(const Vector2& point) const;
    static AARectangle inset(const AARectangle& rect, const Vector2& insets);


};
