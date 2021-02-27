#include "Camera.h"
#include "Math.h"

Camera::Camera()
{
	//@TODO 目前写死镜头
	
	const Vec3f Eye(0.0f, 0.0f, 5.0f);
	Matrix4 EyeTranslate;
	EyeTranslate.Translate(-Eye);
	ViewMat = EyeTranslate * ViewMat;

	float Near = 0.1f;
	float Far = 50.0f;
	float FovY = 45.0f;
	float Aspect = 1.0f;
	Matrix4 Persp2Ortho;
	Persp2Ortho.SetAllRow(
		Near, 0.0f, 0.0f, 0.0f,
		0.0f, Near, 0.0f, 0.0f,
		0.0f, 0.0f, Near + Far, -Near * Far,
		0.0f, 0.0f, 1.0f, 0.0f
	);
	Matrix4 Ortho;
	float Top = std::tan(FovY / 2.0f) * std::abs(Near);
	float Bottom = -Top;
	float Right = Aspect * Top;
	float Left = -Right;
	Ortho.SetAllRow(
		2.0f / (Right - Left), 0.0f, 0.0f, -(Left + Right) / 2.0f,
		0.0f, 2.0f / (Top - Bottom), 0.0f, -(Bottom + Top) / 2.0f,
		0.0f, 0.0f, 2.0f / (Near - Far), -(Near + Far) / 2.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	ProjMat = Ortho * Persp2Ortho;
}
