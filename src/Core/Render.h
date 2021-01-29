#pragma once

#include "Types.h"
#include "Vector.h"

class Render
{
private:
	uint32 Width;
	uint32 Height;
	uint32* ColorBuffer;
	uint32 ColorBufferSize;

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

	void DrawPixel(const uint32& InX, const uint32& InY, const Color& InColor);
	void DrawLine(int32 InX1, int32 InY1, int32 InX2, int32 InY2, const Color& InColor);
	void DrawTriangle_OldSchool(Vec2i V1, Vec2i V2, Vec2i V3);
};
