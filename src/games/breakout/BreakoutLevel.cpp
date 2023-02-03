#include "BreakoutLevel.h"

#include "./Ball.h"
#include "./BoundaryEdge.h"
#include "app/App.h"
#include "games/breakout/Block.h"
#include "util/FileCommandLoader.h"
#include <algorithm>

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

struct LayoutBlock {
    char symbol = '-';
    int health = 0;
    Color color = Color::BLACK;
};

std::vector<LayoutBlock>::const_iterator findSymbol(
    const std::vector<LayoutBlock>& blocks, char symbol) {
    return std::find_if(blocks.begin(),
        blocks.end(),
        [&](const LayoutBlock& layout) { return layout.symbol == symbol; });
}

std::vector<BreakoutLevel> BreakoutLevel::loadFromFile(
    const std::string& path) {
    static constexpr int BLOCK_WIDTH = 16;
    static constexpr int BLOCK_HEIGHT = 8;

    App& app = App::Singleton();

    std::vector<BreakoutLevel> levels;
    std::vector<LayoutBlock> layoutBlocks;
    std::vector<Block> levelBlocks;

    int width = 0;
    int height = 0;

    FileCommandLoader loader;

    // --- LEVEL COMMANDS ---
    Command levelCommand("level", [&](const ParseParams& params) {
        if (levels.size() != 0) levels.back().load(levelBlocks);
        levelBlocks.clear();
        width = 0;
        height = 0;

        levels.emplace_back(
            AARectangle(Vector2::ZERO, app.width(), app.height()));
    });
    loader.addCommand(levelCommand);

    Command widthCommand("width", [&](const ParseParams& params) {
        width = FileCommandLoader::parseInt(params);
    });
    loader.addCommand(widthCommand);
    Command heightCommand("height", [&](const ParseParams& params) {
        height = FileCommandLoader::parseInt(params);
    });
    loader.addCommand(heightCommand);

    // --- BLOCK COMMANDS ---
    Command blockCommand("block", [&](const ParseParams&) {
        LayoutBlock block{};
        layoutBlocks.push_back(block);
    });
    loader.addCommand(blockCommand);

    Command symbolCommand("symbol", [&](const ParseParams& params) {
        layoutBlocks.back().symbol = FileCommandLoader::parseChar(params);
    });
    loader.addCommand(symbolCommand);

    Command fillCommand("fillcolor", [&](const ParseParams& params) {
        layoutBlocks.back().color = FileCommandLoader::parseColor(params);
    });
    loader.addCommand(fillCommand);

    Command hpCommand("hp", [&](const ParseParams& params) {
        layoutBlocks.back().health = FileCommandLoader::parseInt(params);
    });
    loader.addCommand(hpCommand);

    // -- MAIN LAYOUT ---
    Command layoutCommand(
        "layout",
        [&](const ParseParams& params) {
            float startX =
                static_cast<float>(app.width() - BLOCK_WIDTH * width) / 2;

            AARectangle rect(
                Vector2(startX, (params.lineNum + 1) * BLOCK_HEIGHT),
                BLOCK_WIDTH,
                BLOCK_HEIGHT);

            for (int x = 0; x < params.line.length(); x++) {
                if (params.line[x] != '-') {
                    auto layoutBlock = findSymbol(layoutBlocks, params.line[x]);
                    assert(layoutBlock != layoutBlocks.end());

                    levelBlocks.emplace_back(rect,
                        layoutBlock->health,
                        Color::BLACK,
                        layoutBlock->color);
                }
                rect.move(Vector2(BLOCK_WIDTH, 0));
            }
        },
        CommandType::Multiline);
    loader.addCommand(layoutCommand);

    // Parse file
    loader.loadFile(path);
    if (levels.size() > 0) levels.back().load(levelBlocks);

    return levels;
}
bool BreakoutLevel::isLevelComplete() const {
    for(const auto& block : m_blocks) {
        if(block.getHealth() == Block::UNBREAKABLE) continue;
        if(!block.isDestroyed() ) return false;
    }
    return true;
}
