#include "util.h"

#include <cmath>

bool isEqual(float x, float y)
{
    return fabsf(x - y) < EPSILON;
}
