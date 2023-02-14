#include "BitmapFont.h"

#include "shapes/AARectangle.h"
#include "util/Vector2.h"

void BitmapFont::loadFromFile(
    const std::string& imagePath, const std::string& sheetPath) {
    m_fontImage.loadFromFile(imagePath);
    m_spriteSheet.loadFromFile(sheetPath);
}

Size BitmapFont::getStringSize(const std::string& str) const {
    Size textSize{};

    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (c == ' ') {
            textSize.width += getWordSpacing();
            continue;
        }

        Sprite sprite = m_spriteSheet[std::string(1, c)];
        textSize.height = std::max(textSize.height, sprite.height);

        textSize.width += sprite.width;

        if (i + 1 == str.size()) continue;
        textSize.width += getLetterSpacing();
    }
    return textSize;
}
Vector2 BitmapFont::getDrawPosition(
    const std::string& str, const AARectangle& box, FontAlignment alignment) const {

    Size size = getStringSize(str);
    Vector2 pos;

    // vertical alignment
    if (alignment & TopAlign) {
        pos.y = box.getTopLeft().y;
    } else if (alignment & MiddleAlign) {
        pos.y = box.getTopLeft().y + (box.getHeight() - size.height) / 2.0f;

    } else if (alignment & BottomAlign) {
        pos.y = box.getBottomRight().y - size.height;
    }

    // horizontal alignment
    if (alignment & LeftAlign) {
        pos.x = box.getTopLeft().x;
    } else if (alignment & CenterAlign) {
        pos.x = box.getTopLeft().x + (box.getWidth() - size.width) / 2.0f;

    } else if (alignment & RightAlign) {
        pos.x = box.getBottomRight().x - size.height;
    }

    return pos;
}
