/*
** B, 2019
** Rendering / Vertex.cpp
*/

#include "B/Rendering/Vertex.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

Vertex::Vertex()
: color(Color::White)
{}

Vertex::Vertex(const Vector3 &p)
: pos(p)
, color(Color::White)
{}

Vertex::Vertex(const Vector3 &p, const Color &c)
: pos(p)
, color(c)
{}

Vertex::Vertex(const Vector3 &p, const Color &c, const Vector3 &t)
: pos(p)
, color(c)
, tex(t)
{}

Vertex::Vertex(const Vector3 &p, const Color &c, const Vector3 &t, const Vector3 &n)
: pos(p)
, color(c)
, tex(t)
, norm(n)
{}

////////////////////////////////////////////////////////////////////////////////

}