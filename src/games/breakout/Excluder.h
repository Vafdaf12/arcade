#pragma once

#include "shapes/AARectangle.h"
#include "BoundaryEdge.h"

class Excluder {
public:
    Excluder(const AARectangle& rect, bool reverseNormals = false);
    virtual ~Excluder() {}

    bool hasCollided(const AARectangle& rect, BoundaryEdge& edge) const;
    Vector2 getCollisionOffset(const AARectangle& rect) const;

    inline const AARectangle& getRect() const { return m_rect; }

    void move(const Vector2& delta);
    void setPosition(const Vector2& pos);

    const BoundaryEdge& getEdge(BoundaryEdge::EdgeType edge) const;
private:
    void setupEdges();

    AARectangle m_rect;
    BoundaryEdge m_edges[BoundaryEdge::EdgeCount];
    bool m_reverseNormals;
};
