#pragma once

#include "Matrix.h"

struct Material;

struct Uniform
{
	Material* CurMaterial;
	Matrix4 MatModel;
	Matrix4 MatCameraVP;

	Uniform() = default;
	virtual ~Uniform();
};

struct BlinnUniform : Uniform
{
	BlinnUniform();
	virtual ~BlinnUniform() = default;
};
