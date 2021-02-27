///////////////////////////////////////////////////////////////////////////////
// Matrice.h
// =========
// NxN Matrix Math classes
//
// The elements of the matrix are stored as column major order.
// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
//            | 2 5 8 |    |  2  6 10 14 |
//                         |  3  7 11 15 |
//
// Dependencies: Vector2, Vector3, Vector3
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2005-06-24
// UPDATED: 2020-03-26
//
// Copyright (C) 2005 Song Ho Ahn
///////////////////////////////////////////////////////////////////////////////

#ifndef MATH_MATRICES_H
#define MATH_MATRICES_H

#include <iostream>
#include <iomanip>
#include "Vector.h"

///////////////////////////////////////////////////////////////////////////
// 2x2 matrix
///////////////////////////////////////////////////////////////////////////
struct Matrix2
{
	// constructors
	Matrix2();  // init with identity
	Matrix2(const float src[4]);
	Matrix2(float m0, float m1, float m2, float m3);

	void        Set(const float src[4]);
	void        Set(float m0, float m1, float m2, float m3);
	void        SetAllRow(float m00, float m01,	// 1st row
						float m10, float m11);	// 2nd row
	void        SetRow(int index, const float row[2]);
	void        SetRow(int index, const Vec2f& v);
	void        SetColumn(int index, const float col[2]);
	void        SetColumn(int index, const Vec2f& v);

	const float* Get() const;
	const float* GetTranspose();
	Vec2f		GetRow(int index) const;
	Vec2f		GetColumn(int index) const;
	float       GetDeterminant() const;
	float       GetAngle() const;                       // retrieve angle (degree) from matrix

	Matrix2&    Identity();
	Matrix2&    Transpose();                            // transpose itself and return reference
	Matrix2&    Invert();

	// operators
	Matrix2     operator+(const Matrix2& rhs) const;    // add rhs
	Matrix2     operator-(const Matrix2& rhs) const;    // subtract rhs
	Matrix2&    operator+=(const Matrix2& rhs);         // add rhs and update this object
	Matrix2&    operator-=(const Matrix2& rhs);         // subtract rhs and update this object
	Vec2f		operator*(const Vec2f& rhs) const;		// multiplication: v' = M * v
	Matrix2     operator*(const Matrix2& rhs) const;    // multiplication: M3 = M1 * M2
	Matrix2&    operator*=(const Matrix2& rhs);         // multiplication: M1' = M1 * M2
	bool        operator==(const Matrix2& rhs) const;   // exact compare, no epsilon
	bool        operator!=(const Matrix2& rhs) const;   // exact compare, no epsilon
	float       operator[](int index) const;            // subscript operator v[0], v[1]
	float&      operator[](int index);                  // subscript operator v[0], v[1]

	// friends functions
	friend Matrix2 operator-(const Matrix2& m);                     // unary operator (-)
	friend Matrix2 operator*(float scalar, const Matrix2& m);       // pre-multiplication
	friend Vec2f operator*(const Vec2f& vec, const Matrix2& m); // pre-multiplication
	friend std::ostream& operator<<(std::ostream& os, const Matrix2& m);
	


	float m[4];
	float tm[4];
};



///////////////////////////////////////////////////////////////////////////
// 3x3 matrix
///////////////////////////////////////////////////////////////////////////
struct Matrix3
{
	// constructors
	Matrix3();  // init with identity
	Matrix3(const float src[9]);
	Matrix3(float m0, float m1, float m2,           // 1st column
			float m3, float m4, float m5,           // 2nd column
			float m6, float m7, float m8);          // 3rd column

	void        Set(const float src[9]);
	void        Set(float m0, float m1, float m2,   // 1st column
					float m3, float m4, float m5,   // 2nd column
					float m6, float m7, float m8);  // 3rd column
	void        SetAllRow(float m00, float m01, float m02,	// 1st row
						float m10, float m11, float m12,	// 2nd row
						float m20, float m21, float m22);	// 3rd row
	void        SetRow(int index, const float row[3]);
	void        SetRow(int index, const Vec3f& v);
	void        SetColumn(int index, const float col[3]);
	void        SetColumn(int index, const Vec3f& v);

	const float* Get() const;
	const float* GetTranspose();
	Vec3f	     GetRow(int index) const;
	Vec3f		GetColumn(int index) const;
	float       GetDeterminant() const;
	Vec3f		GetAngle() const;                       // return (pitch, yaw, roll) in degree
	Matrix3&    Identity();
	Matrix3&    Transpose();                            // transpose itself and return reference
	Matrix3&    Invert();

