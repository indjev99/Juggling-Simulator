#include "vec2d.h"

struct Move
{
    enum Type
    {
        Catch,
        Throw
    };

    Move(Type type, double t):
        type(type),
        t(t) {}

    Type type;

    double t;
    Vec2d pos;
    Vec2d vel;
};
