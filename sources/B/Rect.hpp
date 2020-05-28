/*
** B, 2019
** Rect.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Rect;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Size.hpp"
#include "B/Position.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class Rect : public Positionable, public Sizeable
{
public:
	Rect() = default;
	virtual ~Rect() = default;

	Rect(Rect &&rect)
	: Positionable(std::move(rect.position()))
	, Sizeable(std::move(rect.size()))
	{}

	Rect(const Rect &rect)
	: Positionable(rect.position())
	, Sizeable(rect.size())
	{}

	Rect(int x, int y, unsigned width, unsigned height)
	: Positionable(x, y)
	, Sizeable(width, height)
	{}

	Rect(const Position &position, const Size &size)
	: Positionable(position)
	, Sizeable(size)
	{}


	bool contains(const Position &point) const
	{
		return x() <= point.x && point.x < x() + (int)width()
		    && y() <= point.y && point.y < y() + (int)height();
	}

	Rect &operator =(Rect &&rhs)
	{
		setPosition(std::move(rhs.position()));
		setSize(std::move(rhs.size()));
		return *this;
	}

	Rect &operator =(const Rect &rhs)
	{
		setPosition(rhs.position());
		setSize(rhs.size());
		return *this;
	}

	bool operator ==(const Rect &rhs) const { return position() == rhs.position() && size() == rhs.size(); }
	bool operator !=(const Rect &rhs) const { return !(*this == rhs); }
};

////////////////////////////////////////////////////////////////////////////////

}