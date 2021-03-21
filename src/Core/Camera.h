#pragma once

#include "Vector.h"
#include "Matrix.h"

class Camera
{
private:
	Matrix4 ViewMat;
	Matrix4 ProjMat;
    Vec3f SelfPos;
    Vec3f TargetPos;
    Vec3f WorldUp;
    Vec3f Forward;
    Vec3f Right;
    Vec3f Up;
	
public:
	Camera(const Vec3f& InSelfPos, const Vec3f& InTargetPos, const Vec3f& InWorldUp = Vec3f::Up);

	const Matrix4& GetViewMat()
	{
		return ViewMat;
	}

	const Matrix4& GetProjMat()
	{
		return ProjMat;
	}
    
    void LookAt(const Vec3f& InSelfPos, const Vec3f& InTargetPos, const Vec3f& InWorldUp = Vec3f::Up);
};
