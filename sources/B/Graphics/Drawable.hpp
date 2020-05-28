/*
** B, 2019
** Graphics / Drawable.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Renderer;
}

////////////////////////////////////////////////////////////////////////////////

namespace B
{

/*
 * Used to draw 2D stuff
 */

class Drawable
{
public:
	virtual ~Drawable() = default;

	virtual void draw(Renderer &renderer) const = 0;

protected:
	friend class Renderer;
};

}