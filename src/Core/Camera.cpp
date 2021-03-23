#include "Camera.h"
#include "Math.h"

Camera::Camera(const Vec3f& InSelfPos, const Vec3f& InTargetPos, const Vec3f& InWorldUp)
{
    LookAt(InSelfPos, InTargetPos, InWorldUp);
    

	/**
	 * GAMES101使用的View矩阵和Projection矩阵形式
	 */
	// const Vec3f Eye(0.0f, 0.0f, 5.0f);
	// Matrix4 EyeTranslate;
	// EyeTranslate.Translate(-Eye);
	// ViewMat.Identity();
	// ViewMat = EyeTranslate * ViewMat;
	//
	// float Near = 0.1f;
	// float Far = 50.0f;
	// float FovY = 45.0f;
	// float Aspect = 1.0f;
	// Matrix4 Persp2Ortho;
	// Persp2Ortho.SetAllRow(
	// 	Near, 0.0f, 0.0f, 0.0f,
	// 	0.0f, Near, 0.0f, 0.0f,
	// 	0.0f, 0.0f, Near + Far, -Near * Far,
	// 	0.0f, 0.0f, 1.0f, 0.0f
	// );
	// Matrix4 Ortho;
	// float Top = std::tan(FovY / 2.0f) * std::abs(Near);
	// float Bottom = -Top;
	// float Right = Aspect * Top;
	// float Left = -Right;
	// Ortho.SetAllRow(
	// 	2.0f / (Right - Left), 0.0f, 0.0f, -(Left + Right) / 2.0f,
	// 	0.0f, 2.0f / (Top - Bottom), 0.0f, -(Bottom + Top) / 2.0f,
	// 	0.0f, 0.0f, 2.0f / (Near - Far), -(Near + Far) / 2.0f,
	// 	0.0f, 0.0f, 0.0f, 1.0f
	// );
	// ProjMat = Ortho * Persp2Ortho;
}

void Camera::LookAt(const Vec3f& InSelfPos, const Vec3f& InTargetPos, const Vec3f& InWorldUp)
{
    SelfPos = InSelfPos;
    TargetPos = InTargetPos;
    WorldUp = InWorldUp;
    Forward = (SelfPos - TargetPos).GetNormal();
    Right = Vec3f::CrossProduct(WorldUp, Forward).GetNormal();
    Up = Vec3f::CrossProduct(Forward, Right);
    ViewMat.Identity();
    ViewMat.SetAllRow(
		Right.X, Right.Y, Right.Z, -SelfPos.X,
		Up.X, Up.Y, Up.Z, -SelfPos.Y,
		Forward.X, Forward.Y, Forward.Z, -SelfPos.Z,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void Camera::SetupProjection(const float& InFovY, const float& InAspect, const float& InNear, const float& InFar)
{
	FovY = InFovY;
	Aspect = InAspect;
	Near = InNear;
	Far = InFar;
	ProjMat.Identity();
	ProjMat.SetAllRow(
		1.0f / (Aspect * std::tan(FovY / 2.0f)), 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / std::tan(FovY / 2.0f), 0.0f, 0.0f,
		0.0f, 0.0f, (Near + Far) / (Near - Far), 2 * Near * Far / (Near - Far),
		0.0f, 0.0f, -1.0f, 0.0f
	);
}
