#pragma once

#include <sstream>

#include "Types.h"
#include "Math.h"

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

	void Set(const T& InX, const T& InY)
	{
		X = InX;
		Y = InY;
	}

	Vec2 operator - () const
	{
		return Vec2(-X, -Y);
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

	Vec2 operator *= (const T& Value)
	{
		X *= Value;
		Y *= Value;
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

	void Set(const float& InX, const float& InY, const float& InZ)
	{
		X = InX;
		Y = InY;
		Z = InZ;
	}

	Vec3f operator - () const
	{
		return Vec3f(-X, -Y, -Z);
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

	Vec3f operator *= (const float& Value)
	{
		X *= Value;
		Y *= Value;
		Z *= Value;
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
		Z /= Length;
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

struct Vec4f
{
	float X = 0;
	float Y = 0;
	float Z = 0;
	float W = 1;

	Vec4f() = default;
	Vec4f(const float& InX, const float& InY, const float& InZ,const float& InW = 1.0f) :
	X(InX),
	Y(InY),
	Z(InZ),
	W(InW)
	{

	}
	Vec4f(const Vec3f& Value, const float& InW = 1.0f) :
	X(Value.X),
	Y(Value.Y),
	Z(Value.Z),
	W(InW)
	{
		
	}
	Vec4f(const Vec4f& Value) :
	X(Value.X),
	Y(Value.Y),
	Z(Value.Z),
	W(Value.W)
	{

	}

	void Set(const float& InX, const float& InY, const float& InZ, const float& InW)
	{
		X = InX;
		Y = InY;
		Z = InY;
		W = InW;
	}

	Vec4f operator - () const
	{
		return Vec4f(-X, -Y, -Z, -W);
	}

	Vec4f operator + (const Vec4f& Value) const
	{
		return Vec4f(X + Value.X, Y + Value.Y, Z + Value.Z, W + Value.W);
	}

	Vec4f operator - (const Vec4f& Value) const
	{
		return Vec4f(X - Value.X, Y - Value.Y, Z + Value.Z, W - Value.W);
	}

	Vec4f operator * (const Vec4f& Value) const
	{
		return Vec4f(X * Value.X, Y * Value.Y, Z * Value.Z, W * Value.W);
	}

	Vec4f operator * (const float& Value) const
	{
		return Vec4f(X * Value, Y* Value, Z * Value, W * Value);
	}

	Vec4f operator += (const Vec4f& Value)
	{
		X += Value.X;
		Y += Value.Y;
		Z += Value.Z;
		W += Value.W;
		return *this;
	}

	Vec4f operator -= (const Vec4f& Value)
	{
		X -= Value.X;
		Y -= Value.Y;
		Z -= Value.Z;
		W -= Value.W;
		return *this;
	}

	Vec4f operator *= (const Vec4f& Value)
	{
		X *= Value.X;
		Y *= Value.Y;
		Z *= Value.Z;
		W *= Value.W;
		return *this;
	}

	Vec4f operator *= (const float& Value)
	{
		X *= Value;
		Y *= Value;
		Z *= Value;
		W *= Value;
		return *this;
	}

	bool operator == (const Vec4f& Value) const
	{
		return X == Value.X && Y == Value.Y && Z == Value.Z && W == Value.W;
	}

	bool operator != (const Vec4f& Value) const
	{
		return X != Value.X || Y != Value.Y || Z != Value.Z || W != Value.W;
	}

	friend std::ostream& operator << (std::ostream& Out, const Vec4f& Value)
	{
		Out << Value.ToString();
		return Out;
	}

	std::string ToString() const
	{
		std::stringstream ss;
		ss << "(" << X << ", " << Y << ", " << Z << ", " << W << ")";
		return ss.str();
	}

	float Size() const
	{
		return std::sqrt(X * X + Y * Y + Z * Z + W * W);
	}

	float SizeSquared() const
	{
		return X * X + Y * Y + Z * Z + W * W;
	}

	void Normalize()
	{
		const float Length = X * X + Y * Y + Z * Z;
		X /= Length;
		Y /= Length;
		Z /= Length;
		W = 0.0f;
	}

	Vec4f GetNormal() const
	{
		const float Length = X * X + Y * Y + Z * Z;
		return Vec4f(X / Length, Y / Length, Z / Length, 0.0f);
	}

	static float Dot3(const Vec4f& V1, const Vec4f& V2)
	{
		return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
	}

	static float Dot4(const Vec4f& V1, const Vec4f& V2)
	{
		return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z + V1.W * V2.W;
	}

	static Vec4f CrossProduct(const Vec4f& V1, const Vec4f& V2)
	{
		return Vec4f(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X, 0.0f);
	}
};
