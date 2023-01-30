#pragma once

#include <stdint.h>
#include <string>

#include "input/GameController.h"

class Screen;

class Scene {
public:
    virtual ~Scene() {}

    virtual void init() = 0;
    virtual const std::string& getName() const = 0;

    virtual void update(uint32_t dt) = 0;
    virtual void draw(Screen& screen) = 0;

    inline GameController* getController() { return &m_controller; }

protected:
    GameController m_controller;
};
