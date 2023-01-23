#include "graphics/Color.h"
#include "graphics/Screen.h"
#include "graphics/ScreenBuffer.h"

#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 4;

int main() {
    Screen screen;
    screen.init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    screen.draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, Color::Orange());
    screen.swapBuffers();

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: running = false; break;
            }
        }
    }

    std::cout << "Hello World\n";
}
