/*
** B, 2019
** Position.cpp
*/

#include "B/Position.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

Position::Position()
: x(0)
, y(0)
{}

Position::Position(int x_, int y_)
: x(x_)
, y(y_)
{}

Position::Position(const Position &other)
: x(other.x)
, y(other.y)
{}


Position &Position::operator =(const Position &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

bool Position::operator ==(const Position &rhs) const
{
	return (this->x == rhs.x) && (this->y == rhs.y);
}

bool Position::operator !=(const Position &rhs) const
{
	return !(*this == rhs);
}

Position Position::operator +(const Position &rhs) const
{
	return Position(this->x + rhs.x, this->y + rhs.y);
}

Position Position::operator -(const Position &rhs) const
{
	return Position(this->x - rhs.x, this->y - rhs.y);
}

void Position::operator +=(const Position &rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
}

void Position::operator -=(const Position &rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
}

////////////////////////////////////////////////////////////////////////////////

Positionable::Positionable()
: m_pos(0, 0)
{}

Positionable::Positionable(int x, int y)
: m_pos(x, y)
{}

Positionable::Positionable(const Position &pos)
: m_pos(pos.x, pos.y)
{}

////////////////////////////////////////////////////////////////////////////////

}