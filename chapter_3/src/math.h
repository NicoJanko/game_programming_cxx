#ifndef MATH_H
#define MATH_H
#include <cmath>
#include <limits>
#include <numbers>

namespace Math {

const float pi = std::numbers::pi_v<float>;
const float twoPi = pi * 2.0f;
const float piOver2 = pi / 2.0f;
const float infinity = std::numeric_limits<float>::infinity();
const float negInfinity = -std::numeric_limits<float>::infinity();

inline float toRadians(float degrees) { return degrees * pi / 180.0f; }

inline float toDegrees(float radians) { return radians * 180.0f / pi; }

inline bool nearZero(float val, float epsilon) { return std::fabs(val) <= epsilon; }

} // namespace Math

class Vector2 {
  public:
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}

    explicit Vector2(float inX, float inY) : x(inX), y(inY) {}

    void set(float inX, float inY) {
        x = inX;
        y = inY;
    }

    // move an object
    friend Vector2 operator+(const Vector2& a, const Vector2& b) {
        return Vector2(a.x + b.x, a.y + b.y);
    }
    // vector from a to b
    // lenght of a-b is distance
    friend Vector2 operator-(const Vector2& a, const Vector2& b) {
        return Vector2(a.x - b.x, a.y - b.y);
    }

    friend Vector2 operator*(const Vector2& a, const Vector2& b) {
        return Vector2(a.x * b.x, a.y * b.y);
    }

    friend Vector2 operator*(const Vector2& a, float scalar) {
        return Vector2(a.x * scalar, a.y * scalar);
    }

    friend Vector2 operator*(float scalar, const Vector2& a) {
        return Vector2(a.x * scalar, a.y * scalar);
    }

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator+=(const Vector2& b) {
        x += b.x;
        y += b.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& b) {
        x -= b.x;
        y -= b.y;
        return *this;
    }
    // compare distance
    float lenghtSeq() const { return ((x * x) + (y * y)); }

    float lenght() const { return std::sqrt(lenghtSeq()); }

    void normalize() {
        float len = lenght();
        x /= len;
        y /= len;
    }
    // sign gives in front or behind
    static float dot(const Vector2& a, const Vector2& b) { return (a.x * b.x + a.y * b.y); }
    // if f = 0.5 partway between a and b
    static Vector2 lerp(const Vector2& a, const Vector2& b, float f) {
        return Vector2(a + f * (b - a));
    }
    // bouce of a surface
    static Vector2 reflect(const Vector2& a, const Vector2& b) {
        return a - 2.0f * Vector2::dot(a, b) * b;
    }
};

#endif
