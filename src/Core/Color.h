#pragma once

#include <sstream>
#include "Types.h"
#include "Math.h"

struct Color
{
	float R = 1.0f;
	float G = 1.0f;
	float B = 1.0f;
	float A = 1.0f;
	uint8 R8 = 255;
	uint8 G8 = 255;
	uint8 B8 = 255;
	uint8 A8 = 255;

	static Color White;
	static Color Black;
	static Color Red;
	static Color Green;
	static Color Blue;

	Color()
	{
		_setupR8G8B8A8();
	}

	Color(const float& InR, const float& InG, const float& InB, const float& InA = 1.0f) :
	R(InR),
	G(InG),
	B(InB),
	A(InA)
	{
		_setupR8G8B8A8();
	}

	Color(const uint8& InR, const uint8& InG, const uint8& InB, const uint8& InA = 255):
	R8(InR),
	G8(InG),
	B8(InB),
	A8(InA)
	{
		_setupRGBA();
	}

	Color(const Color& InColor) :
	R(InColor.R),
	G(InColor.G),
	B(InColor.B),
	A(InColor.A),
	R8(InColor.R8),
	G8(InColor.G8),
	B8(InColor.B8),
	A8(InColor.A8)
	{

	}

	void _setupR8G8B8A8()
	{
		R8 = (uint8)(R * 255.0f);
		G8 = (uint8)(G * 255.0f);
		B8 = (uint8)(B * 255.0f);
		A8 = (uint8)(A * 255.0f);
	}

	void _setupRGBA()
	{
		R = ((float)R8) / 255.0f;
		G = ((float)G8) / 255.0f;
		B = ((float)B8) / 255.0f;
		A = ((float)A8) / 255.0f;
	}

	uint32 GetRGBA32() const
	{
		return R8 << 24 | G8 << 16 | B8 << 8 | A8;
	}

	uint32 GetARGB32() const
	{
		return A8 << 24 | R8 << 16 | G8 << 8 | B8;
	}

	Color operator + (const Color& Value) const
	{
		return Color(
			std::min(R + Value.R, 1.0f),
			std::min(G + Value.G, 1.0f),
			std::min(B + Value.B, 1.0f),
			std::min(A + Value.A, 1.0f)
		);
	}

	Color& operator += (const Color& Value)
	{
		R = std::min(R + Value.R, 1.0f);
		G = std::min(G + Value.G, 1.0f);
		B = std::min(B + Value.B, 1.0f);
		A = std::min(A + Value.A, 1.0f);
		_setupR8G8B8A8();
		return *this;
	}

	Color operator * (const float& Value) const
	{
		return Color(
			std::min(R * Value, 1.0f),
			std::min(G * Value, 1.0f),
			std::min(B * Value, 1.0f),
			std::min(A * Value, 1.0f)
		);
	}

	Color& operator *= (const float& Value)
	{
		R = std::min(R * Value, 1.0f);
		G = std::min(G * Value, 1.0f);
		B = std::min(B * Value, 1.0f);
		A = std::min(A * Value, 1.0f);
		_setupR8G8B8A8();
		return *this;
	}

	std::string ToString() const
	{
		std::stringstream ss;
		ss << "(" << R << ", " << G << ", " << B << ", " << A << ")";
		return ss.str();
	}

	static Color RandomColor();

	friend std::ostream& operator << (std::ostream& Out, const Color& InColor)
	{
		Out << InColor.ToString();
		return Out;
	}
};
