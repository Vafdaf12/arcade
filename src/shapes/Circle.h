#include "Shape.h"
#include <vector>

class Circle : public Shape {
public:
    Circle();
    Circle(const Vector2& center, float radius);
    
    inline Vector2 getCenterPoint() const override { return m_points[0]; }
    virtual std::vector<Vector2> getPoints() const override;

    inline float getRadius() const { return m_radius; }
    inline void setRadius(float r) { m_radius = r; }

    inline void setPosition(const Vector2& newPos) { m_points[0] = newPos; }

    bool intersects(const Circle& circle) const;
    bool containsPoint(const Vector2& point) const;


private:
    float m_radius;
};
