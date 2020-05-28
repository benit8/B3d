/*
** B, 2019
** Math / Vector3.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Vector3;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Types.hpp"
#include "B/Position.hpp"
#include "B/Math/Vector2.hpp"
#include "B/Math/Matrix.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class Vector3
{
public:
	Vector3();
	Vector3(f64 n);
	Vector3(f64 x, f64 y, f64 z);
	Vector3(const Vector3 &other);
	Vector3(const Vector2 &other);
	~Vector3() = default;

	f64 length() const;
	f64 lengthSq() const;
	f64 dot(const Vector3 &other) const;
	Vector3 cross(const Vector3 &other) const;
	f64 dist(const Vector3 &other) const;
	Vector3 &normalize();
	Vector3 normalized() const;
	Vector3 abs() const;
	f64 min() const;
	f64 max() const;

	Vector3 &operator =(const Vector3 &rhs);

	Vector3 operator +(const Vector3 &rhs) const;
	Vector3 operator +(f64 rhs) const;
	Vector3 operator -(const Vector3 &rhs) const;
	Vector3 operator -(f64 rhs) const;
	Vector3 operator -() const;
	Vector3 operator *(f64 rhs) const;
	Vector3 operator *(const Matrix &rhs) const;
	Vector3 operator /(f64 rhs) const;
	Vector3 &operator +=(const Vector3 &rhs);
	Vector3 &operator +=(f64 rhs);
	Vector3 &operator -=(const Vector3 &rhs);
	Vector3 &operator -=(f64 rhs);
	Vector3 &operator *=(f64 rhs);
	Vector3 &operator *=(const Matrix &rhs);
	Vector3 &operator /=(f64 rhs);

	bool operator ==(const Vector3 &rhs) const;
	bool operator !=(const Vector3 &rhs) const;

	operator Vector2() const;
	operator Position() const;

public:
	f64 x, y, z;
};

////////////////////////////////////////////////////////////////////////////////

}