#pragma once

#include "Vector.h"
#include "Matrix.h"

class Camera
{
private:
	Matrix4 ViewMat;
	Matrix4 ProjMat;
	
public:
	Camera();

	const Matrix4& GetViewMat()
	{
		return ViewMat;
	}

	const Matrix4& GetProjMat()
	{
		return ProjMat;
	}
};
