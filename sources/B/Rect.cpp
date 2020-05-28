/*
** B, 2019
** Rect.cpp
*/

#include "B/Rect.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////


bool Rect::contains(const Position &point)
{
	return x() <= point.x && point.x < x() + (int)width()
	    && y() <= point.y && point.y < y() + (int)height();
}


Rect &Rect::operator =(const Rect &rhs)
{
	setPosition(rhs.position());
	setSize(rhs.size());
	return *this;
}

bool Rect::operator ==(const Rect &rhs) const
{
	return (position() == rhs.position()) && (size() == rhs.size());
}

bool Rect::operator !=(const Rect &rhs) const
{
	return !(*this == rhs);
}

////////////////////////////////////////////////////////////////////////////////

}