#pragma once

#include <cstdint>
#include <sstream>

typedef int8_t		int8;
typedef int16_t		int16;
typedef int32_t		int32;
typedef int64_t		int64;
typedef uint8_t		uint8;
typedef uint16_t	uint16;
typedef uint32_t	uint32;
typedef uint64_t	uint64;

struct Color
{
	float R;
	float G;
	float B;
	float A;
	uint8 R8;
	uint8 G8;
	uint8 B8;
	uint8 A8;

	static Color White;
	static Color Black;
	static Color Red;
	static Color Green;
	static Color Blue;

	Color(float InR, float InG, float InB, float InA = 1.0f) :
	R(InR),
	G(InG),
	B(InB),
	A(InA)
	{
		R8 = static_cast<uint8>(R * 255.0f);
		G8 = static_cast<uint8>(G * 255.0f);
		B8 = static_cast<uint8>(B * 255.0f);
		A8 = static_cast<uint8>(A * 255.0f);
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

	uint32 GetRGBA32() const
	{
		return R8 << 24 | G8 << 16 | B8 << 8 | A8;
	}

	uint32 GetARGB32() const
	{
		return A8 << 24 | R8 << 16 | G8 << 8 | B8;
	}

	std::string ToString() const
	{
		std::stringstream ss;
		ss << "(" << R << ", " << G << ", " << B << ")";
		return ss.str();
	}

	static Color RandomColor();

	friend std::ostream& operator << (std::ostream& Out, const Color& InColor)
	{
		Out << InColor.ToString();
		return Out;
	}
};
