#pragma once

#include "Matrix.h"
#include "Material.h"

struct Uniform
{
	Material* CurMaterial;
	Matrix4 MatModel;
	Matrix4 MatCameraVP;

	Uniform() = default;
	virtual ~Uniform()
	{
		if (CurMaterial)
		{
			delete CurMaterial;
			CurMaterial = nullptr;
		}
	}
};

struct BlinnUniform : Uniform
{
	BlinnUniform()
	{
		CurMaterial = new BlinnMaterial();
	}
	virtual ~BlinnUniform() = default;
};
