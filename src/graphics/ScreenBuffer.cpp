#include "ScreenBuffer.h"
#include "SDL_surface.h"

#include <cassert>
#include <iostream>
#include <utility>

#define ASSERT_GUARD(cond, body)                                               \
    assert(cond);                                                              \
    if (!(cond)) body

ScreenBuffer::ScreenBuffer() : m_pSurface(nullptr) {}
ScreenBuffer::ScreenBuffer(const ScreenBuffer& buf) : ScreenBuffer() {
    if (!buf.m_pSurface) return;

    m_pSurface = SDL_CreateRGBSurfaceWithFormat(
        0, buf.m_pSurface->w, buf.m_pSurface->h, 0, m_pSurface->format->format);
    SDL_BlitSurface(buf.m_pSurface, nullptr, m_pSurface, nullptr);
}
ScreenBuffer::ScreenBuffer(ScreenBuffer&& buf) {
    std::swap(buf.m_pSurface, m_pSurface);
}
ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& buf) {
    if (this == &buf) return *this;

    // Free pre-existing surface
    if (m_pSurface) SDL_FreeSurface(m_pSurface);
    m_pSurface = nullptr;

    if (buf.m_pSurface) {
        m_pSurface = SDL_CreateRGBSurfaceWithFormat(0,
            buf.m_pSurface->w,
            buf.m_pSurface->h,
            0,
            m_pSurface->format->format);
        SDL_BlitSurface(buf.m_pSurface, nullptr, m_pSurface, nullptr);
    }

    return *this;
}
ScreenBuffer& ScreenBuffer::operator=(ScreenBuffer&& buf) {
    std::swap(buf.m_pSurface, m_pSurface);
    return *this;
}
ScreenBuffer::~ScreenBuffer() {
    if (m_pSurface) SDL_FreeSurface(m_pSurface);
}

void ScreenBuffer::init(uint32_t format, uint32_t width, uint32_t height) {
    m_pSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
    clear();
}

void ScreenBuffer::setPixel(const Color& color, int x, int y) {
    ASSERT_GUARD(m_pSurface, { return; })

    if (y >= m_pSurface->h || y < 0) return;
    if (x >= m_pSurface->w || x < 0) return;

    SDL_LockSurface(m_pSurface);

    uint32_t* pixels = static_cast<uint32_t*>(m_pSurface->pixels);
    size_t i = index(y, x);

    Color dest(pixels[i], m_pSurface->format);
    pixels[i] = Color::blendColors(color, dest).mapToFormat(m_pSurface->format);

    SDL_UnlockSurface(m_pSurface);
}
void ScreenBuffer::clear(const Color& c) {
    ASSERT_GUARD(m_pSurface, { return; })

    SDL_FillRect(m_pSurface, nullptr, c.mapToFormat(m_pSurface->format));
}

size_t ScreenBuffer::index(int r, int c) const {
    ASSERT_GUARD(m_pSurface, { return 0; })

    return r * m_pSurface->w + c;
}
