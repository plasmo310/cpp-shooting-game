#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
:x(0.0f)
,y(0.0f)
{}

Vector2::Vector2(float inX, float inY)
:x(inX)
,y(inY)
{}

// vec + vec
Vector2 operator+(const Vector2& a, const Vector2& b)
{
    return Vector2(a.x + b.x, a.y + b.y);
}

// vec - vec
Vector2 operator-(const Vector2& a, const Vector2& b)
{
    return Vector2(a.x - b.x, a.y - b.y);
}

// vec * vec
Vector2 operator*(const Vector2& a, const Vector2& b)
{
    return Vector2(a.x * b.x, a.y * b.y);
}

// vec * scalar
Vector2 operator*(const Vector2& vec, float scalar)
{
    return Vector2(vec.x * scalar, vec.y * scalar);
}

// += vec
Vector2& Vector2::operator+=(const Vector2& right)
{
    x += right.x;
    y += right.y;
    return *this;
}

// -=vector
Vector2& Vector2::operator-=(const Vector2& right)
{
    x -= right.x;
    y -= right.y;
    return *this;
}

// *= scalar
Vector2& Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

// vec length
float Vector2::Length() const
{
    return (sqrtf(x*x + y*y));
}

// vec length(not sqrt)
float Vector2::LengthSq() const
{
    return (x*x + y*y);
}

// zero vec
const Vector2 Vector2::Zero(0.0f, 0.0f);