	// operators
	Matrix3     operator+(const Matrix3& rhs) const;    // add rhs
	Matrix3     operator-(const Matrix3& rhs) const;    // subtract rhs
	Matrix3&    operator+=(const Matrix3& rhs);         // add rhs and update this object
	Matrix3&    operator-=(const Matrix3& rhs);         // subtract rhs and update this object
	Vec3f		operator*(const Vec3f& rhs) const;    // multiplication: v' = M * v
	Matrix3     operator*(const Matrix3& rhs) const;    // multiplication: M3 = M1 * M2
	Matrix3&    operator*=(const Matrix3& rhs);         // multiplication: M1' = M1 * M2
	bool        operator==(const Matrix3& rhs) const;   // exact compare, no epsilon
	bool        operator!=(const Matrix3& rhs) const;   // exact compare, no epsilon
	float       operator[](int index) const;            // subscript operator v[0], v[1]
	float&      operator[](int index);                  // subscript operator v[0], v[1]

	// friends functions
	friend Matrix3 operator-(const Matrix3& m);                     // unary operator (-)
	friend Matrix3 operator*(float scalar, const Matrix3& m);       // pre-multiplication
	friend Vec3f operator*(const Vec3f& vec, const Matrix3& m); // pre-multiplication
	friend std::ostream& operator<<(std::ostream& os, const Matrix3& m);


	
	float m[9];
	float tm[9];
};



///////////////////////////////////////////////////////////////////////////
// 4x4 matrix
///////////////////////////////////////////////////////////////////////////
struct Matrix4
{
	// constructors
	Matrix4();  // init with identity
	Matrix4(const float src[16]);
	Matrix4(float m00, float m01, float m02, float m03, // 1st column
			float m04, float m05, float m06, float m07, // 2nd column
			float m08, float m09, float m10, float m11, // 3rd column
			float m12, float m13, float m14, float m15);// 4th column

	void        Set(const float src[16]);
	void        Set(float m00, float m01, float m02, float m03, // 1st column
					float m04, float m05, float m06, float m07, // 2nd column
					float m08, float m09, float m10, float m11, // 3rd column
					float m12, float m13, float m14, float m15);// 4th column
	void        SetAllRow(float m00, float m01, float m02, float m03,	// 1st row
						float m10, float m11, float m12, float m13,		// 2nd row
						float m20, float m21, float m22, float m23,		// 3rd row
						float m30, float m31, float m32, float m33);	// 4th row
	void        SetRow(int index, const float row[4]);
	void        SetRow(int index, const Vec4f& v);
	void        SetRow(int index, const Vec3f& v);
	void        SetColumn(int index, const float col[4]);
	void        SetColumn(int index, const Vec4f& v);
	void        SetColumn(int index, const Vec3f& v);

	const float* Get() const;
	const float* GetTranspose();                        // return transposed matrix
	Vec4f		GetRow(int index) const;                // return the selected row vector
	Vec4f		GetColumn(int index) const;             // return the selected col vector
	float       GetDeterminant() const;
	Vec3f		GetAngle() const;                       // return (pitch, yaw, roll) in degree
	Vec3f		GetLeftAxis() const;                    // return left vector
	Vec3f		GetUpAxis() const;                      // return up vector
	Vec3f		GetForwardAxis() const;                 // return forward vector

	Matrix4&    Identity();
	Matrix4&    Transpose();                            // transpose itself and return reference
	Matrix4&    Invert();                               // check best inverse method before inverse
	Matrix4&    InvertEuclidean();                      // inverse of Euclidean transform matrix
	Matrix4&    InvertAffine();                         // inverse of affine transform matrix
	Matrix4&    InvertProjective();                     // inverse of projective matrix using partitioning
	Matrix4&    InvertGeneral();                        // inverse of generic matrix

	// transform matrix
	Matrix4&    Translate(float x, float y, float z);   // translation by (x,y,z)
	Matrix4&    Translate(const Vec3f& v);            //
	Matrix4&    Rotate(float angle, const Vec3f& axis); // rotate angle(degree) along the given axix
	Matrix4&    Rotate(float angle, float x, float y, float z);
	Matrix4&    RotateX(float angle);                   // rotate on X-axis with degree
	Matrix4&    RotateY(float angle);                   // rotate on Y-axis with degree
	Matrix4&    RotateZ(float angle);                   // rotate on Z-axis with degree
	Matrix4&    Scale(float scale);                     // uniform scale
	Matrix4&    Scale(float sx, float sy, float sz);    // scale by (sx, sy, sz) on each axis
	Matrix4&    LookAt(float tx, float ty, float tz);   // face object to the target direction
	Matrix4&    LookAt(float tx, float ty, float tz, float ux, float uy, float uz);
	Matrix4&    LookAt(const Vec3f& target);
	Matrix4&    LookAt(const Vec3f& target, const Vec3f& up);
	//@@Matrix4&    skew(float angle, const Vector3& axis); //

