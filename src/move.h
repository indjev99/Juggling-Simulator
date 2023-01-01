#include "vec2d.h"

struct Move
{
    enum Type
    {
        Catch,
        Throw
    };

    Move(Type type, double t, const Vec2d& pos, const Vec2d& vel):
        type(type),
        t(t),
        pos(pos),
        vel(vel) {}

    Move(Type type, double t, const Vec2d& pos):
        Move(type, t, pos, Vec2d()) {}

    Move(Type type, double t):
        Move(type, t, Vec2d(), Vec2d()) {}

    Type type;

    double t;
    Vec2d pos;
    Vec2d vel;
};
