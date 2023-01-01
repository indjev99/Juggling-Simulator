#pragma once

struct Vec2d
{
    Vec2d(double x, double y):
        x(x),
        y(y) {}

    Vec2d():
        Vec2d(0, 0) {}

    Vec2d(const Vec2d& other) = default;

    Vec2d& operator=(const Vec2d& other) = default;

    double length() const;

    void negate();
    void norm();
    void rotate(double a);
    void perpPos();
    void perpNeg();

    Vec2d normed() const;
    Vec2d rotated(double a) const;
    Vec2d perpedPos() const;
    Vec2d perpedNeg() const;

    static double dot(const Vec2d& u, const Vec2d& v);
    static double cross(const Vec2d& u, const Vec2d& v);

    static Vec2d fromAngle(double a);

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
