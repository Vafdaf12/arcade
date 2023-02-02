#include "BreakoutLevel.h"

#include "./Ball.h"
#include "./BoundaryEdge.h"
#include "games/breakout/Block.h"

BreakoutLevel::BreakoutLevel(const AARectangle& boundary) {
    createDefaultLevel(boundary);
}

void BreakoutLevel::load(const std::vector<Block>& blocks) {
    m_blocks.clear();
    m_blocks = blocks;
}

void BreakoutLevel::update(uint32_t dt, Ball& ball) {
    std::vector<Block> collided;

    float largestOffset = -1;
    Block* pBounceBlock = nullptr;

    for (auto& block : m_blocks) {
        if (block.isDestroyed()) continue;

        BoundaryEdge edge;
        if (!block.hasCollided(ball.getBoundingBox(), edge)) continue;

        collided.push_back(block);
        float mag = block.getCollisionOffset(ball.getBoundingBox()).magnitude();
        if (mag > largestOffset) {

            largestOffset = mag;
            pBounceBlock = &block;
        }
    }

    if (pBounceBlock) {
        pBounceBlock->reduceHealth();
        pBounceBlock->bounce(ball);
    }

    for (const auto& block : collided) {
        BoundaryEdge edge;
        if (!block.hasCollided(ball.getBoundingBox(), edge)) continue;

        Vector2 p;
        ball.makeFlushWithEdge(edge, p, true);
    }
}

void BreakoutLevel::draw(Screen& screen) {
    for (auto& block : m_blocks) {
        if (block.isDestroyed()) continue;
        block.draw(screen);
    }
}
void BreakoutLevel::createDefaultLevel(const AARectangle& boundary) {
    static constexpr int BLOCK_WIDTH = 20;
    static constexpr int BLOCK_HEIGHT = 10;
    const int NBLOCKS_X = boundary.getWidth() / BLOCK_WIDTH;
    const int NBLOCKS_Y = 5;

    float startX = (boundary.getWidth() - (NBLOCKS_X * BLOCK_WIDTH)) / 2;

    Color colors[NBLOCKS_Y];
    colors[0] = Color::RED;
    colors[1] = Color::MAGENTA;
    colors[2] = Color::YELLOW;
    colors[3] = Color::GREEN;
    colors[4] = Color::CYAN;

    m_blocks.clear();

    for (int r = 0; r < NBLOCKS_Y; r++) {
        AARectangle rect(
            Vector2(startX, BLOCK_HEIGHT * (r + 1)), BLOCK_WIDTH, BLOCK_HEIGHT);
        for (int c = 0; c < NBLOCKS_X; c++) {
            Block block(rect, 1, Color::BLACK, colors[r]);
            m_blocks.push_back(block);
            rect.move(Vector2::POS_X * BLOCK_WIDTH);
        }
        rect.move(Vector2::POS_Y * BLOCK_HEIGHT);
    }
}
