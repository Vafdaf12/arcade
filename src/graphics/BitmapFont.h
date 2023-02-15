#pragma once

#include "graphics/SpriteSheet.h"
#include "graphics/BMPImage.h"
#include "util/util.h"

class Vector2;
class AARectangle;

class BitmapFont {
public:
    BitmapFont() = default;

    using FontAlignment = uint8_t;

    enum AlignmentFlags {
        LeftAlign = 1 << 0,
        CenterAlign = 1 << 1,
        RightAlign = 1 << 2,

        TopAlign = 1 << 3,
        MiddleAlign = 1 << 4,
        BottomAlign = 1 << 5,
    };

    void loadFromFile(const std::string& imagePath, const std::string& sheetPath);
    Size getStringSize(const std::string& string) const;
    Vector2 getDrawPosition(const std::string& str, const AARectangle& box, FontAlignment alignment =  TopAlign | LeftAlign) const;

    inline const SpriteSheet& getSpriteSheet() const { return m_spriteSheet; }
    inline const BMPImage& getFontImage() const { return m_fontImage; }

    inline uint32_t getLetterSpacing() const { return 2; }
    inline uint32_t getWordSpacing() const { return 5; }

private:

    BMPImage m_fontImage;
    SpriteSheet m_spriteSheet;
};
