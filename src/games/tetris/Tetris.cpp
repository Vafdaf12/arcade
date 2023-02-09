#include "Tetris.h"

#include "app/App.h"
#include "./Tetromino.h"
#include "input/GameController.h"
#include "input/InputAction.h"
#include <cstdlib>
#include <ctime>

Tetris::Tetris() : m_playfield(AARectangle(), 0, 0) {}

void Tetris::init(GameController& controller) {
    ButtonAction dropAction;
    dropAction.key = GameController::KEY_ACTION;
    dropAction.action = [this](uint32_t dt, InputState state) {
        if (!GameController::isPressed(state)) return;
        auto dropped = dropTetromino(m_tetromino);
        placeTetromino(dropped);
        resetActiveTetromino();
    };
         
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
        if (!canMove(m_tetromino, 0, -1)) {
            placeTetromino(m_tetromino);
            resetActiveTetromino();
        } else {
            m_tetromino.move(0, -1);
        }
        m_fallTimer.reset();
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
    controller.addAction(dropAction);

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


    m_availableTetrominos = {
        Tetromino::SHAPE_I,
        Tetromino::SHAPE_L,
        Tetromino::SHAPE_J,
        Tetromino::SHAPE_O,
        Tetromino::SHAPE_T,
        Tetromino::SHAPE_Z,
        Tetromino::SHAPE_S
    };
    m_tetromino = m_availableTetrominos[1];
    m_tetromino.move(0, 10);

    m_fallTimer = Timer(1000);

    srand(time(NULL));
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
void Tetris::placeTetromino(const Tetromino& tetromino) {
    for (const auto& cell : tetromino.getCells()) {
        m_playfield.place(cell.x, cell.y, tetromino.getColor());
    }
}

void Tetris::update(uint32_t dt) {
    m_fallTimer.update(dt);

    if (m_fallTimer.elapsed()) {
        m_fallTimer.reset();
        if (canMove(m_tetromino, 0, -1)) {
            m_tetromino.move(0, -1);
        } else {
            placeTetromino(m_tetromino);
            resetActiveTetromino();
        }
    }
    m_playfield.clearLines();
}
void Tetris::resetActiveTetromino() {
    int i = rand() % m_availableTetrominos.size();
    m_tetromino = m_availableTetrominos[i];
    m_tetromino.move(0, 10);
}
Tetromino Tetris::dropTetromino(const Tetromino& tetromino) const {
    Tetromino dropped = tetromino;
    while(canMove(dropped, 0, -1)) dropped.move(0, -1);
    return dropped;
}

void Tetris::draw(Screen& screen) {
    m_playfield.draw(screen);
    m_tetromino.draw(screen, m_playfield);
}

const std::string& Tetris::getName() const {
    static std::string name = "Tetris";
    return name;
}
