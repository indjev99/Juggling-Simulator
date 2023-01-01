#pragma once

#include <ostream>

struct Vec2d
{
    Vec2d(double x, double y):
        x(x),
        y(y) {}

    Vec2d():
        Vec2d(0, 0) {}

    double lengthSq() const;
    double length() const;
    double sum() const;

    void negate();
    void norm();
    void rotate(double a);
    void perpPos();
    void perpNeg();

    template <class F>
    void apply(F f);

    Vec2d normed() const;
    Vec2d rotated(double a) const;
    Vec2d perpedPos() const;
    Vec2d perpedNeg() const;

    template <class F>
    Vec2d applied(F f) const;

    double dot(const Vec2d& v) const;
    double cross(const Vec2d& v) const;
    Vec2d pointwise(const Vec2d& v) const;

    static Vec2d fromPolar(double a, double d);

    double x, y;
};

Vec2d operator+(const Vec2d& u);
Vec2d operator-(const Vec2d& u);
Vec2d operator+(const Vec2d& u, const Vec2d& v);
Vec2d operator-(const Vec2d& u, const Vec2d& v);
Vec2d operator*(const Vec2d& u, double s);
Vec2d operator*(double s, const Vec2d& u);
Vec2d operator/(const Vec2d& u, double s);
Vec2d& operator+=(Vec2d& u, const Vec2d& v);
Vec2d& operator-=(Vec2d& u, const Vec2d& v);
Vec2d& operator*=(Vec2d& u, double s);
Vec2d& operator/=(Vec2d& u, double s);

std::ostream& operator<<(std::ostream& out, const Vec2d& u);

template <class F>
void Vec2d::apply(F f)
{
    x = f(x);
    y = f(y);
}

template <class F>
Vec2d Vec2d::applied(F f) const
{
    Vec2d w(*this);
    w.apply(f);
    return w;
}
