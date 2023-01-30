#pragma once

#include "InputAction.h"
#include <vector>

class GameController {
public:
    GameController() {}

    InputAction getAction(InputKey key);
    void addAction(const ButtonAction&  buttonAction);

    void clear();

    static bool isPressed(InputState state);
    static bool isReleased(InputState state);

    static InputKey KEY_ACTION;
    static InputKey KEY_CANCEL;
    static InputKey KEY_LEFT;
    static InputKey KEY_RIGHT;
    static InputKey KEY_UP;
    static InputKey KEY_DOWN;



private:
    std::vector<ButtonAction> m_buttonActions;
};
