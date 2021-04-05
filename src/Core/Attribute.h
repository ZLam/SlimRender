#pragma once

#include "Vector.h"
#include "Color.h"

struct Attribute
{

};

struct BlinnAttribute : Attribute
{
	Vec4f Clip_InCoord;
	Vec4f Clip_OutCoord;
	Color Colour;
};
