#pragma once

#include <memory>
#include <vector>

#include "util/Vector2.h"
#include "graphics/Color.h"

class ScreenBuffer;

class BMPImage;
class Sprite;

class Renderer {
public:
    virtual void clear(const Color& color = Color::BLACK) = 0;

    virtual void drawPoint(const Vector2& point, const Color& color) = 0;
    virtual void drawLine(const Vector2& p0, const Vector2& p1, const Color& color) = 0;

    virtual void drawPolygon(const std::vector<Vector2>& points, const Color& color) = 0;
    virtual void fillPolygon(const std::vector<Vector2>& points, const Color& color) = 0;

    virtual void drawImage(const BMPImage& image, const Vector2& pos) = 0;
    virtual void drawSprite(const BMPImage& sheet, const Sprite& sprite, const Vector2& pos) = 0;
};
