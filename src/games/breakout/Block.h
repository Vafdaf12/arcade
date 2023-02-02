#pragma once

#include "Excluder.h"

#include "graphics/Color.h"

class Ball;
class Screen;
struct BoundaryEdge;

class Block : public Excluder {
    public:
        static constexpr int UNBREAKABLE = -1;

        Block();
        Block(const AARectangle& rect, int hp, const Color& outline, const Color& fill);

        void draw(Screen& screen);
        void bounce(Ball& ball);
        void reduceHealth();

        inline int getHealth() const { return m_health; }
        inline bool isDestroyed() const { return m_health == 0; }
        inline const Color& getOutlineColor() const { return m_outline; }
        inline const Color& getFillColor() const { return m_fill; }

    private:
        Color m_outline;
        Color m_fill;


        int m_health = -1;
};
