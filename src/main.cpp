#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_video.h"
#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;

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
