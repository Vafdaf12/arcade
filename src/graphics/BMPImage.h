#pragma once

#include "Color.h"
#include <vector>
#include <string>
#include <stdint.h>

class BMPImage {
public:
    BMPImage();
    bool loadFromFile(const std::string& path);

    inline const std::vector<Color>& getPixels() const { return m_pixels; }

    inline uint32_t width() const { return m_width; }
    inline uint32_t height() const { return m_height; }

private:
    std::vector<Color> m_pixels;
    uint32_t m_width;
    uint32_t m_height;
};
