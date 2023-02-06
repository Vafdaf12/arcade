#include "Tetris.h"

#include "app/App.h"
#include "input/GameController.h"
#include "input/InputAction.h"

Tetris::Tetris() : m_playfield(AARectangle(), 0, 0) {}

void Tetris::init(GameController& controller) {
    ButtonAction spaceAction;
    spaceAction.key = GameController::KEY_SPACE;
    spaceAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::isPressed(state)) {
            uint32_t score = m_playfield.clearLines();
            std::cout << "Cleared Lines: " << score << "\n";
        }
    };

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::KEY_LEFT;
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::isPressed(state)) {
            m_tetromino.rotate();
            // move tetromino left
        }
    };
    /*

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
            m_activeTetromino.move({Playfield::CELL_WIDTH, 0});
        }
    };

    controller.addAction(rightKeyAction);
    controller.addAction(actionKeyAction);
    controller.addAction(cancelKeyAction);
    */

    controller.addAction(spaceAction);
    controller.addAction(leftKeyAction);

    App& app = App::Singleton();
    AARectangle boundary = AARectangle(
        Vector2::ZERO, Playfield::CELL_WIDTH * 10, Playfield::CELL_WIDTH * 20);

    Vector2 pos = {(app.width() - boundary.getWidth()) / 2.0f,
        (app.height() - boundary.getHeight()) / 2.0f};

    boundary.setPosition(pos);

    m_playfield = Playfield(boundary, FIELD_WIDTH, FIELD_HEIGHT);

    for (size_t i = 0; i < FIELD_WIDTH; i++) {
        m_playfield.place(i, 0, Color::YELLOW);
        m_playfield.place(i, 2, Color::MAGENTA);
    }
    m_playfield.place(2, 1, Color::BLUE);
    m_playfield.place(3, 3, Color::ORANGE);

    m_tetromino = Tetromino({
            FieldPosition(0, 0),
            FieldPosition(1, 0),
            FieldPosition(2, 0),
            FieldPosition(0, 1)
        },
        {1, 0},
        Color::CYAN, {5, 5});
}

void Tetris::update(uint32_t dt) {}

void Tetris::draw(Screen& screen) {
    m_playfield.draw(screen);
    m_tetromino.draw(screen, m_playfield);
}

const std::string& Tetris::getName() const {
    static std::string name = "Tetris";
    return name;
}
