#include "vec2d.h"

#include "my_math.h"

double Vec2d::lengthSq() const
{
    return dot(*this);
}

double Vec2d::length() const
{
    return sqrt(lengthSq());
}

double Vec2d::sum() const
{
    return x + y;
}

void Vec2d::negate()
{
    x = -x;
    y = -y;
}

void Vec2d::norm()
{
    *this /= length();
}

void Vec2d::rotate(double angle)
{
    double s = sin(angle);
    double c = cos(angle);
    double oldX = x;
    x = c * x - s * y;
    y = s * oldX + c * y;
}

void Vec2d::perpPos()
{
    double oldX = x;
    x = -y;
    y = oldX;
}

void Vec2d::perpNeg()
{
    double oldX = x;
    x = y;
    y = -oldX;
}

Vec2d Vec2d::normed() const
{
    Vec2d w(*this);
    w.norm();
    return w;
}

Vec2d Vec2d::rotated(double a) const
{
    Vec2d w(*this);
    w.rotate(a);
    return w;
}

Vec2d Vec2d::perpedPos() const
{
    Vec2d w(*this);
    w.perpPos();
    return w;
}

Vec2d Vec2d::perpedNeg() const
{
    Vec2d w(*this);
    w.perpNeg();
    return w;
}

double Vec2d::dot(const Vec2d& v) const
{
    return x * v.x + y * v.y;
}

double Vec2d::cross(const Vec2d& v) const
{
    return x * v.y - y * v.x;
}

Vec2d Vec2d::pointwise(const Vec2d& v) const
{
    return Vec2d(x * v.x, y * v.y);
}

Vec2d Vec2d::fromPolar(double a, double d)
{
    return Vec2d(d, 0).rotated(a);
}

Vec2d operator+(const Vec2d& u)
{
    return u;
}

Vec2d operator-(const Vec2d& u)
{
    Vec2d w(u);
    w.negate();
    return w;
}

Vec2d operator+(const Vec2d& u, const Vec2d& v)
{
    Vec2d w(u);
    return w += v;
}

Vec2d operator-(const Vec2d& u, const Vec2d& v)
{
    Vec2d w(u);
    return w -= v;
}

Vec2d operator*(const Vec2d& u, double s)
{
    Vec2d w(u);
    return w *= s;
}

Vec2d operator*(double s, const Vec2d& u)
{
    return u * s;
}

Vec2d operator/(const Vec2d& u, double s)
{
    Vec2d w(u);
    return w /= s;
}

Vec2d& operator+=(Vec2d& u, const Vec2d& v)
{
    u.x += v.x;
    u.y += v.y;
    return u;
}

Vec2d& operator-=(Vec2d& u, const Vec2d& v)
{
    return u += -v;
}

Vec2d& operator*=(Vec2d& u, double s)
{
    u.x *= s;
    u.y *= s;
    return u;
}

Vec2d& operator/=(Vec2d& u, double s)
{
    return u *= 1 / s;
}

std::ostream& operator<<(std::ostream& out, const Vec2d& u)
{
    out << "[" << u.x << " " << u.y << "]";
    return out;
}
