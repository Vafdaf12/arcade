#pragma once

#include <string>

#define EPSILON 1e-4

bool isEqual(float x, float y);

float millisecondsToSeconds(int ms);

bool stringCompare(const std::string& a, const std::string& b);

struct Size {
    unsigned int width, height;
};
