#pragma once

#include "Types.h"

template<typename T>
struct Vec2
{
	T X = 0, Y = 0;
	
	Vec2() = default;
	Vec2(const T& InX, const T& InY) :
	X(InX),
	Y(InY)
	{
		
	}
	Vec2(const Vec2& InVec2) :
	X(InVec2.X),
	Y(InVec2.Y)
	{
		
	}

	Vec2 operator + (const Vec2& InVecD) const
	{
		return VecD(X + InVecD.X, Y + InVecD.Y);
	}

	Vec2 operator - (const Vec2& InVec2) const
	{
		return Vec2(X - InVec2.X, Y - InVec2.Y);
	}

	Vec2 operator * (const Vec2& InVec2) const
	{
		return Vec2(X * InVec2.X, Y * InVec2.Y);
	}

	Vec2 operator * (const float& Value) const
	{
		return Vec2(X * Value, Y* Value);
	}

	Vec2 operator += (const Vec2& InVec2)
	{
		X += InVec2.X;
		Y += InVec2.Y;
		return *this;
	}

	Vec2 operator -= (const Vec2& InVec2)
	{
		X -= InVec2.X;
		Y -= InVec2.Y;
		return *this;
	}

	Vec2 operator *= (const Vec2& InVec2)
	{
		X *= InVec2.X;
		Y *= InVec2.Y;
		return *this;
	}

	bool operator == (const Vec2& Value) const
	{
		return X == Value.X && Y == Value.Y;
	}

	bool operator != (const Vec2& Value) const
	{
		return X != Value.X || Y != Value.Y;
	}

	friend std::ostream& operator << (std::ostream& Out, const Vec2& Value)
	{
		Out << Value.ToString();
		return Out;
	}

	std::string ToString() const
	{
		std::stringstream ss;
		ss << "(" << X << ", " << Y << ")";
		return ss.str();
	}

	float Size() const
	{
		return std::sqrt(X * X + Y * Y);
	}

	static float DotProduct(const Vec2& V1, const Vec2& V2)
	{
		return V1.X * V2.X + V1.Y * V2.Y;
	}

	static float CrossProduct(const Vec2& V1, const Vec2& V2)
	{
		return V1.X * V2.Y + V1.Y * V2.X;
	}

	static float Distance(const Vec2& V1, const Vec2& V2)
	{
		auto DiffX = V1.X - V2.X;
		auto DiffY = V1.Y - V2.Y;
		return std::sqrt(DiffX * DiffX + DiffY * DiffY);
	}
};

typedef Vec2<int32> Vec2i;
typedef Vec2<float> Vec2f;