	// operators
	Matrix4     operator+(const Matrix4& rhs) const;    // add rhs
	Matrix4     operator-(const Matrix4& rhs) const;    // subtract rhs
	Matrix4&    operator+=(const Matrix4& rhs);         // add rhs and update this object
	Matrix4&    operator-=(const Matrix4& rhs);         // subtract rhs and update this object
	Vec4f		operator*(const Vec4f& rhs) const;		// multiplication: v' = M * v
	Vec3f		operator*(const Vec3f& rhs) const;		// multiplication: v' = M * v
	Matrix4     operator*(const Matrix4& rhs) const;    // multiplication: M3 = M1 * M2
	Matrix4&    operator*=(const Matrix4& rhs);         // multiplication: M1' = M1 * M2
	bool        operator==(const Matrix4& rhs) const;   // exact compare, no epsilon
	bool        operator!=(const Matrix4& rhs) const;   // exact compare, no epsilon
	float       operator[](int index) const;            // subscript operator v[0], v[1]
	float&      operator[](int index);                  // subscript operator v[0], v[1]

	// friends functions
	friend Matrix4 operator-(const Matrix4& m);                     // unary operator (-)
	friend Matrix4 operator*(float scalar, const Matrix4& m);       // pre-multiplication
	friend Vec3f operator*(const Vec3f& vec, const Matrix4& m);		// pre-multiplication
	friend Vec4f operator*(const Vec4f& vec, const Matrix4& m);		// pre-multiplication
	friend std::ostream& operator<<(std::ostream& os, const Matrix4& m);

	
	float       GetCofactor(float m0, float m1, float m2,
							float m3, float m4, float m5,
							float m6, float m7, float m8) const;


	
	float m[16];
	float tm[16];                                       // transpose m
};



///////////////////////////////////////////////////////////////////////////
// inline functions for Matrix2
///////////////////////////////////////////////////////////////////////////
inline Matrix2::Matrix2()
{
	// initially identity matrix
	Identity();
}



inline Matrix2::Matrix2(const float src[4])
{
	Set(src);
}



inline Matrix2::Matrix2(float m0, float m1, float m2, float m3)
{
	Set(m0, m1, m2, m3);
}



inline void Matrix2::Set(const float src[4])
{
	m[0] = src[0];  m[1] = src[1];  m[2] = src[2];  m[3] = src[3];
}



inline void Matrix2::Set(float m0, float m1, float m2, float m3)
{
	m[0] = m0;  m[1] = m1;  m[2] = m2;  m[3] = m3;
}



inline void Matrix2::SetAllRow(float m00, float m01, float m10, float m11)
{
	m[0] = m00; m[2] = m01;
	m[1] = m10; m[3] = m11;
}



inline void Matrix2::SetRow(int index, const float row[2])
{
	m[index] = row[0];  m[index + 2] = row[1];
}



inline void Matrix2::SetRow(int index, const Vec2f& v)
{
	m[index] = v.X;  m[index + 2] = v.Y;
}



inline void Matrix2::SetColumn(int index, const float col[2])
{
	m[index * 2] = col[0];  m[index * 2 + 1] = col[1];
}



inline void Matrix2::SetColumn(int index, const Vec2f& v)
{
	m[index * 2] = v.X;  m[index * 2 + 1] = v.Y;
}



inline const float* Matrix2::Get() const
{
	return m;
}



inline const float* Matrix2::GetTranspose()
{
	tm[0] = m[0];   tm[2] = m[1];
	tm[1] = m[2];   tm[3] = m[3];
	return tm;
}



inline Vec2f Matrix2::GetRow(int index) const
{
	return Vec2f(m[index], m[index + 2]);
}



inline Vec2f Matrix2::GetColumn(int index) const
{
	return Vec2f(m[index * 2], m[index * 2 + 1]);
}



inline Matrix2& Matrix2::Identity()
{
	m[0] = m[3] = 1.0f;
	m[1] = m[2] = 0.0f;
	return *this;
}



inline Matrix2 Matrix2::operator+(const Matrix2& rhs) const
{
	return Matrix2(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3]);
}



