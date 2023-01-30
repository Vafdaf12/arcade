#pragma once

#include <functional>
#include <stdint.h>

using InputKey = uint8_t;
using InputState = uint8_t;
using InputAction = std::function<void(uint32_t dt, InputState)>;

using MouseButton = uint8_t;

struct ButtonAction {
    InputKey key;
    InputAction action;

};

struct MousePosition {
    int32_t x, y;
};

using MouseMovedAction = std::function<void(const MousePosition& mousePosition)>;
using MouseInputAction = std::function<void(InputState, const MousePosition&)>;
struct MouseButtonAction {
    MouseButton button;
    MouseInputAction inputAction;
};

