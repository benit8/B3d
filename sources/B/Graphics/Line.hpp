/*
** B, 2019
** Graphics / Line.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Line;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Position.hpp"
#include "B/Color.hpp"
#include "B/Graphics/Drawable.hpp"
#include "B/Graphics/Renderer.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class Line : public Drawable
{
public:
	Line() = default;
	Line(const Position &s, const Position &e);
	Line(const Position &s, const Position &e, const Color &c);
	~Line() = default;

public:
	void draw(Renderer &renderer) const;

public:
	Position start, end;
	Color color = Color::White;
};

////////////////////////////////////////////////////////////////////////////////

}