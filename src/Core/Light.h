#pragma once

#include "Vector.h"

struct Light
{
	Vec3f Position;

	Vec3f Ambient;
	Vec3f Diffuse;
	Vec3f Specular;

	Light(const Vec3f& InPosition, const Vec3f& InAmbient, const Vec3f& InDiffuse, const Vec3f& InSpecular) :
	Position(InPosition),
	Ambient(InAmbient),
	Diffuse(InDiffuse),
	Specular(InSpecular)
	{
		
	}
};
