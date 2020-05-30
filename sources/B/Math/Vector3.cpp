/*
** B, 2019
** Graphics / Vector3.cpp
*/

#include "B/Math/Vector3.hpp"
#include "B/Common.hpp"
#include <cfloat>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3(f64 n)
: x(n)
, y(n)
, z(n)
{}

Vector3::Vector3(f64 _x, f64 _y, f64 _z)
: x(_x)
, y(_y)
, z(_z)
{}

Vector3::Vector3(const Vector3 &other)
: x(other.x)
, y(other.y)
, z(other.z)
{}

Vector3::Vector3(const Vector2 &other)
: x(other.x)
, y(other.y)
, z(0)
{}


f64 Vector3::length() const
{
	return sqrt(lengthSq());
}

f64 Vector3::lengthSq() const
{
	return dot(*this);
}

f64 Vector3::dot(const Vector3 &other) const
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3 Vector3::cross(const Vector3 &other) const
{
	return Vector3(
		this->y * other.z - this->z * other.y,
		this->z * other.x - this->x * other.z,
		this->x * other.y - this->y * other.x
	);
}

f64 Vector3::dist(const Vector3 &other) const
{
	return (other - *this).length();
}

Vector3 &Vector3::normalize()
{
	return *this /= length();
}

Vector3 Vector3::normalized() const
{
	return *this / length();
}

Vector3 Vector3::abs() const
{
	return Vector3(fabs(x), fabs(y), fabs(z));
}

f64 Vector3::min() const
{
	return B::min(this->x, this->y, this->z);
}

f64 Vector3::max() const
{
	return B::max(this->x, this->y, this->z);
}


Vector3 &Vector3::operator =(const Vector3 &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

Vector3 Vector3::operator +(const Vector3 &rhs) const
{
	return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

Vector3 Vector3::operator +(f64 rhs) const
{
	return Vector3(this->x + rhs, this->y + rhs, this->z + rhs);
}

Vector3 Vector3::operator -(const Vector3 &rhs) const
{
	return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

Vector3 Vector3::operator -(f64 rhs) const
{
	return Vector3(this->x - rhs, this->y - rhs, this->z - rhs);
}

Vector3 Vector3::operator -() const
{
	return Vector3(-this->x, -this->y, -this->z);
}

Vector3 Vector3::operator *(f64 rhs) const
{
	return Vector3(this->x * rhs, this->y * rhs, this->z * rhs);
}

Vector3 Vector3::operator *(const Matrix &rhs) const
{
	return rhs * (*this);
}

Vector3 Vector3::operator /(f64 rhs) const
{
	return Vector3(this->x / rhs, this->y / rhs, this->z / rhs);
}

Vector3 &Vector3::operator +=(const Vector3 &rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

Vector3 &Vector3::operator +=(f64 rhs)
{
	this->x += rhs;
	this->y += rhs;
	this->z += rhs;
	return *this;
}

Vector3 &Vector3::operator -=(const Vector3 &rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

Vector3 &Vector3::operator -=(f64 rhs)
{
	this->x -= rhs;
	this->y -= rhs;
	this->z -= rhs;
	return *this;
}

Vector3 &Vector3::operator *=(f64 rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;
	return *this;
}

Vector3 &Vector3::operator *=(const Matrix &rhs)
{
	return *this = *this * rhs;
}

Vector3 &Vector3::operator /=(f64 rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	this->z /= rhs;
	return *this;
}

bool Vector3::operator ==(const Vector3 &rhs) const
{
	return fabs(this->x - rhs.x) < DBL_EPSILON
	    && fabs(this->y - rhs.y) < DBL_EPSILON
	    && fabs(this->z - rhs.z) < DBL_EPSILON;
}

bool Vector3::operator !=(const Vector3 &rhs) const
{
	return !(*this == rhs);
}


Vector3::operator Vector2() const
{
	return Vector2(this->x, this->y);
}

Vector3::operator Position() const
{
	return Position(round(this->x), round(this->y));
}

////////////////////////////////////////////////////////////////////////////////

}