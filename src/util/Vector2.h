#pragma once

#include "util.h"

#include <cmath>
#include <iostream>
#include <assert.h>

struct Vector2 {
    inline Vector2(): x(0), y(0) {}
    inline Vector2(float X, float Y): x(X), y(Y) {}
    
    inline static Vector2 fromAngle(float a) { return Vector2(cosf(a), sinf(a)); }

    // --- UTILS ---
    inline void set(float nx, float ny) { x = nx; y = ny; }

    // --- PROPERTIES ---
    float x, y;
    inline float magnitude()    const { return hypot(x, y); }
    inline float sqrMagnitude() const { return dot(*this); }

    // --- EQUALITY ---
    inline bool equals(const Vector2& v) const { return x == v.x && y == v.y; }
    inline bool operator==(const Vector2& v) const { return isEqual(x, v.x) && isEqual(x, v.y); }
    inline bool operator!=(const Vector2& v) const { return !(*this == v); }

    // --- OPERATOR OVERLOADS ---
    inline Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
    inline Vector2& operator+=(const Vector2& v) { *this = *this + v; return *this; }

    inline Vector2 operator-() const { return Vector2(-x, -y); }
    inline Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
    inline Vector2& operator-=(const Vector2& v) { *this = *this - v; return *this; }
    
    inline Vector2 operator*(const float scale) const { return Vector2(x * scale, y * scale); }
    inline Vector2& operator*=(const float scale) { *this = *this * scale; return *this; }
    friend inline Vector2 operator*(float scale, const Vector2& v) { return v * scale; }

    inline Vector2 operator/(const float scale) const {  return Vector2(x / scale, y / scale); }
    inline Vector2& operator/=(const float scale) { *this /= scale; return *this; }
    
    // --- OUTPUT ---
    friend std::ostream& operator<<(std::ostream& consoleOut, const Vector2& v) {
        consoleOut << "Vector2(" << v.x << ", " << v.y << ")";
        return consoleOut;
    }

    /**
     * @brief Calculate the angle to v.
     * 
     * @param v The destination vector
     * 
     * @return The angle between 'this' and 'v'
     */
    inline float angle(const Vector2& v) const { return acosf(this->dot(v) / v.magnitude() / this->magnitude()); }
    
    /**
     * @brief Calculate the distance to v.
     * 
     * @param v The 'destination' point
     * 
     * @return The distance between 'this' and 'v' 
    */
    inline float distance(const Vector2& v) const { return (*this - v).magnitude(); }

    /**
     * Reflect around normal n
     * 
     * @param n The normal for reflection
     * 
     * @return The reflected vector
    */
    inline Vector2 reflect(const Vector2& n) const { return *this - projectOnto(n) * 2; }
 
    /**
     * Normalize the current vector.
     * 
     * @return A reference to the current vector(for any further operations) 
    */
    inline Vector2& normalize() { *this = normalized(); return *this; }

    /**
     * Get the normalized vector of the current vector.
     * 
     * @return A normalized vector
    */
    inline Vector2 normalized() const {
        if(isEqual(0, magnitude())) return ZERO;
        return *this / magnitude();
    }
    
    /**
     * Perform a dot product between the current vector and v.
     * 
     * @param v The vector to perform the dot product with
     * 
     * @return The result of the dot product
    */
    inline float dot(const Vector2& v) const { return x * v.x + y * v.y; }

    /**
     * Perform a cross product between the current vector and v.
     * 
     * @param v The vector to perform the cross product with
     * 
     * @return The result of the cross product
    */
    inline float cross(const Vector2& v) const { return x * v.y - y * v.x; }
 
    /**
     * Project the vector onto the normalized vector v.
     * Math: dot(this, v.normalized) * v
     * 
     * @param v The vector to be projected onto(will be normalized).
    */
    inline Vector2 projectOnto(const Vector2& v) const { return v * dot(v.normalized()) ; }
    
    /**
     * Rotate the current vector.
     * 
     * @param angle The angle to rotate by(in radians)
     * @return The rotated vector.
    */
    inline Vector2 rotate(float angle) const { return rotate(angle, Vector2(0, 0)); }

    /**
     * Rotate the current vector around a point.
     * 
     * @param origin The origin point to rotate around
     * @param angle The angle to rotate by(in radians)
     * 
     * @return The rotated vector.
    */
    Vector2 rotate(float angle, const Vector2& origin) const {
        float cosine = cosf(angle);
        float sine = sinf(angle);

        Vector2 relative = *this - origin;
        Vector2 rotated(
            relative.x*cosine - relative.y*sine,
            relative.x*sine + relative.y*cosine
        );

        return origin + rotated;
    }

    // --- STATIC VALUES ---
    static const Vector2 ZERO;
    static const Vector2 ONE;

    static const Vector2 POS_X;
    static const Vector2 POS_Y;

    static const Vector2 NEG_X;
    static const Vector2 NEG_Y;

};