inline Matrix2 Matrix2::operator-(const Matrix2& rhs) const
{
	return Matrix2(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3]);
}



inline Matrix2& Matrix2::operator+=(const Matrix2& rhs)
{
	m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];  m[3] += rhs[3];
	return *this;
}



inline Matrix2& Matrix2::operator-=(const Matrix2& rhs)
{
	m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];  m[3] -= rhs[3];
	return *this;
}



inline Vec2f Matrix2::operator*(const Vec2f& rhs) const
{
	return Vec2f(m[0] * rhs.X + m[2] * rhs.Y, m[1] * rhs.X + m[3] * rhs.Y);
}



inline Matrix2 Matrix2::operator*(const Matrix2& rhs) const
{
	return Matrix2(m[0] * rhs[0] + m[2] * rhs[1], m[1] * rhs[0] + m[3] * rhs[1],
		m[0] * rhs[2] + m[2] * rhs[3], m[1] * rhs[2] + m[3] * rhs[3]);
}



inline Matrix2& Matrix2::operator*=(const Matrix2& rhs)
{
	*this = *this * rhs;
	return *this;
}



inline bool Matrix2::operator==(const Matrix2& rhs) const
{
	return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) && (m[3] == rhs[3]);
}



inline bool Matrix2::operator!=(const Matrix2& rhs) const
{
	return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) || (m[3] != rhs[3]);
}



inline float Matrix2::operator[](int index) const
{
	return m[index];
}



inline float& Matrix2::operator[](int index)
{
	return m[index];
}



inline Matrix2 operator-(const Matrix2& rhs)
{
	return Matrix2(-rhs[0], -rhs[1], -rhs[2], -rhs[3]);
}



inline Matrix2 operator*(float s, const Matrix2& rhs)
{
	return Matrix2(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3]);
}



inline Vec2f operator*(const Vec2f& v, const Matrix2& rhs)
{
	return Vec2f(v.X*rhs[0] + v.Y*rhs[1], v.X*rhs[2] + v.Y*rhs[3]);
}



inline std::ostream& operator<<(std::ostream& os, const Matrix2& m)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[2] << "]\n"
		<< "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[3] << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}
// END OF MATRIX2 INLINE //////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////
// inline functions for Matrix3
///////////////////////////////////////////////////////////////////////////
inline Matrix3::Matrix3()
{
	// initially identity matrix
	Identity();
}



inline Matrix3::Matrix3(const float src[9])
{
	Set(src);
}



inline Matrix3::Matrix3(float m0, float m1, float m2,
	float m3, float m4, float m5,
	float m6, float m7, float m8)
{
	Set(m0, m1, m2, m3, m4, m5, m6, m7, m8);
}



inline void Matrix3::Set(const float src[9])
{
	m[0] = src[0];  m[1] = src[1];  m[2] = src[2];
	m[3] = src[3];  m[4] = src[4];  m[5] = src[5];
	m[6] = src[6];  m[7] = src[7];  m[8] = src[8];
}



inline void Matrix3::Set(float m0, float m1, float m2,
	float m3, float m4, float m5,
	float m6, float m7, float m8)
{
	m[0] = m0;  m[1] = m1;  m[2] = m2;
	m[3] = m3;  m[4] = m4;  m[5] = m5;
	m[6] = m6;  m[7] = m7;  m[8] = m8;
}



inline void Matrix3::SetAllRow(float m00, float m01, float m02,
	float m10, float m11, float m12,
	float m20, float m21, float m22)
{
	m[0] = m00; m[3] = m01; m[6] = m02;
	m[1] = m10; m[4] = m11; m[7] = m12;
	m[2] = m20; m[5] = m22; m[8] = m22;
}



inline void Matrix3::SetRow(int index, const float row[3])
{
	m[index] = row[0];  m[index + 3] = row[1];  m[index + 6] = row[2];
}



inline void Matrix3::SetRow(int index, const Vec3f& v)
{
	m[index] = v.X;  m[index + 3] = v.Y;  m[index + 6] = v.Z;
}



inline void Matrix3::SetColumn(int index, const float col[3])
{
	m[index * 3] = col[0];  m[index * 3 + 1] = col[1];  m[index * 3 + 2] = col[2];
}



inline void Matrix3::SetColumn(int index, const Vec3f& v)
{
	m[index * 3] = v.X;  m[index * 3 + 1] = v.Y;  m[index * 3 + 2] = v.Z;
}



