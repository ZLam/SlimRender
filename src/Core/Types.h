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
	float r;
	float g;
	float b;
	float a;
	uint8 r8;
	uint8 g8;
	uint8 b8;
	uint8 a8;

	static Color White;
	static Color Black;
	static Color Red;
	static Color Green;
	static Color Blue;

	Color(float InR, float InG, float InB, float InA = 1.0f) :
	r(InR),
	g(InG),
	b(InB),
	a(InA)
	{
		r8 = static_cast<uint8>(r * 255.0f);
		g8 = static_cast<uint8>(g * 255.0f);
		b8 = static_cast<uint8>(b * 255.0f);
		a8 = static_cast<uint8>(a * 255.0f);
	}

	Color(const Color& InColor) :
	r(InColor.r),
	g(InColor.g),
	b(InColor.b),
	a(InColor.a),
	r8(InColor.r8),
	g8(InColor.g8),
	b8(InColor.b8),
	a8(InColor.a8)
	{
		
	}

	uint32 GetRGBA32() const
	{
		return r8 << 24 | g8 << 16 | b8 << 8 | a8;
	}

	uint32 GetARGB32() const
	{
		return a8 << 24 | r8 << 16 | g8 << 8 | b8;
	}

	std::string ToString() const
	{
		std::stringstream ss;
		ss << "(" << r << ", " << g << ", " << b << ")";
		return ss.str();
	}

	static Color RandomColor();

	friend std::ostream& operator << (std::ostream& Out, const Color& InColor)
	{
		Out << InColor.ToString();
		return Out;
	}
};
