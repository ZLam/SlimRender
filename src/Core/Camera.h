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

	float FovY		= 0.0f;
	float Aspect	= 0.0f;
	float Near		= 0.0f;
	float Far		= 0.0f;
	
public:
	Camera(const Vec3f& InSelfPos, const Vec3f& InTargetPos, const Vec3f& InWorldUp = Vec3f::Up);

	Matrix4 GetViewMat()
	{
		return ViewMat;
	}

	Matrix4 GetProjMat()
	{
		return ProjMat;
	}
    
    void LookAt(const Vec3f& InSelfPos, const Vec3f& InTargetPos, const Vec3f& InWorldUp = Vec3f::Up);

	void SetupProjection(const float& InFovY, const float& InAspect, const float& InNear, const float& InFar);

	Vec3f GetPosition() const
	{
		return SelfPos;
	}
};
