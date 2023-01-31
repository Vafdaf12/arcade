#pragma once

#include <string>
#include <stdint.h>

class GameController;
class Screen;

class Game {
public:
    virtual ~Game() {}

    virtual void init(GameController& pController) = 0;
    virtual void update(uint32_t dt) = 0;
    virtual void draw(Screen& screen) = 0;
    virtual const std::string& getName() const = 0;
};
