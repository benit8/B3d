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
// #include "B/IO/Reader.hpp"
#include "B/Rendering/Mesh.hpp"
#include "B/Math/Vector3.hpp"

#include <fstream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class MeshLoader
{
private:
	struct Face
	{
		typedef Array<i64,3> Indexes;
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

	bool loadToMesh(Mesh &mesh);

private:
	void cleanLine(std::string &line);
	bool parseVertex(std::istringstream &stream);
	bool parseTexture(std::istringstream &stream);
	bool parseNormal(std::istringstream &stream);
	bool parseFace(std::istringstream &stream);
	bool buildFaces(Mesh &mesh);

private:
	String m_filename;
	MeshBuffer m_buffer;
};

////////////////////////////////////////////////////////////////////////////////

}