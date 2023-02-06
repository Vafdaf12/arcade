#include "Tetris.h"

#include "app/App.h"
#include "input/GameController.h"
#include "input/InputAction.h"

Tetris::Tetris() : m_playfield(AARectangle(), 0, 0) {}

void Tetris::init(GameController& controller) {
    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::KEY_LEFT;
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if (!GameController::isPressed(state)) return;
        if (!canMove(m_tetromino, -1, 0)) return;
        m_tetromino.move(-1, 0);
    };
    ButtonAction upKeyAction;
    upKeyAction.key = GameController::KEY_UP;
    upKeyAction.action = [this](uint32_t dt, InputState state) {
        if (!GameController::isPressed(state)) return;
        if (!canRotate(m_tetromino)) return;
        m_tetromino.rotate();
    };
    ButtonAction downKeyAction;
    downKeyAction.key = GameController::KEY_DOWN;
    downKeyAction.action = [this](uint32_t dt, InputState state) {
        if (!GameController::isPressed(state)) return;
        if (!canMove(m_tetromino, 0, -1)) return;
        m_tetromino.move(0, -1);
    };

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::KEY_RIGHT;
    rightKeyAction.action = [this](uint32_t dt, InputState state) {
        if (!GameController::isPressed(state)) return;
        if (!canMove(m_tetromino, 1, 0)) return;
        m_tetromino.move(1, 0);
    };

    controller.addAction(rightKeyAction);
    controller.addAction(leftKeyAction);
    controller.addAction(upKeyAction);
    controller.addAction(downKeyAction);

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

    m_tetromino = Tetromino({FieldPosition(0, 0),
                                FieldPosition(1, 0),
                                FieldPosition(2, 0),
                                FieldPosition(0, 1)},
        {1, 0},
        Color::CYAN,
        {5, 5});
}

bool Tetris::canMove(const Tetromino& tetromino, int dx, int dy) const {
    for (const auto& cell : tetromino.getCells()) {
        if (!m_playfield.canPlace(cell.x + dx, cell.y + dy)) return false;
    }
    return true;
}
bool Tetris::canRotate(const Tetromino& tetromino, bool clockwise) const {
    Tetromino next = tetromino;
    next.rotate(clockwise);
    for (const auto& cell : next.getCells()) {
        if (!m_playfield.canPlace(cell.x, cell.y)) return false;
    }
    return true;
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
