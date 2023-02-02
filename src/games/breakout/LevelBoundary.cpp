#include "./LevelBoundary.h"

#include "./Ball.h"

LevelBoundary::LevelBoundary(const AARectangle& boundary)
    : m_excluder(boundary, true) {}

bool LevelBoundary::hasCollided(const Ball& ball, BoundaryEdge& edge) {
    for (int i = 0; i < BoundaryEdge::EdgeCount; i++) {
        BoundaryEdge::EdgeType type = static_cast<BoundaryEdge::EdgeType>(i);
        BoundaryEdge currentEdge = m_excluder.getEdge(type);

        if (hasCollidedWithEdge(ball, currentEdge)) {
            edge = currentEdge;
            return true;
        }
    }
    return false;
}

bool LevelBoundary::hasCollidedWithEdge(
    const Ball& ball, const BoundaryEdge& edge) const {
    Vector2 pos = ball.getPosition();
    return edge.edge.minDistanceTo(pos) < ball.getRadius();
}
