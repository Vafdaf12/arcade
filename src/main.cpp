#include <iostream>

#include "app/App.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main() {
    App& app = App::Singleton();
    app.init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
    app.run();
    std::cout << "Hello World\n";
}
