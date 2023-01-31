#include "GameScene.h"

GameScene::GameScene(std::unique_ptr<Game> pGame) {
    m_pGame = std::move(pGame);
}

void GameScene::init() { m_pGame->init(m_controller); }
void GameScene::update(uint32_t dt) { m_pGame->update(dt); }
void GameScene::draw(Screen& screen) { m_pGame->draw(screen); }

const std::string& GameScene::getName() const {
    static std::string name = "";
    return name;
}
