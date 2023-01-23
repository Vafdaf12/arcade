#include "ScreenBuffer.h"
#include "SDL_surface.h"

#include <cassert>

#define ASSERT_GUARD(cond, body)                                               \
    assert(cond);                                                              \
    if (!(cond)) body;

ScreenBuffer::ScreenBuffer() : m_pSurface{nullptr} {}
ScreenBuffer::ScreenBuffer(const ScreenBuffer& buf) : ScreenBuffer() {
    if (!buf.m_pSurface) return;

    m_pSurface = SDL_CreateRGBSurfaceWithFormat(
        0, buf.m_pSurface->w, buf.m_pSurface->h, 0, m_pSurface->format->format);
    SDL_BlitSurface(buf.m_pSurface, nullptr, m_pSurface, nullptr);
}
ScreenBuffer::~ScreenBuffer() {
    if (m_pSurface) SDL_FreeSurface(m_pSurface);
}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& other) {
    if (this == &other) return *this;

    // Free pre-existing surface
    if (m_pSurface) SDL_FreeSurface(m_pSurface);
    m_pSurface = nullptr;

    if (other.m_pSurface) {
        m_pSurface = SDL_CreateRGBSurfaceWithFormat(0,
            other.m_pSurface->w,
            other.m_pSurface->h,
            0,
            m_pSurface->format->format);
        SDL_BlitSurface(other.m_pSurface, nullptr, m_pSurface, nullptr);
    }

    return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t height) {
    m_pSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
    Clear();
}

void ScreenBuffer::SetPixel(const Color& color, int x, int y) {
    ASSERT_GUARD(m_pSurface, return)
    if (y >= m_pSurface->h || y < 0) return;
    if (x >= m_pSurface->w || x < 0) return;

    SDL_LockSurface(m_pSurface);

    uint32_t* pixels = static_cast<uint32_t*>(m_pSurface->pixels);
    size_t i = GetIndex(y, x);
    pixels[i] = color.GetColor();

    SDL_UnlockSurface(m_pSurface);
}
void ScreenBuffer::Clear(const Color& c) {
    ASSERT_GUARD(m_pSurface, return)

    SDL_FillRect(m_pSurface, nullptr, c.GetColor());
}

size_t ScreenBuffer::GetIndex(int r, int c) const {
    ASSERT_GUARD(m_pSurface, return 0)

    return r * m_pSurface->w + c;
}
