#pragma once

#include "Vector.h"
#include "Color.h"

struct VSOutput
{
	Vec3f Clip_Coord;
	Vec3f NDC_Coord;
	Vec3f Screen_Coord;
};

struct Vertex
{
	//顶点属性
	Vec3f Position;
	Color Colour = Color::White;

	//vertex shader输出
	VSOutput VSOutputData;

	Vertex(const Vec3f& InPosition) :
	Position(InPosition)
	{
		
	}

	Vertex(const Vec3f& InPosition, const Color& InColor):
	Position(InPosition),
	Colour(InColor)
	{
	}
};