inline const float* Matrix3::Get() const
{
	return m;
}



inline const float* Matrix3::GetTranspose()
{
	tm[0] = m[0];   tm[1] = m[3];   tm[2] = m[6];
	tm[3] = m[1];   tm[4] = m[4];   tm[5] = m[7];
	tm[6] = m[2];   tm[7] = m[5];   tm[8] = m[8];
	return tm;
}



inline Vec3f Matrix3::GetRow(int index) const
{
	return Vec3f(m[index], m[index + 3], m[index + 6]);
}



inline Vec3f Matrix3::GetColumn(int index) const
{
	return Vec3f(m[index * 3], m[index * 3 + 1], m[index * 3 + 2]);
}



inline Matrix3& Matrix3::Identity()
{
	m[0] = m[4] = m[8] = 1.0f;
	m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
	return *this;
}



inline Matrix3 Matrix3::operator+(const Matrix3& rhs) const
{
	return Matrix3(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2],
		m[3] + rhs[3], m[4] + rhs[4], m[5] + rhs[5],
		m[6] + rhs[6], m[7] + rhs[7], m[8] + rhs[8]);
}



inline Matrix3 Matrix3::operator-(const Matrix3& rhs) const
{
	return Matrix3(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2],
		m[3] - rhs[3], m[4] - rhs[4], m[5] - rhs[5],
		m[6] - rhs[6], m[7] - rhs[7], m[8] - rhs[8]);
}



inline Matrix3& Matrix3::operator+=(const Matrix3& rhs)
{
	m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];
	m[3] += rhs[3];  m[4] += rhs[4];  m[5] += rhs[5];
	m[6] += rhs[6];  m[7] += rhs[7];  m[8] += rhs[8];
	return *this;
}



inline Matrix3& Matrix3::operator-=(const Matrix3& rhs)
{
	m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];
	m[3] -= rhs[3];  m[4] -= rhs[4];  m[5] -= rhs[5];
	m[6] -= rhs[6];  m[7] -= rhs[7];  m[8] -= rhs[8];
	return *this;
}



inline Vec3f Matrix3::operator*(const Vec3f& rhs) const
{
	return Vec3f(m[0] * rhs.X + m[3] * rhs.Y + m[6] * rhs.Z,
				m[1] * rhs.X + m[4] * rhs.Y + m[7] * rhs.Z,
				m[2] * rhs.X + m[5] * rhs.Y + m[8] * rhs.Z);
}



inline Matrix3 Matrix3::operator*(const Matrix3& rhs) const
{
	return Matrix3(m[0] * rhs[0] + m[3] * rhs[1] + m[6] * rhs[2], m[1] * rhs[0] + m[4] * rhs[1] + m[7] * rhs[2], m[2] * rhs[0] + m[5] * rhs[1] + m[8] * rhs[2],
		m[0] * rhs[3] + m[3] * rhs[4] + m[6] * rhs[5], m[1] * rhs[3] + m[4] * rhs[4] + m[7] * rhs[5], m[2] * rhs[3] + m[5] * rhs[4] + m[8] * rhs[5],
		m[0] * rhs[6] + m[3] * rhs[7] + m[6] * rhs[8], m[1] * rhs[6] + m[4] * rhs[7] + m[7] * rhs[8], m[2] * rhs[6] + m[5] * rhs[7] + m[8] * rhs[8]);
}



inline Matrix3& Matrix3::operator*=(const Matrix3& rhs)
{
	*this = *this * rhs;
	return *this;
}



inline bool Matrix3::operator==(const Matrix3& rhs) const
{
	return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) &&
		(m[3] == rhs[3]) && (m[4] == rhs[4]) && (m[5] == rhs[5]) &&
		(m[6] == rhs[6]) && (m[7] == rhs[7]) && (m[8] == rhs[8]);
}



inline bool Matrix3::operator!=(const Matrix3& rhs) const
{
	return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) ||
		(m[3] != rhs[3]) || (m[4] != rhs[4]) || (m[5] != rhs[5]) ||
		(m[6] != rhs[6]) || (m[7] != rhs[7]) || (m[8] != rhs[8]);
}



inline float Matrix3::operator[](int index) const
{
	return m[index];
}



inline float& Matrix3::operator[](int index)
{
	return m[index];
}



inline Matrix3 operator-(const Matrix3& rhs)
{
	return Matrix3(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6], -rhs[7], -rhs[8]);
}



inline Matrix3 operator*(float s, const Matrix3& rhs)
{
	return Matrix3(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3], s*rhs[4], s*rhs[5], s*rhs[6], s*rhs[7], s*rhs[8]);
}



