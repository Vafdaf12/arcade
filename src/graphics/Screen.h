#pragma once

#include "Color.h"
#include "ScreenBuffer.h"
#include "graphics/render/SoftwareRenderer.h"
#include "shapes/Shape.h"

#include <stdint.h>

class Vector2;
class Line2D;
class BMPImage;

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;

class Screen {
public:
    Screen();
    ~Screen();

    SDL_Window* init(uint32_t w, uint32_t h, uint32_t mag);
    void swapBuffers();

    inline void setClearColor(const Color& c) { m_clearColor = c; }

    inline uint32_t width() const { return m_width; }
    inline uint32_t height() const { return m_height; }

    inline operator bool() const { return m_pWindow; }

    // --- DRAW CALLS ---

    void draw(int x, int y, const Color& color);
    void draw(const Vector2& p, const Color& color);
    void draw(const Line2D& line, const Color& color);
    void draw(const Shape& shape,
        const Color& color,
        bool fill = false,
        const Color& fillColor = Color::WHITE);

    void draw(const BMPImage& image, const Sprite& sprite, const Vector2& pos, const Color& tint = Color::WHITE);
    void draw(const BMPImage& image, const Vector2& pos, const Color& tint = Color::WHITE);
    void draw(
            const std::string& text,
            const BitmapFont& font, 
            const AARectangle& boundingBox,
            BitmapFont::FontAlignment alignment = BitmapFont::TopAlign | BitmapFont::LeftAlign,
            const Color& tint = Color::WHITE
    );

private:
    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

    uint32_t m_width, m_height;

    SDL_Window* m_pWindow;
    SDL_Surface* m_pSurface;

    ScreenBuffer m_backBuffer;
    Color m_clearColor;
    SoftwareRenderer m_renderer;
};
