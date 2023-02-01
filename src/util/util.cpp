#include "util.h"

#include <cmath>

bool isEqual(float x, float y)
{
    return fabsf(x - y) < EPSILON;
}

float millisecondsToSeconds(int ms) {
    return static_cast<float>(ms) / 1000.0f;
}
