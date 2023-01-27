#include "graphics/Color.h"
#include "graphics/Screen.h"
#include "graphics/ScreenBuffer.h"
#include "shapes/AARectangle.h"
#include "shapes/Line2D.h"
#include "shapes/Triangle.h"
#include "shapes/Circle.h"

#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main() {
    Screen screen;
    screen.init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    screen.draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, Color::ORANGE);

    Line2D line({0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT});
    screen.draw(line, Color::WHITE);

    Triangle triangle({2, 2}, {50, 30}, {20, 60});
    screen.draw(triangle, Color::CYAN);

    AARectangle rect({50, 50}, {100, 100});
    screen.draw(rect, Color::RED);

    Color color = Color::BLUE;
    color.alpha = 128;
    Circle circle({100, 100}, 30);
    screen.draw(circle, Color::CYAN, true, color);


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
