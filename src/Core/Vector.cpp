#include "Vector.h"

Vec3f Vec3f::Up = Vec3f(0.0f, 1.0f, 0.0f);

Vec3f::Vec3f(const Vec4f& Value) :
X(Value.X),
Y(Value.Y),
Z(Value.Z)
{

}
