#pragma once

#include "Vector.h"
#include "Color.h"

struct Vertex
{
	//顶点属性
	Vec3f Position;
	Color Colour;
	Vec2f UV;
	Vec3f Normal;

	Vertex(const Vec3f& InPosition) :
	Position(InPosition)
	{
		
	}
    
    Vertex(const Vec3f& InPosition, const Vec2f& InUV) :
    Position(InPosition),
    UV(InUV)
    {
        
    }

	Vertex(const Vec3f& InPosition, const Color& InColor):
	Position(InPosition),
	Colour(InColor)
	{
		
	}

	Vertex(const Vec3f& InPosition, const Vec3f& InNormal) :
	Position(InPosition),
	Normal(InNormal)
	{

	}

	Vertex(const Vec3f& InPosition, const Color& InColor, const Vec2f& InUV) :
	Position(InPosition),
	Colour(InColor),
	UV(InUV)
	{

	}

	Vertex(const Vec3f& InPosition, const Color& InColor, const Vec2f& InUV, const Vec3f& InNormal) :
	Position(InPosition),
	Colour(InColor),
	UV(InUV),
	Normal(InNormal)
	{
		
	}
};
