#pragma once

#include <vector>
#include "Matrix.h"
#include "Material.h"
#include "Light.h"

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
	/**
	 * 法线矩阵，其实就是处理就算物体怎么旋转或缩放后，面上的法线依然正确，垂直于该面
	 * https://learnopengl-cn.github.io/02%20Lighting/02%20Basic%20Lighting/ （注意，大部分的资源都会将法线矩阵定义为应用到模型-观察矩阵(Model-view Matrix)上的操作，但是由于我们只在世界空间中进行操作（不是在观察空间），我们只使用模型矩阵。）
	 */
	Matrix3 MatNormal;

	std::vector<Light> LightArr;

	Vec3f CameraPos;
	
	BlinnUniform()
	{
		CurMaterial = new BlinnMaterial();
	}
	virtual ~BlinnUniform() = default;
};
