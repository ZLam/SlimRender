#include "Viewport.h"

Viewport::Viewport(const float& InWidth, const float& InHeight) :
Width(InWidth),
Height(InHeight)
{
	//@TODO 为什么这样处理z坐标
	float f1 = (100.0f - 0.1f) / 2.0f;
	float f2 = (100.0f + 0.1f) / 2.0f;
	Matrix4 ScaleMat;
	Matrix4 MoveMat;
	ScaleMat.Scale(Width * 0.5f, Height * 0.5f, f1);
	MoveMat.Translate(Width * 0.5f, Height * 0.5f, f2);
	ViewportMat = MoveMat * ScaleMat;
}
