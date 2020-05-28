/*
** B, 2019
** Graphics / Renderable.hpp
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
 * Used to render 3D stuff
 */

class Renderable
{
public:
	virtual ~Renderable() = default;

	virtual void render(Renderer &renderer) const = 0;

protected:
	friend class Renderer;
};

}