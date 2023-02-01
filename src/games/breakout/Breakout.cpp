#include "Breakout.h"

#include "app/App.h"
#include "input/GameController.h"
#include "shapes/AARectangle.h"

#include <functional>
#include <iostream>

Breakout::Breakout() : m_paddle(AARectangle(), AARectangle()) {}

void Breakout::init(GameController& controller) {
    controller.clear();

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::KEY_LEFT;
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::isPressed(state))
            m_paddle.setMovementDirection(Paddle::Left);
        if (GameController::isReleased(state))
            m_paddle.unsetMovementDirection(Paddle::Left);
    };

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::KEY_RIGHT;
    rightKeyAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::isPressed(state))
            m_paddle.setMovementDirection(Paddle::Right);
        if (GameController::isReleased(state))
            m_paddle.unsetMovementDirection(Paddle::Right);
    };

    controller.addAction(leftKeyAction);
    controller.addAction(rightKeyAction);

    resetGame();
}

void Breakout::resetGame() {
    App& app = App::Singleton();

    AARectangle paddleRect(
        {(app.width() - Paddle::WIDTH) / 2, app.height() - 3 * Paddle::HEIGHT},
        Paddle::WIDTH,
        Paddle::HEIGHT);
    AARectangle boundary(Vector2::ZERO, app.width(), app.height());

    m_paddle = Paddle(paddleRect, boundary);
    m_ball.setPosition({app.width() / 2.0f, app.height() / 2.0f});
}
void Breakout::update(uint32_t dt) {
    m_paddle.update(dt);
    m_ball.update(dt);
}
void Breakout::draw(Screen& screen) {
    m_paddle.draw(screen);
    m_ball.draw(screen);
}
const std::string& Breakout::getName() const {
    static std::string name = "Breakout";
    return name;
}
