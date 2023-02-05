#include "Tetris.h"

#include "app/App.h"
#include "input/GameController.h"
#include "input/InputAction.h"

void Tetris::init(GameController& controller) {
    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::KEY_LEFT;
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::isPressed(state)) {
            m_activeTetromino.move({-Cell::WIDTH, 0});
            // move tetromino left
        }
    };

    ButtonAction actionKeyAction;
    actionKeyAction.key = GameController::KEY_ACTION;
    actionKeyAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::isPressed(state)) {
            m_activeTetromino.rotate();
        }
    };
    ButtonAction cancelKeyAction;
    cancelKeyAction.key = GameController::KEY_CANCEL;
    cancelKeyAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::isPressed(state)) {
            m_activeTetromino.rotate(true);
        }
    };

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::KEY_RIGHT;
    rightKeyAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::isPressed(state)) {
            m_activeTetromino.move({Cell::WIDTH, 0});
        }
    };

    controller.addAction(leftKeyAction);
    controller.addAction(rightKeyAction);
    controller.addAction(actionKeyAction);
    controller.addAction(cancelKeyAction);

    App& app = App::Singleton();

    m_boundary = AARectangle(
        Vector2::ZERO, Cell::WIDTH * 10, Cell::WIDTH * 20);
    Vector2 pos = {(app.width() - m_boundary.getWidth()) / 2.0f,
        (app.height() - m_boundary.getHeight()) / 2.0f};

    m_boundary.setPosition(pos);

    // I shape
    m_availableTetrominos.push_back(Tetromino(
        {
            Cell::createDefaultCell({Cell::WIDTH*0, 0}, Color::CYAN),
            Cell::createDefaultCell({Cell::WIDTH*1, 0}, Color::CYAN),
            Cell::createDefaultCell({Cell::WIDTH*2, 0}, Color::CYAN),
            Cell::createDefaultCell({Cell::WIDTH*3, 0}, Color::CYAN)
        },
        {2*Cell::WIDTH, Cell::WIDTH},
        m_boundary
        ));

    // J shape
    m_availableTetrominos.push_back(Tetromino(
        {
            Cell::createDefaultCell({0, 0}, Color::BLUE),
            Cell::createDefaultCell({0, Cell::WIDTH}, Color::BLUE),
            Cell::createDefaultCell({Cell::WIDTH*1, Cell::WIDTH}, Color::BLUE),
            Cell::createDefaultCell({Cell::WIDTH*2, Cell::WIDTH}, Color::BLUE)
        },
        Vector2::ONE * Cell::WIDTH * 1.5f,
        m_boundary
        ));
    // L shape
    m_availableTetrominos.push_back(Tetromino(
        {
            Cell::createDefaultCell({Cell::WIDTH*0, Cell::WIDTH}, Color::BLUE),
            Cell::createDefaultCell({Cell::WIDTH*1, Cell::WIDTH}, Color::BLUE),
            Cell::createDefaultCell({Cell::WIDTH*2, Cell::WIDTH}, Color::BLUE),
            Cell::createDefaultCell({Cell::WIDTH*2, 0}, Color::BLUE),
        },
        Vector2::ONE * Cell::WIDTH * 1.5f,
        m_boundary
        ));
    // O shape
    m_availableTetrominos.push_back(Tetromino(
        {
            Cell::createDefaultCell({0, 0}, Color::YELLOW),
            Cell::createDefaultCell({0, Cell::WIDTH}, Color::YELLOW),
            Cell::createDefaultCell({Cell::WIDTH, 0}, Color::YELLOW),
            Cell::createDefaultCell({Cell::WIDTH, Cell::WIDTH}, Color::YELLOW),
        },
        Vector2::ONE * Cell::WIDTH,
        m_boundary
        ));
    // S shape
    m_availableTetrominos.push_back(Tetromino(
        {
            Cell::createDefaultCell({0, Cell::WIDTH}, Color::GREEN),
            Cell::createDefaultCell({Cell::WIDTH, Cell::WIDTH}, Color::GREEN),
            Cell::createDefaultCell({Cell::WIDTH, 0}, Color::GREEN),
            Cell::createDefaultCell({Cell::WIDTH*2, 0}, Color::GREEN),
        },
        Vector2::ONE * Cell::WIDTH * 1.5f,
        m_boundary
        ));
    // T shape
    m_availableTetrominos.push_back(Tetromino(
        {
            Cell::createDefaultCell({0, Cell::WIDTH}, Color::MAGENTA),
            Cell::createDefaultCell({Cell::WIDTH, Cell::WIDTH}, Color::MAGENTA),
            Cell::createDefaultCell({Cell::WIDTH*2, Cell::WIDTH}, Color::MAGENTA),
            Cell::createDefaultCell({Cell::WIDTH, 0}, Color::MAGENTA),
        },
        Vector2::ONE * Cell::WIDTH * 1.5f,
        m_boundary
        ));
    // Z shape
    m_availableTetrominos.push_back(Tetromino(
        {
            Cell::createDefaultCell({0, 0}, Color::MAGENTA),
            Cell::createDefaultCell({Cell::WIDTH, 0}, Color::MAGENTA),
            Cell::createDefaultCell({Cell::WIDTH, Cell::WIDTH}, Color::MAGENTA),
            Cell::createDefaultCell({Cell::WIDTH*2, Cell::WIDTH}, Color::MAGENTA),
        },
        Vector2::ONE * Cell::WIDTH * 1.5f,
        m_boundary
        ));

    m_activeTetromino = m_availableTetrominos[3];
    m_activeTetromino.setPosition(m_boundary.getTopLeft());

}

void Tetris::update(uint32_t dt) {
}
void Tetris::draw(Screen& screen) {
    screen.draw(m_boundary, Color::WHITE);
    m_activeTetromino.draw(screen);
}
const std::string& Tetris::getName() const {
    static std::string name = "Tetris";
    return name;
}
