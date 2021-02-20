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

	Vec2 operator + (const Vec2& InVec2) const
	{
		return Vec2(X + InVec2.X, Y + InVec2.Y);
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

	float SizeSquared() const
	{
		return X * X + Y * Y;
	}

	void Normalize()
	{
		const float Length = Size();
		X /= Length;
		Y /= Length;
	}

	Vec2 GetNormal() const
	{
		const float Length = Size();
		return Vec2(X / Length, Y / Length);
	}

	static float DotProduct(const Vec2& V1, const Vec2& V2)
	{
		return V1.X * V2.X + V1.Y * V2.Y;
	}

	static float CrossProduct(const Vec2& V1, const Vec2& V2)
	{
		return V1.X * V2.Y - V1.Y * V2.X;
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

struct Vec3f
{
	float X = 0;
	float Y = 0;
	float Z = 0;

	Vec3f() = default;
	Vec3f(const float& InX, const float& InY, const float& InZ) :
	X(InX),
	Y(InY),
	Z(InZ)
	{
		
	}
	Vec3f(const Vec3f& Value) :
	X(Value.X),
	Y(Value.Y),
	Z(Value.Z)
	{

	}

	Vec3f operator + (const Vec3f& Value) const
	{
		return Vec3f(X + Value.X, Y + Value.Y, Z + Value.Z);
	}

	Vec3f operator - (const Vec3f& Value) const
	{
		return Vec3f(X - Value.X, Y - Value.Y, Z + Value.Z);
	}

	Vec3f operator * (const Vec3f& Value) const
	{
		return Vec3f(X * Value.X, Y * Value.Y, Z * Value.Z);
	}

	Vec3f operator * (const float& Value) const
	{
		return Vec3f(X * Value, Y* Value, Z * Value);
	}

	Vec3f operator += (const Vec3f& Value)
	{
		X += Value.X;
		Y += Value.Y;
		Z += Value.Z;
		return *this;
	}

	Vec3f operator -= (const Vec3f& Value)
	{
		X -= Value.X;
		Y -= Value.Y;
		Z -= Value.Z;
		return *this;
	}

	Vec3f operator *= (const Vec3f& Value)
	{
		X *= Value.X;
		Y *= Value.Y;
		Z *= Value.Z;
		return *this;
	}

	bool operator == (const Vec3f& Value) const
	{
		return X == Value.X && Y == Value.Y && Z == Value.Z;
	}

	bool operator != (const Vec3f& Value) const
	{
		return X != Value.X || Y != Value.Y || Z != Value.Z;
	}

	friend std::ostream& operator << (std::ostream& Out, const Vec3f& Value)
	{
		Out << Value.ToString();
		return Out;
	}

	std::string ToString() const
	{
		std::stringstream ss;
		ss << "(" << X << ", " << Y << ", " << Z << ")";
		return ss.str();
	}

	float Size() const
	{
		return std::sqrt(X * X + Y * Y + Z * Z);
	}

	float SizeSquared() const
	{
		return X * X + Y * Y + Z * Z;
	}

	void Normalize()
	{
		const float Length = Size();
		X /= Length;
		Y /= Length;
	}

	Vec3f GetNormal() const
	{
		const float Length = Size();
		return Vec3f(X / Length, Y / Length, Z / Length);
	}

	static float DotProduct(const Vec3f& V1, const Vec3f& V2)
	{
		return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
	}

	static Vec3f CrossProduct(const Vec3f& V1, const Vec3f& V2)
	{
		return Vec3f(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
	}

	static float Distance(const Vec3f& V1, const Vec3f& V2)
	{
		auto DiffX = V1.X - V2.X;
		auto DiffY = V1.Y - V2.Y;
		auto DiffZ = V1.Z - V2.Z;
		return std::sqrt(DiffX * DiffX + DiffY * DiffY + DiffZ * DiffZ);
	}
};
