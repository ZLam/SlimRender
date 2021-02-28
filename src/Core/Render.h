#pragma once

#include "Types.h"
#include "Color.h"
#include "Vector.h"

class Render
{
private:
	uint32 Width;
	uint32 Height;
	uint32* ColorBuffer;
	uint32 ColorBufferSize;
	float* DepthBuffer;

public:
	Render(const uint32& InWidth, const uint32& InHeight);
	~Render();
	Render(const Render&) = delete;
	Render(Render&&) = delete;

	uint32 GetWidth() const { return Width; }
	uint32 GetHeight() const { return Height; }
	uint32* GetColorBuffer() const { return ColorBuffer; }
	uint32 GetColorBufferSize() const { return ColorBufferSize; }

	void CleanColorBuffer();
	void CleanDepthBuffer();

	void DrawPixel(const int32& InX, const int32& InY, const Color& InColor = Color::White);
	void DrawLine(int32 InX1, int32 InY1, int32 InX2, int32 InY2, const Color& InColor = Color::White);
	void DrawTriangle_OldSchool(Vec2i V1, Vec2i V2, Vec2i V3, const Color& InColor = Color::White);
	void DrawTriangle(const Vec3f& V1, const Vec3f& V2, const Vec3f& V3);

	void GetTriangleAABB(const Vec3f& A, const Vec3f& B, const Vec3f& C, Vec2f& BoxMin, Vec2f& BoxMax);
	Vec3f GetBarycentric2D(const Vec2f& A, const Vec2f& B, const Vec2f& C, const Vec2f& P);
	void GetBarycentric2D(const float& XA, const float& YA, const float& XB, const float& YB, const float& XC, const float& YC,
		const float& XP, const float& YP, float& Alpha, float& Beta, float& Gamma);
};
