#pragma once

#include "./Excluder.h"
#include "./BoundaryEdge.h"

class AARectangle;
class Ball;

class LevelBoundary {
public:
    LevelBoundary(const AARectangle& boundary);
    
    bool hasCollided(const Ball& ball, BoundaryEdge& edge);
    inline const AARectangle& getRect() const { return m_excluder.getRect(); }

private:
    bool hasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const;
    Excluder m_excluder;
};
