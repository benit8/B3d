/*
** B, 2019
** Position.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <utility>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

struct Position
{
	int x = 0;
	int y = 0;

	Position() = default;
	Position(Position &&) = default;
	Position(const Position &) = default;

	Position(int _x, int _y)
	: x(_x)
	, y(_y)
	{}

	Position &operator =(Position &&) = default;
	Position &operator =(const Position &) = default;

	bool operator ==(const Position &rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator !=(const Position &rhs) const { return !(*this == rhs); }
	Position operator +(const Position &rhs) const { return Position(x + rhs.x, y + rhs.y); }
	Position operator -(const Position &rhs) const { return Position(x - rhs.x, y - rhs.y); }
	void operator +=(const Position &rhs) { x += rhs.x; y += rhs.y; }
	void operator -=(const Position &rhs) { x -= rhs.x; y -= rhs.y; }
};

// Alias to prevent verbosity
using Pos = Position;

////////////////////////////////////////////////////////////////////////////////

class Positionable
{
public:
	Positionable() = default;
	virtual ~Positionable() = default;

	Positionable(Position &&position)
	: m_position(std::move(position))
	{}

	Positionable(const Position &position)
	: m_position(position)
	{}

	Positionable(int x, int y)
	: m_position(x, y)
	{}

	int x() const { return position().x; }
	int y() const { return position().y; }
	virtual const Position &position() const { return m_position; }

	void setX(int x) { setPosition(x, y()); }
	void setY(int y) { setPosition(x(), y); }
	void setPosition(int x, int y) { setPosition(Position(x, y)); }
	virtual void setPosition(const Position &pos) { m_position = pos; }

	void move(int x, int y) { move(Position(x, y)); }
	void move(const Position &pos) { setPosition(m_position + pos); }

protected:
	Position m_position;
};

}