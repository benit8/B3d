/*
** B, 2019
** Rendering / Mesh.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Mesh;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/String.hpp"
#include "B/Containers/Vector.hpp"
#include "B/Graphics/Renderable.hpp"
#include "B/Graphics/Renderer.hpp"
#include "B/Rendering/Polygon.hpp"
#include "B/Rendering/MeshLoader.hpp"
#include "B/Rendering/Transformable.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

/*
 * The mesh represents a 3D model.
 * It is composed of 'faces' (typicaly triangles) that makes up its surface.
 * It can be textured and transformed.
 */

class Mesh : public Transformable, public Renderable
{
public:
	Mesh() = default;
	virtual ~Mesh() = default;

	bool loadFromFile(const String &filename);
	void render(Renderer &target) const;

	const Vector<Triangle> &faces() const { return m_faces; }

private:
	Vector<Triangle> m_faces;

	friend class MeshLoader;
};

////////////////////////////////////////////////////////////////////////////////

}