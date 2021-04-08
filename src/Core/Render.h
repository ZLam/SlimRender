#pragma once

#include "Types.h"
#include "Color.h"
#include "Vector.h"
#include "Vertex.h"
#include "BoundingBox.h"
#include "ShaderProgram.h"
#include "Viewport.h"

#define IS_WIREFRAME_MODE 0

class Render
{
private:
	int32 Width;
	int32 Height;
	uint32* ColorBuffer;
	int32 ColorBufferSize;
	float* DepthBuffer;
	Viewport* CurViewport;

public:
	Render(const int32& InWidth, const int32& InHeight);
	~Render();
	Render(const Render&) = delete;
	Render(Render&&) = delete;

	int32 GetWidth() const { return Width; }
	int32 GetHeight() const { return Height; }
	uint32* GetColorBuffer() const { return ColorBuffer; }
	int32 GetColorBufferSize() const { return ColorBufferSize; }

	void CleanColorBuffer();
	void CleanDepthBuffer();

	void DrawPixel(const int32& InX, const int32& InY, const Color& InColor = Color::White);
	void DrawLine(int32 InX1, int32 InY1, int32 InX2, int32 InY2, const Color& InColor = Color::White);
	void DrawTriangle_OldSchool(Vec2i V1, Vec2i V2, Vec2i V3, const Color& InColor = Color::White);
	void DrawTriangle(Vertex** VertexArr, ShaderProgram* InShaderProgram);

	void GetTriangleAABB(const Vec4f& A, const Vec4f& B, const Vec4f& C, BoundingBox& InBoundingBox);
	Vec3f GetBarycentric2D(const Vec2f& A, const Vec2f& B, const Vec2f& C, const Vec2f& P);
	void GetBarycentric2D(const float& XA, const float& YA, const float& XB, const float& YB, const float& XC, const float& YC,
		const float& XP, const float& YP, float& Alpha, float& Beta, float& Gamma);
	bool IsCull(Vec4f InNDC_Coord[3]);
};
