#pragma once

#include "Vector.h"
#include "Color.h"

struct Attribute
{
	Vec4f Clip_InCoord;
	Vec4f Clip_OutCoord;
};

struct BlinnAttribute : Attribute
{
	Color Colour;
	Vec2f UV;
	Vec3f Normal;
	Vec3f WorldPos;
};
