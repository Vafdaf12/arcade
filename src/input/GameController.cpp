#include "GameController.h"

#include <SDL.h>

#include <algorithm>

InputAction GameController::getAction(InputKey key) {
    for (const auto& buttonAction : m_buttonActions) {
        if (buttonAction.key == key) return buttonAction.action;
    }
    return [](uint32_t, InputState) {};
}
void GameController::addAction(const ButtonAction& buttonAction) {
    m_buttonActions.push_back(buttonAction);
}

void GameController::clear() { m_buttonActions.clear(); }

bool GameController::isPressed(InputState state) {
    return state == SDL_PRESSED;
}
bool GameController::isReleased(InputState state) {
    return state == SDL_RELEASED;
}

InputKey GameController::KEY_ACTION(static_cast<InputKey>(SDLK_a));
InputKey GameController::KEY_CANCEL(static_cast<InputKey>(SDLK_s));
InputKey GameController::KEY_LEFT(static_cast<InputKey>(SDLK_LEFT));
InputKey GameController::KEY_RIGHT(static_cast<InputKey>(SDLK_RIGHT));
InputKey GameController::KEY_UP(static_cast<InputKey>(SDLK_UP));
InputKey GameController::KEY_DOWN(static_cast<InputKey>(SDLK_DOWN));
