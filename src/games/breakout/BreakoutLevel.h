#pragma once

#include "./Block.h"

#include <vector>

class AARectangle;
class Ball;
class Screen;

class BreakoutLevel {
public:
    BreakoutLevel(const AARectangle& boundary);

    void load(const std::vector<Block>& blocks);

    void update(uint32_t dt, Ball& ball);

    void draw(Screen& screen);

    static std::vector<BreakoutLevel> loadFromFile(const std::string& path);
    
private:
    void createDefaultLevel(const AARectangle& boundary);

    std::vector<Block> m_blocks;
};
