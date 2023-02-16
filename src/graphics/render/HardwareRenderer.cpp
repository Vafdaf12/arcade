#include "HardwareRenderer.h"

#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "graphics/BMPImage.h"
#include "graphics/ScreenBuffer.h"
#include "graphics/SpriteSheet.h"
#include "util/util.h"

#include <algorithm>
#include <cmath>

#include <SDL.h>
#include <cstring>

HardwareRenderer::HardwareRenderer()
    : m_pWindow(nullptr), m_pRenderer(nullptr), 
      m_renderColor(Color::BLACK) {}

HardwareRenderer::HardwareRenderer(
    SDL_Window* pWindow, uint32_t w, uint32_t h) {
    assert(pWindow);
    m_pWindow = pWindow;

    m_pRenderer = SDL_CreateRenderer(
        m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_pRenderer) throw SDL_EXCEPT("HarwareRenderer::CreateRenderer: ");

    SDL_RenderSetLogicalSize(m_pRenderer, w, h);
    SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

    m_renderColor = Color::BLACK;
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
}
HardwareRenderer& HardwareRenderer::operator=(HardwareRenderer&& other) {
    std::swap(m_pRenderer, other.m_pRenderer);
    std::swap(m_pWindow, other.m_pWindow);
    m_renderColor = other.m_renderColor;

    return *this;
}

HardwareRenderer::~HardwareRenderer() {
    if (m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
}

void HardwareRenderer::present() {
    SDL_RenderPresent(m_pRenderer);
}

void HardwareRenderer::setRenderDrawColor(const Color& color) {
    if (color == m_renderColor) return;
    m_renderColor = color;
    SDL_SetRenderDrawColor(
        m_pRenderer, color.red, color.green, color.blue, color.alpha);
}
void HardwareRenderer::clear(const Color& color) {
    setRenderDrawColor(color);
    SDL_RenderClear(m_pRenderer);
}

void HardwareRenderer::drawPoint(const Vector2& point, const Color& color) {
    assert(m_pRenderer);
    setRenderDrawColor(color);

    SDL_RenderDrawPointF(m_pRenderer, point.x, point.y);
}
void HardwareRenderer::drawLine(
    const Vector2& p0, const Vector2& p1, const Color& color) {
    assert(m_pRenderer);
    setRenderDrawColor(color);

    SDL_RenderDrawLineF(m_pRenderer, p0.x, p0.y, p1.x, p1.y);
}

void HardwareRenderer::drawPolygon(
    const std::vector<Vector2>& points, const Color& color) {
    assert(m_pRenderer);
    setRenderDrawColor(color);

    std::vector<SDL_FPoint> drawPoints;
    drawPoints.resize(points.size() + 1);

    std::transform(
        points.begin(), points.end(), drawPoints.begin(), [](const Vector2& p) {
            SDL_FPoint point;
            point.x = p.x;
            point.y = p.y;
            return point;
        });

    drawPoints.back() = drawPoints.front();
    SDL_RenderDrawLinesF(m_pRenderer, drawPoints.data(), drawPoints.size());
}

void HardwareRenderer::fillPolygon(
    const std::vector<Vector2>& points, const Color& color) {
    fillPolygon(points, [&](uint32_t, uint32_t) { return color; });
}

void HardwareRenderer::fillPolygon(
    const std::vector<Vector2>& points, PolyFillFunc fillFunc) {
    assert(m_pRenderer);
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
                setRenderDrawColor(fillFunc(x, y));
                SDL_RenderDrawPoint(m_pRenderer, x, y);
            }
        }
    }
}

void HardwareRenderer::drawImage(
    const BMPImage& image, const Vector2& pos, const Color& tint) {
    assert(m_pRenderer);
    const std::vector<Color>& pixels = image.getPixels();
    for (size_t i = 0; i < pixels.size(); i++) {
        uint32_t x = i % image.width();
        uint32_t y = i / image.width();

        Color col = pixels[i];

        col.red *= static_cast<float>(tint.red) / 255.0f;
        col.green *= static_cast<float>(tint.green) / 255.0f;
        col.blue *= static_cast<float>(tint.blue) / 255.0f;
        col.alpha *= static_cast<float>(tint.alpha) / 255.0f;

        setRenderDrawColor(col);
        SDL_RenderDrawPointF(m_pRenderer, pos.x + x, pos.y + y);
    }
}

void HardwareRenderer::drawSprite(const BMPImage& image,
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
void HardwareRenderer::drawText(const std::string& text,
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
