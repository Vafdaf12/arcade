#include "SoftwareRenderer.h"

#include "graphics/ScreenBuffer.h"
#include <algorithm>

SoftwareRenderer::SoftwareRenderer() : m_pBuffer(nullptr) {}
SoftwareRenderer::SoftwareRenderer(ScreenBuffer* pBuffer) : m_pBuffer(pBuffer) {
    assert(m_pBuffer);
}

void SoftwareRenderer::clear(const Color& color) {
    assert(m_pBuffer);
    m_pBuffer->clear(color);
}

void SoftwareRenderer::drawPoint(const Vector2& point, const Color& color) {
    assert(m_pBuffer);
    m_pBuffer->setPixel(
        color, static_cast<int>(point.x), static_cast<int>(point.y));
}
void SoftwareRenderer::drawLine(
    const Vector2& p0, const Vector2& p1, const Color& color) {
    assert(m_pBuffer);

    int dx, dy;

    int x0 = std::roundf(p0.x);
    int y0 = std::roundf(p0.y);

    int x1 = std::roundf(p1.x);
    int y1 = std::roundf(p1.y);

    dx = x1 - x0;
    dy = y1 - y0;

    const char ix((dx > 0) - (dx < 0));
    const char iy((dy > 0) - (dy < 0));

    dx = std::abs(dx);
    dy = std::abs(dy);

    m_pBuffer->setPixel(color, x0, y0);
    if (dx >= dy) {
        int p = 2 * dy - dx;

        while (x0 != x1) {
            if (p >= 0) {
                y0 += iy;
                p -= 2 * dx;
            }
            p += 2 * dy;
            x0 += ix;

            m_pBuffer->setPixel(color, x0, y0);
        }
    } else {
        int p = 2 * dx - dy;

        while (y0 != y1) {
            if (p >= 0) {
                x0 += ix;
                p -= 2 * dy;
            }
            p += 2 * dx;
            y0 += iy;

            m_pBuffer->setPixel(color, x0, y0);
        }
    }
}

void SoftwareRenderer::drawPolygon(
    const std::vector<Vector2>& points, const Color& color) {
    assert(m_pBuffer);
    Vector2 p0 = points.back();

    for (size_t i = 0; i < points.size(); i++) {
        Vector2 p1 = points[i];
        drawLine(p0, p1, color);
        p0 = p1;
    }
}

void SoftwareRenderer::fillPolygon(
    const std::vector<Vector2>& points, const Color& color) {
    if (points.size() == 0) return;

    float top = points[0].y;
    float bottom = points[0].y;

    // Find y-range of polygon
    for (size_t i = 1; i < points.size(); ++i) {
        if (points[i].y < top) top = points[i].y;
        if (points[i].y > bottom) bottom = points[i].y;
    }

    for (int y = top; y < bottom; ++y) {
        std::vector<float> intersections;

        for (size_t i = 0; i < points.size(); ++i) {
            size_t j = (i + 1) % points.size();

            float yi = points[i].y;
            float yj = points[j].y;

            // intersection test
            if (y < std::min(yi, yj)) continue;
            if (y >= std::max(yi, yj)) continue;

            // skip line if horizontal
            float denom = yi - yj;
            if (isEqual(denom, 0)) continue;

            // calculate x-position
            float t = (y - yj) / denom;
            float x = points[j].x * (1 - t) + points[i].x * t;

            intersections.push_back(x);
        }

        std::sort(intersections.begin(), intersections.end(), std::less<>());

        for (size_t i = 0; i < intersections.size(); i += 2) {
            // use std::ceil to prevent overlap with line drawing
            int x1 = std::ceil(intersections[i]);
            int x2 = std::ceil(intersections[i + 1]);

            for (int x = x1; x < x2; x++) {
                m_pBuffer->setPixel(color, x, y);
            }
        }
    }
}
