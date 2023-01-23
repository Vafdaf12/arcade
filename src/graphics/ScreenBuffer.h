#pragma once

#include "Color.h"
#include <cstddef>
#include <stdint.h>

struct SDL_Surface;

class ScreenBuffer {
public:
    ScreenBuffer();
    ScreenBuffer(const ScreenBuffer& buf);
    ~ScreenBuffer();

    ScreenBuffer& operator=(const ScreenBuffer& other);

    void init(uint32_t format, uint32_t width, uint32_t height);

    inline SDL_Surface* getSurface() { return m_pSurface; }

    void clear(const Color& c = Color::Black());
    void setPixel(const Color& color, int x, int y);

    inline operator bool() const { return m_pSurface; }

private:
    SDL_Surface* m_pSurface;

    size_t index(int r, int c) const;
};
