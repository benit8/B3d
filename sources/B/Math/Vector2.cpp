/*
** B, 2019
** Graphics / Vector2.cpp
*/

#include "B/Math/Vector2.hpp"
#include "B/Common.hpp"
#include <cfloat>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

Vector2::Vector2(f64 n)
: x(n)
, y(n)
{}

Vector2::Vector2(f64 _x, f64 _y)
: x(_x)
, y(_y)
{}

Vector2::Vector2(const Position &other)
: x(other.x)
, y(other.y)
{}

Vector2::Vector2(const Vector2 &other)
: x(other.x)
, y(other.y)
{}

Vector2::Vector2(const Vector3 &other)
: x(other.x)
, y(other.y)
{}


f64 Vector2::length() const
{
	return sqrt(lengthSq());
}

f64 Vector2::lengthSq() const
{
	return dot(*this);
}

f64 Vector2::dot(const Vector2 &other) const
{
	return this->x * other.x + this->y * other.y;
}

f64 Vector2::cross(const Vector2 &other) const
{
	return this->x * other.y - this->y * other.x;
}

f64 Vector2::dist(const Vector2 &other) const
{
	return (other - *this).length();
}

Vector2 &Vector2::normalize()
{
	return *this /= length();
}

Vector2 Vector2::normalized() const
{
	Vector2 res = *this / length();
	return res;
}

Vector2 Vector2::abs() const
{
	return Vector2(fabs(x), fabs(y));
}

f64 Vector2::min() const
{
	return B::min(this->x, this->y);
}

f64 Vector2::max() const
{
	return B::max(this->x, this->y);
}


Vector2 &Vector2::operator =(const Vector2 &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

Vector2 Vector2::operator +(const Vector2 &rhs) const
{
	return Vector2(this->x + rhs.x, this->y + rhs.y);
}

Vector2 Vector2::operator +(f64 rhs) const
{
	return Vector2(this->x + rhs, this->y + rhs);
}

Vector2 Vector2::operator -(const Vector2 &rhs) const
{
	return Vector2(this->x - rhs.x, this->y - rhs.y);
}

Vector2 Vector2::operator -(f64 rhs) const
{
	return Vector2(this->x - rhs, this->y - rhs);
}

Vector2 Vector2::operator -() const
{
	return Vector2(-this->x, -this->y);
}

Vector2 Vector2::operator *(f64 rhs) const
{
	return Vector2(this->x * rhs, this->y * rhs);
}

Vector2 Vector2::operator /(f64 rhs) const
{
	return Vector2(this->x / rhs, this->y / rhs);
}

Vector2 &Vector2::operator +=(const Vector2 &rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

Vector2 &Vector2::operator +=(f64 rhs)
{
	this->x += rhs;
	this->y += rhs;
	return *this;
}

Vector2 &Vector2::operator -=(const Vector2 &rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

Vector2 &Vector2::operator -=(f64 rhs)
{
	this->x -= rhs;
	this->y -= rhs;
	return *this;
}

Vector2 &Vector2::operator *=(f64 rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}

Vector2 &Vector2::operator /=(f64 rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

bool Vector2::operator ==(const Vector2 &rhs) const
{
	return fabs(this->x - rhs.x) < DBL_EPSILON
	    && fabs(this->y - rhs.y) < DBL_EPSILON;
}

bool Vector2::operator !=(const Vector2 &rhs) const
{
	return !(*this == rhs);
}

Vector2::operator Vector3() const
{
	return Vector3(this->x, this->y, 0.0);
}

Vector2::operator Position() const
{
	return Position(round(this->x), round(this->y));
}

////////////////////////////////////////////////////////////////////////////////

}