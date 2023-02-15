#include "SoftwareRenderer.h"

#include "SDL_video.h"
#include "graphics/BMPImage.h"
#include "graphics/ScreenBuffer.h"
#include "graphics/SpriteSheet.h"
#include "util/util.h"

#include <algorithm>
#include <cmath>

#include <SDL.h>

SoftwareRenderer::SoftwareRenderer(SDL_Window* pWindow, uint32_t w, uint32_t h) {
    assert(pWindow);
    m_pWindow = pWindow;
    m_buffer.init(SDL_GetWindowPixelFormat(pWindow), w, h);

    m_pWindowSurface = SDL_GetWindowSurface(m_pWindow);
    if(!m_pWindowSurface) throw SDL_EXCEPT("SoftwareRenderer(): ");
}


void SoftwareRenderer::present() {
    SDL_BlitScaled(m_buffer.getSurface(), nullptr, m_pWindowSurface, nullptr);
    SDL_UpdateWindowSurface(m_pWindow);
}
void SoftwareRenderer::clear(const Color& color) {
    assert(m_buffer);
    m_buffer.clear(color);
}

void SoftwareRenderer::drawPoint(const Vector2& point, const Color& color) {
    assert(m_buffer);
    m_buffer.setPixel(
        color, static_cast<int>(point.x), static_cast<int>(point.y));
}
void SoftwareRenderer::drawLine(
    const Vector2& p0, const Vector2& p1, const Color& color) {
    assert(m_buffer);

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

    m_buffer.setPixel(color, x0, y0);
    if (dx >= dy) {
        int p = 2 * dy - dx;

        while (x0 != x1) {
            if (p >= 0) {
                y0 += iy;
                p -= 2 * dx;
            }
            p += 2 * dy;
            x0 += ix;

            m_buffer.setPixel(color, x0, y0);
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

            m_buffer.setPixel(color, x0, y0);
        }
    }
}

void SoftwareRenderer::drawPolygon(
    const std::vector<Vector2>& points, const Color& color) {
    assert(m_buffer);
    Vector2 p0 = points.back();

    for (size_t i = 0; i < points.size(); i++) {
        Vector2 p1 = points[i];
        drawLine(p0, p1, color);
        p0 = p1;
    }
}

void SoftwareRenderer::fillPolygon(
    const std::vector<Vector2>& points, const Color& color) {
    fillPolygon(points, [&](uint32_t, uint32_t) { return color; });
}

void SoftwareRenderer::fillPolygon(
    const std::vector<Vector2>& points, PolyFillFunc fillFunc) {
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
                m_buffer.setPixel(fillFunc(x, y), x, y);
            }
        }
    }
}

void SoftwareRenderer::drawImage(
    const BMPImage& image, const Vector2& pos, const Color& tint) {
    const std::vector<Color>& pixels = image.getPixels();
    for (size_t i = 0; i < pixels.size(); i++) {
        uint32_t x = i % image.width();
        uint32_t y = i / image.width();

        Color col = pixels[i];

        col.red *= static_cast<float>(tint.red) / 255.0f;
        col.green *= static_cast<float>(tint.green) / 255.0f;
        col.blue *= static_cast<float>(tint.blue) / 255.0f;
        col.alpha *= static_cast<float>(tint.alpha) / 255.0f;

        m_buffer.setPixel(col, pos.x + x, pos.y + y);
    }
}

void SoftwareRenderer::drawSprite(const BMPImage& image,
    const Sprite& sprite,
    const Vector2& pos,
    const Color& tint) {
    const std::vector<Color>& pixels = image.getPixels();

    Vector2 topLeft = pos;
    Vector2 topRight = pos + Vector2(sprite.width, 0);
    Vector2 bottomLeft = pos + Vector2(0, sprite.height);
    Vector2 bottomRight = pos + Vector2(sprite.width, sprite.height);

    std::vector<Vector2> points = {topLeft, bottomLeft, bottomRight, topRight};

    Vector2 axisX = topRight - topLeft;
    Vector2 axisY = bottomLeft - topLeft;

    float invXAxisLengthSq = 1.0f / axisX.sqrMagnitude();
    float invYAxisLengthSq = 1.0f / axisY.sqrMagnitude();

    fillPolygon(points, [&](uint32_t x, uint32_t y) {
        Vector2 relPoint = Vector2(x, y) - topLeft;

        // The calculation here is equivalent to
        // relPoint.projectOnto(axisX) / axisX.magnitude()
        // but avoids unnecesary computation by using sqrMagnitude
        float u = relPoint.dot(axisX) * invXAxisLengthSq;
        float v = relPoint.dot(axisY) * invYAxisLengthSq;

        u = clamp(u, 0.0f, 1.0f);
        v = clamp(v, 0.0f, 1.0f);

        int tx = std::roundf(u * static_cast<float>(sprite.width)) + sprite.x;
        int ty = std::roundf(v * static_cast<float>(sprite.height)) + sprite.y;

        size_t i = image.index(tx, ty);

        Color col = pixels[i];

        col.red *= static_cast<float>(tint.red) / 255.0f;
        col.green *= static_cast<float>(tint.green) / 255.0f;
        col.blue *= static_cast<float>(tint.blue) / 255.0f;
        col.alpha *= static_cast<float>(tint.alpha) / 255.0f;
        return col;
    });
}
void SoftwareRenderer::drawText(const std::string& text,
    const BitmapFont& font,
    const AARectangle& boundingBox,
    BitmapFont::FontAlignment alignment,
    const Color& tint) {
    Vector2 start = font.getDrawPosition(text, boundingBox, alignment);
    for (char c : text) {
        if (c == ' ') {
            start.x += font.getWordSpacing();
            continue;
        }
        Sprite sprite = font.getSpriteSheet()[std::string(1, c)];

        drawSprite(font.getFontImage(), sprite, start, tint);

        start.x += sprite.width + font.getLetterSpacing();
    }
}
