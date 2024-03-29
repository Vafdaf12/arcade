#pragma once

#include <string>
#include <exception>

#define EPSILON 1e-4

bool isEqual(float x, float y);

float millisecondsToSeconds(int ms);

bool stringCompare(const std::string& a, const std::string& b);

struct Size {
    unsigned int width, height;
};

template<typename T>
T clamp(const T& val, const T& min, const T& max) {
    if(val > max) return max;
    if(val < min) return min;
    return val;
}

#define SDL_EXCEPT(prefix)                                                     \
    std::runtime_error(prefix + std::string(SDL_GetError()))
