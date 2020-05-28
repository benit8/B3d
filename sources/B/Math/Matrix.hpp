/*
** B, 2019
** Math / Matrix.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Matrix;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Types.hpp"
#include "B/Math/Vector3.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class Matrix
{
public:
	Matrix();
	Matrix(const Matrix &other);
	~Matrix() = default;

	void setTranslated(const Vector3 &vec);
	void setRotated(const Vector3 &vec);
	void setRotatedX(f64 theta);
	void setRotatedY(f64 theta);
	void setRotatedZ(f64 theta);
	void setScaled(const Vector3 &vec);

	Matrix &identity();
	Matrix &translate(const Vector3 &vec);
	Matrix &rotate(const Vector3 &vec);
	Matrix &rotateX(f64 theta);
	Matrix &rotateY(f64 theta);
	Matrix &rotateZ(f64 theta);
	Matrix &scale(const Vector3 &vec);
	Matrix &inverse();

	Matrix &operator =(const Matrix &rhs);
	Matrix operator *(const Matrix &rhs) const;
	Matrix &operator *=(const Matrix &rhs);
	Vector3 operator *(const Vector3 &rhs) const;

	f64 &operator ()(unsigned i, unsigned j) { return m[i][j]; }
	const f64 &operator ()(unsigned i, unsigned j) const { return m[i][j]; }

	static Matrix projection(f64 aspectRatio, f64 fov = 90.0);
	static Matrix translated(const Vector3 &vec);
	static Matrix rotated(const Vector3 &vec);
	static Matrix rotatedX(f64 theta);
	static Matrix rotatedY(f64 theta);
	static Matrix rotatedZ(f64 theta);
	static Matrix scaled(const Vector3 &vec);

public:
	f64 m[4][4] = {0};
};

////////////////////////////////////////////////////////////////////////////////

}