#include "util.h"

#include <algorithm>
#include <cctype>
#include <cmath>

bool isEqual(float x, float y) {
    return fabsf(x - y) < EPSILON;
}

float millisecondsToSeconds(int ms) {
    return static_cast<float>(ms) / 1000.0f;
}

bool stringCompare(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) return false;

    return std::equal(a.begin(),
        a.end(),
        b.begin(),
        b.end(),
        [](unsigned char a, unsigned char b) {
            return std::tolower(a) == std::tolower(b);
        });
}
