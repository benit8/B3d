/*
** B, 2019
** Rendering / MeshLoader.cpp
*/

#include "B/Rendering/MeshLoader.hpp"
#include "B/String.hpp"
#include "B/StringView.hpp"
#include "B/Containers/Map.hpp"
#include "B/Utils/Logger.hpp"

#include <cctype>
#include <functional>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

using namespace std::placeholders;

////////////////////////////////////////////////////////////////////////////////

MeshLoader::MeshLoader(const String &filename)
: m_filename(filename)
{}


bool MeshLoader::loadToMesh(Mesh &mesh)
{
	auto reader = Reader::fromFile(m_filename);
	// if (!file.is_open()) {
	// 	Logger::error("Failed to open mesh file '%$': %m\n", m_filename);
	// 	return false;
	// }

	bool hasError = false;
	String line;
	while (!hasError && reader.readLine(line)) {
		cleanLine(line);
		if (line.empty())
			continue;

		Logger::debug("%$", line);

		// Extract the line type (v, f, ...) and search for a parser bound to it
		auto lineReader = Reader::fromString(line);
		String type;
		lineReader >> type;

		bool ok = false;
		/**/ if (type == "v")  ok = parseVertex(lineReader);
		else if (type == "vt") ok = parseTexture(lineReader);
		else if (type == "vn") ok = parseNormal(lineReader);
		else if (type == "f")  ok = parseFace(lineReader);
		else {
			Logger::warn("Un-parsed line type '%$'", type);
			continue;
		}

		if (!ok) {
			hasError = true;
			break;
		}
	}

	return hasError ? false : buildFaces(mesh);
}


void MeshLoader::cleanLine(String &s)
{
	// Search for a comment and erase from it to end of the line
	usize p = s.findOf("#");
	if (p != String::nPos)
		s.erase(p);

	s.trim();
}

bool MeshLoader::parseVertex(Reader &reader)
{
	Vector3 v;
	reader >> v.x >> v.y >> v.z;

	m_buffer.vertices.append(v);
	return true;
}

bool MeshLoader::parseTexture(Reader &reader)
{
	Vector3 t;
	reader >> t.x >> t.y >> t.z;

	m_buffer.textures.append(t);
	return true;
}

bool MeshLoader::parseNormal(Reader &reader)
{
	Vector3 n;
	reader >> n.x >> n.y >> n.z;

	m_buffer.normals.append(n);
	return true;
}

bool MeshLoader::parseFace(Reader &reader)
{
	Face face;

	do {
		Face::Indexes indexes = {0};

		/// Geometric vertex index
		reader >> indexes[0];
		Logger::debug("%$", indexes[0]);
		if (!reader.peek('/'))
			goto cont;
		reader.ignore();

		// Vertex texture index ?
		if (!reader.peek('/')) {
			reader >> indexes[1];
		}
		else {
			reader.ignore();
			reader >> indexes[2];
			goto cont;
		}

		// Vertex normal index ?
		if (reader.peek('/')) {
			reader.ignore();
			reader >> indexes[2];
		}

cont:
		face.indexes.append(indexes);
	} while (!reader.eof());

	m_buffer.faces.append(face);
	return true;
}

bool MeshLoader::buildFaces(Mesh &mesh)
{
	mesh.m_faces.clear();

	for (auto bFace : m_buffer.faces) {
		Triangle tri;

		for (usize i = 0; i < bFace.indexes.size(); ++i) {
			/// Remember that indices starts at 1
			int iv  = bFace.indexes[i][0];  // vertex position index
			int ivt = bFace.indexes[i][1];  // vertex texture index
			int ivn = bFace.indexes[i][2];  // vertex normal index
			Vertex vertex;

			if (iv < 0)
				iv += m_buffer.vertices.size() + 1;
			if ((usize)iv > m_buffer.vertices.size()) {
				eprint("%$: Invalid vertex normal index: %$\n", m_filename, iv);
				break;
			}
			else if (iv != 0) {
				vertex.pos = m_buffer.vertices[iv - 1];
			}

			if (ivt < 0)
				ivt += m_buffer.textures.size() + 1;
			if ((usize)ivt > m_buffer.textures.size()) {
				eprint("%$: Invalid vertex normal index: %$\n", m_filename, ivt);
				break;
			}
			else if (ivt != 0) {
				vertex.tex = m_buffer.textures[ivt - 1];
			}

			if (ivn < 0)
				ivn += m_buffer.normals.size() + 1;
			if ((usize)ivn > m_buffer.normals.size()) {
				eprint("%$: Invalid vertex normal index: %$\n", m_filename, ivn);
				break;
			}
			else if (ivn != 0) {
				vertex.norm = m_buffer.normals[ivn - 1];
			}

			tri.vertices[i] = vertex;
		}

		mesh.m_faces.append(tri);
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////

}