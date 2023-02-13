#pragma once

#include "./Renderer.h"


class SoftwareRenderer : public Renderer {
public:
    SoftwareRenderer();
    SoftwareRenderer(ScreenBuffer* pBuffer);

    void clear(const Color& color = Color::BLACK) override;

    void drawPoint(const Vector2& point, const Color& color) override;
    void drawLine(const Vector2& p0, const Vector2& p1, const Color& color) override;

    void drawPolygon(const std::vector<Vector2>& points, const Color& color) override;
    void fillPolygon(const std::vector<Vector2>& points, const Color& color) override;

    void drawImage(const BMPImage& image, const Vector2& pos);

private:
    ScreenBuffer* m_pBuffer;
};
