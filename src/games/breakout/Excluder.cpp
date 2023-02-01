#include "Excluder.h"
#include "util/util.h"
#include <cassert>

Excluder::Excluder(const AARectangle& rect, bool reverseNormals) {
    m_reverseNormals = reverseNormals;
    m_rect = rect;

    setupEdges();
}

bool Excluder::hasCollided(const AARectangle& rect, BoundaryEdge& edge) const {
    if (!m_rect.intersects(rect)) return false;

    float yMin = std::max(m_rect.getTopLeft().y, rect.getTopLeft().y);
    float yMax = std::min(m_rect.getBottomRight().y, rect.getBottomRight().y);
    float ySize = yMax - yMin;

    float xMin = std::max(m_rect.getTopLeft().x, rect.getTopLeft().x);
    float xMax = std::min(m_rect.getBottomRight().x, rect.getBottomRight().x);
    float xSize = xMax - xMin;

    BoundaryEdge::EdgeType type = BoundaryEdge::EdgeCount;

    // intersect more over horizontal edge
    if (xSize > ySize) {
        if (rect.getCenterPoint().y > m_rect.getCenterPoint().y)
            type = BoundaryEdge::Bottom;
        else type = BoundaryEdge::Top;
    }
    // intersects more over vertical edge
    else {
        if (rect.getCenterPoint().x > m_rect.getCenterPoint().x)
            type = BoundaryEdge::Right;
        else type = BoundaryEdge::Left;
    }

    edge = getEdge(type);

    return true;
}
Vector2 Excluder::getCollisionOffset(const AARectangle& rect) const {

    BoundaryEdge edge;
    if (!hasCollided(rect, edge)) return Vector2::ZERO;

    float yMin = std::max(m_rect.getTopLeft().y, rect.getTopLeft().y);
    float yMax = std::min(m_rect.getBottomRight().y, rect.getBottomRight().y);
    float ySize = yMax - yMin;

    float xMin = std::max(m_rect.getTopLeft().x, rect.getTopLeft().x);
    float xMax = std::min(m_rect.getBottomRight().x, rect.getBottomRight().x);
    float xSize = xMax - xMin;

    Vector2 offset = Vector2::ZERO;

    if (isEqual(edge.normal.y, 0)) offset = (ySize + 1) * edge.normal;
    else offset = (xSize + 1) * edge.normal;

    return offset;
}

void Excluder::move(const Vector2& delta) {
    m_rect.move(delta);
    setupEdges();
}
void Excluder::setPosition(const Vector2& pos) {
    m_rect.moveTo(pos);
    setupEdges();
}

const BoundaryEdge& Excluder::getEdge(BoundaryEdge::EdgeType edge) const {
    assert(edge != BoundaryEdge::EdgeCount);
    return m_edges[edge];
}

void Excluder::setupEdges() {
    Vector2 tl = m_rect.getTopLeft();
    Vector2 br = m_rect.getBottomRight();

    int dir = m_reverseNormals ? -1 : 1;

    m_edges[BoundaryEdge::Bottom].edge = Line2D(br, {tl.x, br.y});
    m_edges[BoundaryEdge::Top].edge = Line2D(tl, {br.x, tl.y});
    m_edges[BoundaryEdge::Right].edge = Line2D({br.x, tl.y}, br);
    m_edges[BoundaryEdge::Left].edge = Line2D(tl, {tl.x, br.y});

    m_edges[BoundaryEdge::Bottom].normal = Vector2(0, dir);
    m_edges[BoundaryEdge::Top].normal = Vector2(0, -dir);
    m_edges[BoundaryEdge::Right].normal = Vector2(dir, 0);
    m_edges[BoundaryEdge::Left].normal = Vector2(-dir, 0);
}
