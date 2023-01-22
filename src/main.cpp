#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_pixels.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include "graphics/Color.h"
#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;

void SetPixel(SDL_Surface* pSurface, uint32_t color, int x, int y);
size_t GetIndex(SDL_Surface* pSurface, int r, int c);


int main() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "failed to initialize SDL\n";
        return 1;
    }

    SDL_Window* pWindow = SDL_CreateWindow("Arcade",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    if (!pWindow) {
        std::cout << "failed to create SDL window: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Surface* pWindowSurface = SDL_GetWindowSurface(pWindow);
    SDL_PixelFormat* pPixelFormat = pWindowSurface->format;

    Color::SetColorFormat(pPixelFormat);

    std::cout << "Window pixel format: " << SDL_GetPixelFormatName(pPixelFormat->format) << "\n";

    SetPixel(pWindowSurface, Color::Orange(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    SDL_UpdateWindowSurface(pWindow);

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: running = false; break;
            }
        }
    }
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    std::cout << "Hello World\n";
}

void SetPixel(SDL_Surface* pSurface, uint32_t color, int x, int y) {
    SDL_LockSurface(pSurface);

    uint32_t* pixels = static_cast<uint32_t*>(pSurface->pixels);
    size_t i = GetIndex(pSurface, y, x);
    pixels[i] = color;

    SDL_UnlockSurface(pSurface);

}
size_t GetIndex(SDL_Surface* pSurface, int r, int c) {
    return r * pSurface->w + c;
}
