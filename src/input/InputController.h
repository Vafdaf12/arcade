#pragma once

#include "InputAction.h"

class GameController;

class InputController {
public:
    InputController();
    void init(InputAction quitAction);

    void update(uint32_t dt);

    void setGameController(GameController* pController);

private:
    InputAction m_quit;
    GameController* m_pCurrentController;
};
