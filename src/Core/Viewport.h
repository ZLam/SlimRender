#pragma once

#include "Matrix.h"

class Viewport
{
private:
	float Width;
	float Height;
	Matrix4 ViewportMat;

public:
	Viewport(const float& InWidth, const float& InHeight);

	const Matrix4& GetViewportMat()
	{
		return ViewportMat;
	}
};
