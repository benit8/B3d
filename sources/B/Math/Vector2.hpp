/*
** B, 2019
** Math / Vector2.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Vector2;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Types.hpp"
#include "B/Position.hpp"
#include "B/Math/Vector3.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class Vector2
{
public:
	Vector2() = default;
	explicit Vector2(f64 n);
	Vector2(f64 x, f64 y);
	Vector2(const Position &other);
	Vector2(const Vector2 &other);
	explicit Vector2(const Vector3 &other);
	~Vector2() = default;

	f64 length() const;
	f64 lengthSq() const;
	f64 dot(const Vector2 &other) const;
	f64 cross(const Vector2 &other) const;
	f64 dist(const Vector2 &other) const;
	Vector2 &normalize();
	Vector2 normalized() const;
	Vector2 abs() const;
	f64 min() const;
	f64 max() const;

	Vector2 &operator =(const Vector2 &rhs);

	Vector2 operator +(const Vector2 &rhs) const;
	Vector2 operator +(f64 rhs) const;
	Vector2 operator -(const Vector2 &rhs) const;
	Vector2 operator -(f64 rhs) const;
	Vector2 operator -() const;
	Vector2 operator *(f64 rhs) const;
	Vector2 operator /(f64 rhs) const;
	Vector2 &operator +=(const Vector2 &rhs);
	Vector2 &operator +=(f64 rhs);
	Vector2 &operator -=(const Vector2 &rhs);
	Vector2 &operator -=(f64 rhs);
	Vector2 &operator *=(f64 rhs);
	Vector2 &operator /=(f64 rhs);

	bool operator ==(const Vector2 &rhs) const;
	bool operator !=(const Vector2 &rhs) const;

	explicit operator Vector3() const;
	operator Position() const;

public:
	f64 x = 0;
	f64 y = 0;
};

////////////////////////////////////////////////////////////////////////////////

}