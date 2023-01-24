#include "Shape.h"

void Shape::move(const Vector2& delta) {
    for (auto& point : m_points)
        point += delta;
}
