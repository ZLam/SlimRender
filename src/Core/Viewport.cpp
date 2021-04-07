#include "Viewport.h"

Viewport::Viewport(const float& InWidth, const float& InHeight) :
Width(InWidth),
Height(InHeight)
{
	ViewportMat.Identity();
	ViewportMat.SetAllRow(
		Width * 0.5f, 0.0f, 0.0f, Width * 0.5f,
		0.0f, Height * 0.5f, 0.0f, Height * 0.5f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	
	
	/**
	 * GAMES101的Viewport矩阵
	 */
	// @TODO 下面加减0.1f有咩用
	// float f1 = (100.0f - 0.1f) / 2.0f;
	// float f2 = (100.0f + 0.1f) / 2.0f;
	// Matrix4 ScaleMat;
	// Matrix4 MoveMat;
	// ScaleMat.Scale(Width * 0.5f, Height * 0.5f, f1);
	// MoveMat.Translate(Width * 0.5f, Height * 0.5f, f2);
	// ViewportMat = MoveMat * ScaleMat;
}
