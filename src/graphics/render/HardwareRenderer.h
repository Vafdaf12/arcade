#pragma once

#include "./Renderer.h"
#include "graphics/ScreenBuffer.h"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Texture;

class HardwareRenderer : public Renderer {
public:
<<<<<<< HEAD
    HardwareRenderer() = default;
    HardwareRenderer(SDL_Window* pWindow, uint32_t w, uint32_t h);

=======
    HardwareRenderer();
    HardwareRenderer(SDL_Window* pWindow, uint32_t w, uint32_t h);

    // move semantics
    HardwareRenderer& operator=(HardwareRenderer&& other);

    // disable copying of renderer
    HardwareRenderer(const HardwareRenderer& other) = delete;
    HardwareRenderer& operator=(const HardwareRenderer& other) = delete;

>>>>>>> dd1c42a (feat: add hardware-accelerated renderer for better performance)
    ~HardwareRenderer();

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
    void setRenderDrawColor(const Color& color);

    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;
    SDL_Window* m_pWindow;
<<<<<<< HEAD
    SDL_PixelFormat* m_pFormat;
=======
>>>>>>> dd1c42a (feat: add hardware-accelerated renderer for better performance)

    ScreenBuffer m_buffer;
    Color m_renderColor;
};
