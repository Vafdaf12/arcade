#include "ArcadeScene.h"

#include "app/App.h"
#include "shapes/AARectangle.h"
#include "shapes/Circle.h"
#include "shapes/Line2D.h"
#include "shapes/Triangle.h"

#include "graphics/BitmapFont.h"
#include "graphics/Screen.h"
#include "input/GameController.h"
#include "input/InputAction.h"

#include <iostream>

ArcadeScene::ArcadeScene() {}

void ArcadeScene::init() {
    ButtonAction action;
    action.key = GameController::KEY_ACTION;
    action.action = [](uint32_t, InputState state) {
        std::cout << "Action button ";
        if (GameController::isPressed(state)) {
            std::cout << "pressed";
        } else if (GameController::isReleased(state)) {
            std::cout << "released";
        }
        std::cout << std::endl;
    };

    MouseButtonAction mouseAction;
    mouseAction.button = GameController::MOUSE_BUTTON_LEFT;
    mouseAction.inputAction = [](InputState state, const MousePosition& pos) {
        std::cout << "Mouse button ";
        if (GameController::isPressed(state)) {
            std::cout << "pressed";
        } else if (GameController::isReleased(state)) {
            std::cout << "released";
        }
        std::cout << std::endl;
    };

    m_controller.addAction(action);
    m_controller.addMouseInputAction(mouseAction);
}
const std::string& ArcadeScene::getName() const {
    static std::string name = "Arcade Scene";
    return name;
}

void ArcadeScene::update(uint32_t dt) {}
void ArcadeScene::draw(Screen& screen) {

    Line2D line({0, 0},
        {static_cast<float>(screen.width()),
            static_cast<float>(screen.height())});

    Triangle triangle({2, 2}, {50, 30}, {20, 60});

    AARectangle rect({50, 50}, {100, 100});

    Color color = Color::BLUE;
    color.alpha = 128;
    Circle circle({100, 100}, 30);

    screen.draw(line, Color::WHITE);
    screen.draw(triangle, Color::CYAN);
    screen.draw(rect, Color::RED);
    screen.draw(circle, Color::CYAN, true, color);

    App& app = App::Singleton();

    screen.draw(getName(), app.getFont(), AARectangle(Vector2::ZERO, app.width(), app.height()), BitmapFont::CenterAlign | BitmapFont::MiddleAlign);
}

std::unique_ptr<Scene> ArcadeScene::getScene(ArcadeGame game) {
    switch (game) {
    case ArcadeGame::Pacman: break;
    case ArcadeGame::Breakout: break;
    case ArcadeGame::Tetris: break;
    case ArcadeGame::Asteroids: break;
    case ArcadeGame::GameList: break;
    default: break;
    }
    return nullptr;
}
