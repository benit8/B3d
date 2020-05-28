/*
** B, 2019
** Size.cpp
*/

#include "B/Size.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

// Size::Size()
// : width(0)
// , height(0)
// {}

Size::Size(unsigned w, unsigned h)
: width(w)
, height(h)
{}

// Size::Size(const Size &other)
// : width(other.width)
// , height(other.height)
// {}


// Size &Size::operator =(const Size &rhs)
// {
// 	width = rhs.width;
// 	height = rhs.height;
// 	return *this;
// }

bool Size::operator ==(const Size &rhs) const
{
	return (width == rhs.width) && (height == rhs.height);
}

bool Size::operator !=(const Size &rhs) const
{
	return !(*this == rhs);
}

Size Size::operator +(const Size &rhs) const
{
	return Size(width + rhs.width, height + rhs.height);
}

Size Size::operator -(const Size &rhs) const
{
	return Size(width - rhs.width, height - rhs.height);
}

void Size::operator +=(const Size &rhs)
{
	width += rhs.width;
	height += rhs.height;
}

void Size::operator -=(const Size &rhs)
{
	width -= rhs.width;
	height -= rhs.height;
}

////////////////////////////////////////////////////////////////////////////////

Sizeable::Sizeable()
: m_size(0, 0)
{}

Sizeable::Sizeable(unsigned w, unsigned h)
: m_size(w, h)
{}

Sizeable::Sizeable(const Size &size)
: m_size(size)
{}

////////////////////////////////////////////////////////////////////////////////

}