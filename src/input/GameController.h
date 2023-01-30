#pragma once

#include "InputAction.h"
#include <vector>

class GameController {
public:
    GameController();

    InputAction getAction(InputKey key);
    void addAction(const ButtonAction&  buttonAction);

    void clear();

    static bool isPressed(InputState state);
    static bool isReleased(InputState state);

    inline MouseMovedAction getMouseMovedAction() const { return m_mouseMovedAction; }
    inline void setMouseMovedAction(const MouseMovedAction& action) {  m_mouseMovedAction = action; }

    MouseInputAction getMouseInputAction(MouseButton button) const;
    void addMouseInputAction(MouseButtonAction button);

    static InputKey KEY_ACTION;
    static InputKey KEY_CANCEL;
    static InputKey KEY_LEFT;
    static InputKey KEY_RIGHT;
    static InputKey KEY_UP;
    static InputKey KEY_DOWN;

    static MouseButton MOUSE_BUTTON_LEFT;
    static MouseButton MOUSE_BUTTON_RIGHT;
    static MouseButton MOUSE_BUTTON_MIDDLE;

private:
    std::vector<ButtonAction> m_buttonActions;
    std::vector<MouseButtonAction> m_mouseButtonActions;

    MouseMovedAction m_mouseMovedAction;
};
