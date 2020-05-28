/*
** B, 2019
** Rendering / MeshLoader.cpp
*/

#include "B/StringView.hpp"
#include "B/Containers/Map.hpp"
// #include "B/FileSystem/File.hpp"
#include "B/IO/Print.hpp"
#include "B/Rendering/MeshLoader.hpp"
#include "B/Utils/Logger.hpp"

#include <cctype>
#include <functional>
#include <unordered_map>
#include <string>

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
	static std::unordered_map<std::string, std::function<bool(std::istringstream &)>> lineTypes = {
		{"v",  std::bind(&MeshLoader::parseVertex, this, _1)},
		{"vt", std::bind(&MeshLoader::parseTexture, this, _1)},
		{"vn", std::bind(&MeshLoader::parseNormal, this, _1)},
		{"f",  std::bind(&MeshLoader::parseFace, this, _1)}
	};


	std::ifstream file(m_filename.cStr());
	if (!file.is_open()) {
		Logger::error("Failed to open mesh file '%$': %m\n", m_filename);
		return false;
	}

	bool hasError = false;
	std::string line;
	while (!hasError && std::getline(file, line)) {
		if (line.empty())
			continue;

		cleanLine(line);

		// Extract the line type (v, f, ...) and search for a parser bound to it
		std::istringstream stream(line);
		std::string type;
		stream >> type;

		auto it = lineTypes.find(type);
		if (it != lineTypes.end()) {
			if (!it->second(stream)) {
				hasError = true;
				break;
			}
		}
	}

	file.close();

	return hasError ? false : buildFaces(mesh);
}


void MeshLoader::cleanLine(std::string &s)
{
	// Search for a comment and erase from it to end of the line
	usize p = s.find_first_of("#");
	if (p != std::string::npos)
		s.erase(p);

	// s.trim();
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
}

bool MeshLoader::parseVertex(std::istringstream &stream)
{
	Vector3 v;
	stream >> v.x >> v.y >> v.z;

	m_buffer.vertices.append(v);
	return true;
}

bool MeshLoader::parseTexture(std::istringstream &stream)
{
	Vector3 t;
	stream >> t.x >> t.y >> t.z;

	m_buffer.textures.append(t);
	return true;
}

bool MeshLoader::parseNormal(std::istringstream &stream)
{
	Vector3 n;
	stream >> n.x >> n.y >> n.z;

	m_buffer.normals.append(n);
	return true;
}

bool MeshLoader::parseFace(std::istringstream &stream)
{
	Face face;

	do {
		Face::Indexes indexes = {0};

		/// Geometric vertex index
		stream >> indexes[0];
		if (stream.peek() != '/')
			goto cont;
		stream.ignore(1, '/');

		// Vertex texture index ?
		if (stream.peek() != '/') {
			stream >> indexes[1];
		}
		else {
			stream.ignore(1, '/');
			stream >> indexes[2];
			goto cont;
		}

		// Vertex normal index ?
		if (stream.peek() == '/') {
			stream.ignore(1, '/');
			stream >> indexes[2];
		}

cont:
		face.indexes.append(indexes);
		stream.ignore(1L << 12, ' ');
	} while (stream);

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
			if (iv > (int)m_buffer.vertices.size()) {
				eprint("%$: Invalid vertex normal index: %$\n", m_filename, iv);
				break;
			}
			else if (iv != 0) {
				vertex.pos = m_buffer.vertices[iv - 1];
			}

			if (ivt < 0)
				ivt += m_buffer.textures.size() + 1;
			if (ivt > (int)m_buffer.textures.size()) {
				eprint("%$: Invalid vertex normal index: %$\n", m_filename, ivt);
				break;
			}
			else if (ivt != 0) {
				vertex.tex = m_buffer.textures[ivt - 1];
			}

			if (ivn < 0)
				ivn += m_buffer.normals.size() + 1;
			if (ivn > (int)m_buffer.normals.size()) {
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