inline Vec3f operator*(const Vec3f& v, const Matrix3& m)
{
	return Vec3f(v.X*m[0] + v.Y*m[1] + v.Z*m[2], v.X*m[3] + v.Y*m[4] + v.Z*m[5], v.X*m[6] + v.Y*m[7] + v.Z*m[8]);
}



inline std::ostream& operator<<(std::ostream& os, const Matrix3& m)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[3] << " " << std::setw(10) << m[6] << "]\n"
		<< "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[7] << "]\n"
		<< "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[5] << " " << std::setw(10) << m[8] << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}
// END OF MATRIX3 INLINE //////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////
// inline functions for Matrix4
///////////////////////////////////////////////////////////////////////////
inline Matrix4::Matrix4()
{
	// initially identity matrix
	Identity();
}



inline Matrix4::Matrix4(const float src[16])
{
	Set(src);
}



inline Matrix4::Matrix4(float m00, float m01, float m02, float m03,
	float m04, float m05, float m06, float m07,
	float m08, float m09, float m10, float m11,
	float m12, float m13, float m14, float m15)
{
	Set(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);
}



inline void Matrix4::Set(const float src[16])
{
	m[0] = src[0];  m[1] = src[1];  m[2] = src[2];  m[3] = src[3];
	m[4] = src[4];  m[5] = src[5];  m[6] = src[6];  m[7] = src[7];
	m[8] = src[8];  m[9] = src[9];  m[10] = src[10]; m[11] = src[11];
	m[12] = src[12]; m[13] = src[13]; m[14] = src[14]; m[15] = src[15];
}



inline void Matrix4::Set(float m00, float m01, float m02, float m03,
	float m04, float m05, float m06, float m07,
	float m08, float m09, float m10, float m11,
	float m12, float m13, float m14, float m15)
{
	m[0] = m00;  m[1] = m01;  m[2] = m02;  m[3] = m03;
	m[4] = m04;  m[5] = m05;  m[6] = m06;  m[7] = m07;
	m[8] = m08;  m[9] = m09;  m[10] = m10;  m[11] = m11;
	m[12] = m12;  m[13] = m13;  m[14] = m14;  m[15] = m15;
}



inline void Matrix4::SetAllRow(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	m[0] = m00; m[4] = m01; m[8] = m02; m[12] = m03;
	m[1] = m10; m[5] = m11; m[9] = m12; m[13] = m13;
	m[2] = m20; m[6] = m21; m[10] = m22; m[14] = m23;
	m[3] = m30; m[7] = m31; m[11] = m32; m[15] = m33;
}



inline void Matrix4::SetRow(int index, const float row[4])
{
	m[index] = row[0];  m[index + 4] = row[1];  m[index + 8] = row[2];  m[index + 12] = row[3];
}



inline void Matrix4::SetRow(int index, const Vec4f& v)
{
	m[index] = v.X;  m[index + 4] = v.Y;  m[index + 8] = v.Z;  m[index + 12] = v.W;
}



inline void Matrix4::SetRow(int index, const Vec3f& v)
{
	m[index] = v.X;  m[index + 4] = v.Y;  m[index + 8] = v.Z;
}



inline void Matrix4::SetColumn(int index, const float col[4])
{
	m[index * 4] = col[0];  m[index * 4 + 1] = col[1];  m[index * 4 + 2] = col[2];  m[index * 4 + 3] = col[3];
}



inline void Matrix4::SetColumn(int index, const Vec4f& v)
{
	m[index * 4] = v.X;  m[index * 4 + 1] = v.Y;  m[index * 4 + 2] = v.Z;  m[index * 4 + 3] = v.W;
}



inline void Matrix4::SetColumn(int index, const Vec3f& v)
{
	m[index * 4] = v.X;  m[index * 4 + 1] = v.Y;  m[index * 4 + 2] = v.Z;
}



inline const float* Matrix4::Get() const
{
	return m;
}



inline const float* Matrix4::GetTranspose()
{
	tm[0] = m[0];   tm[1] = m[4];   tm[2] = m[8];   tm[3] = m[12];
	tm[4] = m[1];   tm[5] = m[5];   tm[6] = m[9];   tm[7] = m[13];
	tm[8] = m[2];   tm[9] = m[6];   tm[10] = m[10];  tm[11] = m[14];
	tm[12] = m[3];   tm[13] = m[7];   tm[14] = m[11];  tm[15] = m[15];
	return tm;
}



