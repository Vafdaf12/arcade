#include "Tetris.h"

#include "./Tetromino.h"
#include "app/App.h"
#include "input/GameController.h"
#include "input/InputAction.h"

#include <cstdlib>
#include <ctime>
#include <random>

Tetris::Tetris()
    : m_playfield(AARectangle(), 0, 0), m_nextField(AARectangle(), 0, 0) {}

void Tetris::init(GameController& controller) {
    ButtonAction dropAction;
    dropAction.key = GameController::KEY_ACTION;
    dropAction.action = [this](uint32_t dt, InputState state) {
        if (!GameController::isPressed(state)) return;
        if (isGameOver()) resetGame();
        else {
            auto dropped = dropTetromino(m_tetromino);
            placeTetromino(dropped);
            nextTetromino();
        }
    };

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::KEY_LEFT;
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if (isGameOver()) return;
        if (!GameController::isPressed(state)) return;
        if (!canMove(m_tetromino, -1, 0)) return;
        m_tetromino.move(-1, 0);
    };
    ButtonAction upKeyAction;
    upKeyAction.key = GameController::KEY_UP;
    upKeyAction.action = [this](uint32_t dt, InputState state) {
        if (isGameOver()) return;
        if (!GameController::isPressed(state)) return;
        if (!canRotate(m_tetromino)) return;
        m_tetromino.rotate();
    };

    ButtonAction downKeyAction;
    downKeyAction.key = GameController::KEY_DOWN;
    downKeyAction.action = [this](uint32_t dt, InputState state) {
        if (isGameOver()) return;
        if (!GameController::isPressed(state)) return;
        if (!canMove(m_tetromino, 0, -1)) {
            placeTetromino(m_tetromino);
            nextTetromino();
        } else {
            m_tetromino.move(0, -1);
        }
        m_fallTimer.reset();
    };

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::KEY_RIGHT;
    rightKeyAction.action = [this](uint32_t dt, InputState state) {
        if (isGameOver()) return;
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

    AARectangle boundary = AARectangle(Vector2::ZERO,
        Playfield::CELL_WIDTH * FIELD_WIDTH,
        Playfield::CELL_WIDTH * FIELD_HEIGHT);
    AARectangle nextField(
        Vector2::ZERO, Playfield::CELL_WIDTH * 6, Playfield::CELL_WIDTH * 6);

    Vector2 pos = {
        (app.width() - boundary.getWidth() - nextField.getWidth()) / 2.0f,
        (app.height() - boundary.getHeight()) / 2.0f};

    boundary.setPosition(pos);

    nextField.setPosition(
        boundary.getTopLeft() + Vector2(boundary.getWidth() + 3, 0));

    m_playfield = Playfield(boundary, FIELD_WIDTH, FIELD_HEIGHT);
    m_nextField = Playfield(nextField, 6, 6);

    m_availableTetrominos = {
        Tetromino::SHAPE_I,
        Tetromino::SHAPE_L,
        Tetromino::SHAPE_J,
        Tetromino::SHAPE_O,
        Tetromino::SHAPE_T,
        Tetromino::SHAPE_Z,
        Tetromino::SHAPE_S,
    };

    m_randomEngine = std::default_random_engine(time(0));
    m_rand =
        std::uniform_int_distribution<int>(0, m_availableTetrominos.size() - 1);

    resetGame();
}

void Tetris::resetGame() {
    // reset playfields
    m_playfield.clear();
    m_nextField.clear();

    // reset timer duration
    m_fallTimer.setDuration(1000);
    m_fallTimer.reset();

    // reset game state
    m_state = Playing;
    m_score = 0;

    // reset playing tetrominos
    m_nextTetromino = m_availableTetrominos[m_rand(m_randomEngine)];
    nextTetromino();
}

bool Tetris::canPlace(const Tetromino& tetromino) const {
    for (const auto& cell : tetromino.getCells()) {
        if (!m_playfield.canPlace(cell.x, cell.y)) return false;
    }
    return true;
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
    if (isGameOver()) return;
    m_fallTimer.update(dt);

    if (m_fallTimer.elapsed()) {
        m_fallTimer.reset();

        if (canMove(m_tetromino, 0, -1)) m_tetromino.move(0, -1);
        else if (!canPlace(m_tetromino)) m_state = GameOver;

        else {
            placeTetromino(m_tetromino);
            nextTetromino();
        }
    }
    uint32_t nLines = m_playfield.clearLines();
    if (nLines == 0) return;

    uint32_t score = 100;
    for (uint32_t i = 1; i < nLines; i++)
        score *= 2;
    if (nLines == 4) score += 1000;

    m_score += score;
}

void Tetris::nextTetromino() {
    // place new tetromino at correct spawn position
    m_tetromino = m_nextTetromino;
    int x = (m_playfield.width() - m_tetromino.width()) / 2;
    int y = (m_playfield.height() - m_tetromino.height()) - 1;
    m_tetromino.setOffset(x, y);

    // select new tetromino
    m_nextTetromino = m_availableTetrominos[m_rand(m_randomEngine)];
    m_nextTetromino.setOffset(1, 0);
    m_nextTetromino.setOffset(
        (m_nextField.width() - m_nextTetromino.width()) / 2,
        (m_nextField.height() - m_nextTetromino.height()) / 2);
}

Tetromino Tetris::dropTetromino(const Tetromino& tetromino) const {
    Tetromino dropped = tetromino;
    while (canMove(dropped, 0, -1))
        dropped.move(0, -1);
    return dropped;
}

void Tetris::draw(Screen& screen) {
    m_playfield.draw(screen);
    m_tetromino.draw(screen, m_playfield);

    m_nextTetromino.draw(screen, m_nextField);
    m_nextField.draw(screen);
}

const std::string& Tetris::getName() const {
    static std::string name = "Tetris";
    return name;
}
