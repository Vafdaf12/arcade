#pragma once

#include "shapes/Line2D.h"
#include "util/Vector2.h"

struct BoundaryEdge {
    Vector2 normal;
    Line2D edge;

    enum EdgeType {
        Bottom = 0,
        Top,
        Left,
        Right,
        EdgeCount

    };
};