inline Vec4f Matrix4::GetRow(int index) const
{
	return Vec4f(m[index], m[index + 4], m[index + 8], m[index + 12]);
}



inline Vec4f Matrix4::GetColumn(int index) const
{
	return Vec4f(m[index * 4], m[index * 4 + 1], m[index * 4 + 2], m[index * 4 + 3]);
}



inline Vec3f Matrix4::GetLeftAxis() const
{
	return Vec3f(m[0], m[1], m[2]);
}



inline Vec3f Matrix4::GetUpAxis() const
{
	return Vec3f(m[4], m[5], m[6]);
}



inline Vec3f Matrix4::GetForwardAxis() const
{
	return Vec3f(m[8], m[9], m[10]);
}



inline Matrix4& Matrix4::Identity()
{
	m[0] = m[5] = m[10] = m[15] = 1.0f;
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	return *this;
}



inline Matrix4 Matrix4::operator+(const Matrix4& rhs) const
{
	return Matrix4(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3],
		m[4] + rhs[4], m[5] + rhs[5], m[6] + rhs[6], m[7] + rhs[7],
		m[8] + rhs[8], m[9] + rhs[9], m[10] + rhs[10], m[11] + rhs[11],
		m[12] + rhs[12], m[13] + rhs[13], m[14] + rhs[14], m[15] + rhs[15]);
}



inline Matrix4 Matrix4::operator-(const Matrix4& rhs) const
{
	return Matrix4(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3],
		m[4] - rhs[4], m[5] - rhs[5], m[6] - rhs[6], m[7] - rhs[7],
		m[8] - rhs[8], m[9] - rhs[9], m[10] - rhs[10], m[11] - rhs[11],
		m[12] - rhs[12], m[13] - rhs[13], m[14] - rhs[14], m[15] - rhs[15]);
}



inline Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
	m[0] += rhs[0];   m[1] += rhs[1];   m[2] += rhs[2];   m[3] += rhs[3];
	m[4] += rhs[4];   m[5] += rhs[5];   m[6] += rhs[6];   m[7] += rhs[7];
	m[8] += rhs[8];   m[9] += rhs[9];   m[10] += rhs[10];  m[11] += rhs[11];
	m[12] += rhs[12];  m[13] += rhs[13];  m[14] += rhs[14];  m[15] += rhs[15];
	return *this;
}



inline Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
	m[0] -= rhs[0];   m[1] -= rhs[1];   m[2] -= rhs[2];   m[3] -= rhs[3];
	m[4] -= rhs[4];   m[5] -= rhs[5];   m[6] -= rhs[6];   m[7] -= rhs[7];
	m[8] -= rhs[8];   m[9] -= rhs[9];   m[10] -= rhs[10];  m[11] -= rhs[11];
	m[12] -= rhs[12];  m[13] -= rhs[13];  m[14] -= rhs[14];  m[15] -= rhs[15];
	return *this;
}



inline Vec4f Matrix4::operator*(const Vec4f& rhs) const
{
	return Vec4f(m[0] * rhs.X + m[4] * rhs.Y + m[8] * rhs.Z + m[12] * rhs.W,
				m[1] * rhs.X + m[5] * rhs.Y + m[9] * rhs.Z + m[13] * rhs.W,
				m[2] * rhs.X + m[6] * rhs.Y + m[10] * rhs.Z + m[14] * rhs.W,
				m[3] * rhs.X + m[7] * rhs.Y + m[11] * rhs.Z + m[15] * rhs.W);
}



inline Vec3f Matrix4::operator*(const Vec3f& rhs) const
{
	return Vec3f(m[0] * rhs.X + m[4] * rhs.Y + m[8] * rhs.Z + m[12],
				m[1] * rhs.X + m[5] * rhs.Y + m[9] * rhs.Z + m[13],
				m[2] * rhs.X + m[6] * rhs.Y + m[10] * rhs.Z + m[14]);
}



