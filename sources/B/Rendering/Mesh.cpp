/*
** B, 2019
** Rendering / Mesh.cpp
*/

#include "B/Rendering/Mesh.hpp"
#include "B/Graphics/Line.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

bool Mesh::loadFromFile(const String &filename)
{
	MeshLoader loader(filename);
	return loader.loadToMesh(*this);
}

void Mesh::render(Renderer &renderer) const
{
	for (auto face : m_faces) {
		// Apply tranformations
		Triangle tri = face;
		for (auto &vtx : tri.vertices)
			this->transform(vtx.pos);

		renderer.addToBatch(tri);
	}
}

////////////////////////////////////////////////////////////////////////////////

}