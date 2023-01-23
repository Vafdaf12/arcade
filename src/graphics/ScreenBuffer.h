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

    void Init(uint32_t format, uint32_t width, uint32_t height);

    inline SDL_Surface* GetSurface() { return m_pSurface; }

    void Clear(const Color& c = Color::Black());
    void SetPixel(const Color& color, int x, int y);

private:
    SDL_Surface* m_pSurface;

    size_t GetIndex(int r, int c) const;
};