inline Matrix4 Matrix4::operator*(const Matrix4& n) const
{
	return Matrix4(m[0] * n[0] + m[4] * n[1] + m[8] * n[2] + m[12] * n[3], m[1] * n[0] + m[5] * n[1] + m[9] * n[2] + m[13] * n[3], m[2] * n[0] + m[6] * n[1] + m[10] * n[2] + m[14] * n[3], m[3] * n[0] + m[7] * n[1] + m[11] * n[2] + m[15] * n[3],
		m[0] * n[4] + m[4] * n[5] + m[8] * n[6] + m[12] * n[7], m[1] * n[4] + m[5] * n[5] + m[9] * n[6] + m[13] * n[7], m[2] * n[4] + m[6] * n[5] + m[10] * n[6] + m[14] * n[7], m[3] * n[4] + m[7] * n[5] + m[11] * n[6] + m[15] * n[7],
		m[0] * n[8] + m[4] * n[9] + m[8] * n[10] + m[12] * n[11], m[1] * n[8] + m[5] * n[9] + m[9] * n[10] + m[13] * n[11], m[2] * n[8] + m[6] * n[9] + m[10] * n[10] + m[14] * n[11], m[3] * n[8] + m[7] * n[9] + m[11] * n[10] + m[15] * n[11],
		m[0] * n[12] + m[4] * n[13] + m[8] * n[14] + m[12] * n[15], m[1] * n[12] + m[5] * n[13] + m[9] * n[14] + m[13] * n[15], m[2] * n[12] + m[6] * n[13] + m[10] * n[14] + m[14] * n[15], m[3] * n[12] + m[7] * n[13] + m[11] * n[14] + m[15] * n[15]);
}



inline Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
	*this = *this * rhs;
	return *this;
}



inline bool Matrix4::operator==(const Matrix4& n) const
{
	return (m[0] == n[0]) && (m[1] == n[1]) && (m[2] == n[2]) && (m[3] == n[3]) &&
		(m[4] == n[4]) && (m[5] == n[5]) && (m[6] == n[6]) && (m[7] == n[7]) &&
		(m[8] == n[8]) && (m[9] == n[9]) && (m[10] == n[10]) && (m[11] == n[11]) &&
		(m[12] == n[12]) && (m[13] == n[13]) && (m[14] == n[14]) && (m[15] == n[15]);
}



inline bool Matrix4::operator!=(const Matrix4& n) const
{
	return (m[0] != n[0]) || (m[1] != n[1]) || (m[2] != n[2]) || (m[3] != n[3]) ||
		(m[4] != n[4]) || (m[5] != n[5]) || (m[6] != n[6]) || (m[7] != n[7]) ||
		(m[8] != n[8]) || (m[9] != n[9]) || (m[10] != n[10]) || (m[11] != n[11]) ||
		(m[12] != n[12]) || (m[13] != n[13]) || (m[14] != n[14]) || (m[15] != n[15]);
}



inline float Matrix4::operator[](int index) const
{
	return m[index];
}



inline float& Matrix4::operator[](int index)
{
	return m[index];
}



inline Matrix4 operator-(const Matrix4& rhs)
{
	return Matrix4(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6], -rhs[7], -rhs[8], -rhs[9], -rhs[10], -rhs[11], -rhs[12], -rhs[13], -rhs[14], -rhs[15]);
}



inline Matrix4 operator*(float s, const Matrix4& rhs)
{
	return Matrix4(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3], s*rhs[4], s*rhs[5], s*rhs[6], s*rhs[7], s*rhs[8], s*rhs[9], s*rhs[10], s*rhs[11], s*rhs[12], s*rhs[13], s*rhs[14], s*rhs[15]);
}



inline Vec4f operator*(const Vec4f& v, const Matrix4& m)
{
	return Vec4f(v.X*m[0] + v.Y*m[1] + v.Z*m[2] + v.W*m[3], v.X*m[4] + v.Y*m[5] + v.Z*m[6] + v.W*m[7], v.X*m[8] + v.Y*m[9] + v.Z*m[10] + v.W*m[11], v.W*m[12] + v.Y*m[13] + v.Z*m[14] + v.W*m[15]);
}



inline Vec3f operator*(const Vec3f& v, const Matrix4& m)
{
	return Vec3f(v.X*m[0] + v.Y*m[1] + v.Z*m[2], v.X*m[4] + v.Y*m[5] + v.Z*m[6], v.X*m[8] + v.Y*m[9] + v.Z*m[10]);
}



inline std::ostream& operator<<(std::ostream& os, const Matrix4& m)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[8] << " " << std::setw(10) << m[12] << "]\n"
		<< "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[5] << " " << std::setw(10) << m[9] << " " << std::setw(10) << m[13] << "]\n"
		<< "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[6] << " " << std::setw(10) << m[10] << " " << std::setw(10) << m[14] << "]\n"
		<< "[" << std::setw(10) << m[3] << " " << std::setw(10) << m[7] << " " << std::setw(10) << m[11] << " " << std::setw(10) << m[15] << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}
// END OF MATRIX4 INLINE //////////////////////////////////////////////////////
#endif
