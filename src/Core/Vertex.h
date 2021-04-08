#pragma once

#include "Vector.h"
#include "Color.h"

struct Vertex
{
	//顶点属性
	Vec3f Position;
	Color Colour;
	Vec2f UV;

	Vertex(const Vec3f& InPosition) :
	Position(InPosition)
	{
		
	}

	Vertex(const Vec3f& InPosition, const Color& InColor):
	Position(InPosition),
	Colour(InColor)
	{
		
	}

	Vertex(const Vec3f& InPosition, const Color& InColor, const Vec2f& InUV) :
	Position(InPosition),
	Colour(InColor),
	UV(InUV)
	{
		
	}
};
