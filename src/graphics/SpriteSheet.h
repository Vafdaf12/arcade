#pragma once

#include "graphics/BMPImage.h"

#include <stdint.h>
#include <string>
#include <vector>

struct Sprite {
    uint32_t x, y;
    uint32_t width, height;
};

class SpriteSheet {
public:
    using SpriteKey = std::string;

    SpriteSheet() = default;

    void loadFromFile(const std::string& path);

    Sprite operator[](const SpriteKey& key) const;

    std::vector<SpriteKey> getKeys() const;

private:
    void loadSpriteSections(const std::string& path);

    struct SpriteSection {
        Sprite sprite;
        SpriteKey key;
    };
    std::vector<SpriteSection> m_sections;
    BMPImage m_image;
};
