#pragma once

struct FieldPosition {
    int x, y;

    inline FieldPosition() : x(0), y(0) {}
    inline FieldPosition(int X, int Y) : x(X), y(Y) {}

    // --- EQUALITY ---
    inline bool operator==(const FieldPosition& v) const { return (x == v.x) && (y == v.y); }
    inline bool operator!=(const FieldPosition& v) const { return !(*this == v); }

    // --- OPERATOR OVERLOADS ---
    inline FieldPosition operator+(const FieldPosition& v) const { return FieldPosition(x + v.x, y + v.y); }
    inline FieldPosition& operator+=(const FieldPosition& v) { *this = *this + v; return *this; }

    inline FieldPosition operator-() const { return FieldPosition(-x, -y); }
    inline FieldPosition operator-(const FieldPosition& v) const { return FieldPosition(x - v.x, y - v.y); }
    inline FieldPosition& operator-=(const FieldPosition& v) { *this = *this - v; return *this; }
    
    inline FieldPosition operator*(const float scale) const { return FieldPosition(x * scale, y * scale); }
    inline FieldPosition& operator*=(const float scale) { *this = *this * scale; return *this; }
    friend inline FieldPosition operator*(float scale, const FieldPosition& v) { return v * scale; }

};
