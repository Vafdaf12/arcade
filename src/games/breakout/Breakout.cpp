#include "Breakout.h"

#include "app/App.h"
#include "input/GameController.h"
#include "shapes/AARectangle.h"

#include <functional>
#include <iostream>

Breakout::Breakout()
    : m_paddle(AARectangle(), AARectangle()), m_boundary(AARectangle()) {}

void Breakout::setToServeState() {
    m_state = Serve;
    m_ball.stop();

    AARectangle paddle = m_paddle.getRect();
    Vector2 center = paddle.getCenterPoint();

    float r = m_ball.getRadius();

    m_ball.setPosition(Vector2(center.x - r, paddle.getTopLeft().y - r - 1));
}

void Breakout::init(GameController& controller) {
    controller.clear();
    resetGame();

    ButtonAction serveAction;
    serveAction.key = GameController::KEY_ACTION;
    serveAction.action = [this](uint32_t dt, InputState state) {
        if (m_state == Serve) {
            if (!GameController::isPressed(state)) return;

            m_state = Play;
            if (m_paddle.isMovingLeft())
                m_ball.setVelocity({-Ball::INIT_SPEED, -Ball::INIT_SPEED});
            else m_ball.setVelocity({Ball::INIT_SPEED, -Ball::INIT_SPEED});

        } else if (m_state == GameOver) {
            if (!GameController::isPressed(state)) return;
            resetGame();
        }
    };

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::KEY_LEFT;
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if (!(m_state == Play || m_state == Serve)) return;
        if (GameController::isPressed(state))
            m_paddle.setMovementDirection(Paddle::Left);
        if (GameController::isReleased(state))
            m_paddle.unsetMovementDirection(Paddle::Left);
    };

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::KEY_RIGHT;
    rightKeyAction.action = [this](uint32_t dt, InputState state) {
        if (!(m_state == Play || m_state == Serve)) return;
        if (GameController::isPressed(state))
            m_paddle.setMovementDirection(Paddle::Right);
        if (GameController::isReleased(state))
            m_paddle.unsetMovementDirection(Paddle::Right);
    };

    controller.addAction(leftKeyAction);
    controller.addAction(rightKeyAction);
    controller.addAction(serveAction);
}

void Breakout::resetGame() {
    App& app = App::Singleton();

    AARectangle paddleRect(
        {(app.width() - Paddle::WIDTH) / 2, app.height() - 3 * Paddle::HEIGHT},
        Paddle::WIDTH,
        Paddle::HEIGHT);
    AARectangle boundary(Vector2::ZERO, app.width(), app.height());

    std::cout << "Path: " << app.getBasePath() << std::endl;
    m_levels = BreakoutLevel::loadFromFile(
        app.getBasePath() + "../assets/BreakoutLevels.txt");
    m_currentLevel = 0;

    m_boundary = LevelBoundary(boundary);
    m_paddle = Paddle(paddleRect, boundary);
    setToServeState();
}
void Breakout::update(uint32_t dt) {
    if (m_state == Serve) {
        m_paddle.update(dt, m_ball);
        setToServeState();
    } else if (m_state == Play) {
        m_paddle.update(dt, m_ball);
        m_ball.update(dt);

        if (m_paddle.bounce(m_ball)) return;

        BoundaryEdge edge;
        if (m_boundary.hasCollided(m_ball, edge)) {
            m_ball.bounce(edge);
        }
        getCurrentLevel().update(dt, m_ball);
    }
}
void Breakout::draw(Screen& screen) {
    m_paddle.draw(screen);
    m_ball.draw(screen);
    getCurrentLevel().draw(screen);
    screen.draw(m_boundary.getRect(), Color::WHITE);
}
const std::string& Breakout::getName() const {
    static std::string name = "Breakout";
    return name;
}
