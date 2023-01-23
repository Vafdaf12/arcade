#include "util.h"

#include <cmath>

#define FLOAT_THRESHOLD 1e-4

bool isEqual(float x, float y)
{
    return fabsf(x - y) < FLOAT_THRESHOLD;
}
