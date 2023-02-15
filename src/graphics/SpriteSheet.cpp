#include "SpriteSheet.h"

#include "app/App.h"
#include "util/FileCommandLoader.h"
#include "util/util.h"

#include <algorithm>
#include <exception>

void SpriteSheet::loadFromFile(const std::string& path) {
    FileCommandLoader loader;

    Command spriteCommand{};
    spriteCommand.command = "sprite";
    spriteCommand.parseFunc = [&](const ParseParams& params) {
        m_sections.emplace_back();
    };

    Command keyCommand{};
    keyCommand.command = "key";
    keyCommand.parseFunc = [&](const ParseParams& params) {
        m_sections.back().key = FileCommandLoader::parseString(params);
    };

    Command xPosCommand{};
    xPosCommand.command = "xPos";
    xPosCommand.parseFunc = [&](const ParseParams& params) {
        m_sections.back().sprite.x = FileCommandLoader::parseInt(params);
    };

    Command yPosCommand{};
    yPosCommand.command = "yPos";
    yPosCommand.parseFunc = [&](const ParseParams& params) {
        m_sections.back().sprite.y = FileCommandLoader::parseInt(params);
    };

    Command widthCommand{};
    widthCommand.command = "width";
    widthCommand.parseFunc = [&](const ParseParams& params) {
        m_sections.back().sprite.width = FileCommandLoader::parseInt(params);
    };

    Command heightCommand{};
    heightCommand.command = "height";
    heightCommand.parseFunc = [&](const ParseParams& params) {
        m_sections.back().sprite.height = FileCommandLoader::parseInt(params);
    };

    loader.addCommand(spriteCommand);
    loader.addCommand(keyCommand);
    loader.addCommand(xPosCommand);
    loader.addCommand(yPosCommand);
    loader.addCommand(widthCommand);
    loader.addCommand(heightCommand);

    loader.loadFile(path);
}

Sprite SpriteSheet::operator[](const std::string& key) const {
    for (const auto& section : m_sections) {
        if (stringCompare(key, section.key)) return section.sprite;
    }
    assert(false && "SpriteSheet::operator[] invalid key");
    return Sprite{};
}

std::vector<std::string> SpriteSheet::getKeys() const {
    std::vector<std::string> keys;
    keys.resize(m_sections.size());

    std::transform(m_sections.begin(),
        m_sections.end(),
        keys.begin(),
        [](const SpriteSection& section) { return section.key; });
    return keys;
}
