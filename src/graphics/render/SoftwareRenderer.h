#pragma once

#include "./Renderer.h"
#include "graphics/ScreenBuffer.h"

struct SDL_Window;
struct SDL_Surface;

class SoftwareRenderer : public Renderer {
public:
    SoftwareRenderer() = default;
    SoftwareRenderer(SDL_Window* pWindow, uint32_t w, uint32_t h);

    void present() override;
    void clear(const Color& color = Color::BLACK) override;

    void drawPoint(const Vector2& point, const Color& color) override;
    void drawLine(const Vector2& p0, const Vector2& p1, const Color& color) override;

    void drawPolygon(const std::vector<Vector2>& points, const Color& color) override;
    void fillPolygon(const std::vector<Vector2>& points, const Color& color) override;
    void fillPolygon(const std::vector<Vector2>& points, PolyFillFunc fillFunc) override;

    void drawImage(const BMPImage& image, const Vector2& pos, const Color& tint = Color::WHITE) override;
    void drawSprite(const BMPImage& sheet, const Sprite& sprite, const Vector2& pos, const Color& tint = Color::WHITE) override;
    void drawText(
            const std::string& text,
            const BitmapFont& font, 
            const AARectangle& boundingBox,
            BitmapFont::FontAlignment alignment = BitmapFont::TopAlign | BitmapFont::LeftAlign,
            const Color& tint = Color::WHITE
    ) override;

private:
    SDL_Window* m_pWindow;
    SDL_Surface* m_pWindowSurface;
    ScreenBuffer m_buffer;
};
