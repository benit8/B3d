/*
** B, 2019
** Rendering / MeshLoader.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class MeshLoader;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/String.hpp"
#include "B/Containers/Array.hpp"
#include "B/Containers/Vector.hpp"
#include "B/IO/Reader.hpp"
#include "B/Rendering/Mesh.hpp"
#include "B/Math/Vector3.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class MeshLoader
{
private:
	struct Face
	{
		typedef Array<i64, 3> Indexes;
		Vector<Indexes> indexes;
	};

	struct MeshBuffer
	{
		Vector<Vector3> vertices;
		Vector<Vector3> textures;
		Vector<Vector3> normals;
		Vector<Face> faces;
	};

public:
	MeshLoader(const String &filename);
	~MeshLoader() = default;

	bool loadToMesh(Mesh &);

private:
	void cleanLine(String &line);
	bool parseVertex(Reader &);
	bool parseTexture(Reader &);
	bool parseNormal(Reader &);
	bool parseFace(Reader &);
	bool buildFaces(Mesh &);

private:
	String m_filename;
	MeshBuffer m_buffer;
};

////////////////////////////////////////////////////////////////////////////////

}