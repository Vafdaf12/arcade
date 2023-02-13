#include "BMPImage.h"
#include "SDL_surface.h"

#include <SDL.h>
#include <iostream>

BMPImage::BMPImage() : m_width(0), m_height(0) {}
bool BMPImage::loadFromFile(const std::string& path) {
    std::cout << "opening " << path << std::endl;
    SDL_Surface* pImageSurface = SDL_LoadBMP(path.c_str());

    if(!pImageSurface) return false;
    if(!pImageSurface->pixels) return false;

    m_width = pImageSurface->w;
    m_height = pImageSurface->h;

    size_t length = m_width * m_height;
    m_pixels.reserve(length);

    SDL_LockSurface(pImageSurface);

    
    uint32_t* pPixels = static_cast<uint32_t*>(pImageSurface->pixels);
    for(size_t i = 0; i < length; i++) {
        m_pixels.push_back(Color(pPixels[i], pImageSurface->format));
    }

    SDL_UnlockSurface(pImageSurface);
    SDL_FreeSurface(pImageSurface);
    return true;
}
