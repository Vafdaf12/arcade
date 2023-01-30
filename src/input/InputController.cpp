#include "InputController.h"

#include "input/GameController.h"
#include "input/InputAction.h"

#include <SDL_events.h>

InputController::InputController()
    : m_pCurrentController(nullptr), m_quit(nullptr) {}

void InputController::init(InputAction quitAction) { m_quit = quitAction; }

void InputController::update(uint32_t dt) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: m_quit(dt, SDL_PRESSED); break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (m_pCurrentController) {
                InputAction action =
                    m_pCurrentController->getAction(event.key.keysym.sym);
                action(dt, event.key.state);
            }
            break;
        }
    }
}

void InputController::setGameController(GameController* pController) {
    m_pCurrentController = pController;
}
