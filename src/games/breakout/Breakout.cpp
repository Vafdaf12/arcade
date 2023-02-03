#include "Breakout.h"

#include "app/App.h"
#include "input/GameController.h"
#include "shapes/AARectangle.h"
#include "shapes/Circle.h"

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
    m_highscores.loadFromFile(
        App::Singleton().getBasePath() + "highscores.txt");

    m_playerName = "ABC";
    m_score = 0;
    m_currentLevel = 0;
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

void Breakout::resetGame(size_t level) {
    App& app = App::Singleton();

    if (m_score) m_highscores.addScore(m_playerName, m_score);
    m_highscores.saveToFile(App::Singleton().getBasePath() + "highscores.txt");

    if(isGameOver()) m_score = 0;

    m_levels = BreakoutLevel::loadFromFile(
        app.getBasePath() + "../assets/BreakoutLevels.txt");

    AARectangle paddleRect(
        {(app.width() - Paddle::WIDTH) / 2, app.height() - 3 * Paddle::HEIGHT},
        Paddle::WIDTH,
        Paddle::HEIGHT);
    AARectangle boundary(Vector2::ZERO, app.width(), app.height());

    m_boundary = LevelBoundary(boundary);
    m_paddle = Paddle(paddleRect, boundary);
    m_lives = NUM_LIVES;
    m_currentLevel = level;
    m_thresholdY = App::Singleton().height() - 2 * Paddle::HEIGHT;

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

        if (getCurrentLevel().update(dt, m_ball)) m_score += 10;

        if (isBallOutOfBounds()) {
            reduceLife();
            if (!isGameOver()) setToServeState();
            else m_state = GameOver;
        } else if (getCurrentLevel().isLevelComplete()) {
            m_currentLevel = (m_currentLevel + 1) % m_levels.size();
            resetGame(m_currentLevel);
        }
    }
}
void Breakout::draw(Screen& screen) {
    m_paddle.draw(screen);
    m_ball.draw(screen);
    getCurrentLevel().draw(screen);
    screen.draw(m_boundary.getRect(), Color::WHITE);

    float padding = 5 + 2;
    Circle life(Vector2(padding, App::Singleton().height() - padding), 5);
    for (int i = 0; i < m_lives; i++) {
        screen.draw(life, Color::RED, true, Color::RED);
        life.move(Vector2(12, 0));
    }
}
const std::string& Breakout::getName() const {
    static std::string name = "Breakout";
    return name;
}

bool Breakout::isBallOutOfBounds() const {
    return m_ball.getPosition().y > m_thresholdY;
}
void Breakout::reduceLife(int amount) {
    if (m_lives < 0) return;
    m_lives -= amount;
}
