/*
** B, 2019
** Graphics / Renderer.cpp
*/

#include "B/Graphics/Renderer.hpp"
#include "B/Graphics/X11.hpp"
#include "B/Graphics/Line.hpp"
#include "B/Utils/Logger.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(Surface &surface)
: m_surface(surface)
{
	if (!m_surface.init())
		throw std::runtime_error("Could not initialize render surface");

	m_projection = Matrix::projection((f64)m_surface.width() / (f64)m_surface.height());
}

Renderer::~Renderer()
{
	m_surface.fini();
}

////////////////////////////////////////////////////////////////////////////////

void Renderer::clear(const B::Color &color)
{
	XSetForeground(X11::display(), m_surface.getXContext(), color);
	XFillRectangle(X11::display(), m_surface.getXDrawable(), m_surface.getXContext(), 0, 0, m_surface.width(), m_surface.height());
}

////////////////////////////////////////////////////////////

void Renderer::print(const String &text, const Position &pos, const Color &color)
{
	XSetForeground(X11::display(), m_surface.getXContext(), color);
	XDrawString(X11::display(), m_surface.getXDrawable(), m_surface.getXContext(), pos.x, pos.y + 9, text.cStr(), text.length());
}

////////////////////////////////////////////////////////////

void Renderer::plot(const Position &pos, const Color &color)
{
	XSetForeground(X11::display(), m_surface.getXContext(), color);
	XDrawPoint(X11::display(), m_surface.getXDrawable(), m_surface.getXContext(), pos.x, pos.y);
}

////////////////////////////////////////////////////////////

void Renderer::trace(const Position &start, const Position &end, const Color &color)
{
	Vector2 pos(start);
	const Vector2 d(end - start);
	const unsigned steps = d.abs().max();
	if (steps == 0)
		return;

	const Vector2 inc = d / steps;
	for (usize i = 0; i < steps; ++i) {
		plot(pos, color);
		pos += inc;
	}
}

void Renderer::trace(const Vertex &start, const Vertex &end)
{
	if (start.color == end.color) {
		trace(start.pos, end.pos, start.color);
		return;
	}

	Vector2 pos(start.pos);
	const Vector2 d(end.pos - start.pos);
	const unsigned steps = d.abs().max();
	if (steps == 0)
		return;
	const Vector2 inc = d / steps;

	for (usize i = 0; i < steps; ++i) {
		plot(pos, start.color.interpolate(end.color, (f64)i / steps));
		pos += inc;
	}
}

void Renderer::trace(const Rect &area, const Color &color)
{
	XSetForeground(X11::display(), m_surface.getXContext(), color);
	XDrawRectangle(X11::display(), m_surface.getXDrawable(), m_surface.getXContext(), area.x(), area.y(), area.width(), area.height());
}

template <usize S>
void Renderer::trace(const Polygon<S> &area)
{
	for (usize i = 0; i < S - 1; ++i)
		trace(area.vertices[i], area.vertices[i + 1]);
	trace(area.vertices[S - 1], area.vertices[0]);
}

////////////////////////////////////////////////////////////

void Renderer::fill(const Rect &area, const Color &color)
{
	XSetForeground(X11::display(), m_surface.getXContext(), color);
	XFillRectangle(X11::display(), m_surface.getXDrawable(), m_surface.getXContext(), area.x(), area.y(), area.width(), area.height());
}

template <usize S>
void Renderer::fill(const Polygon<S> &area, const Color &color)
{
	XPoint points[S];
	for (usize i = 0; i < S; ++i)
		points[i] = {(i16)round(area.vertices[i].pos.x), (i16)round(area.vertices[i].pos.y)};

	XSetForeground(X11::display(), m_surface.getXContext(), color);
	XFillPolygon(X11::display(), m_surface.getXDrawable(), m_surface.getXContext(), points, S, Convex, CoordModeOrigin);
}

////////////////////////////////////////////////////////////////////////////////

void Renderer::beginBatch(bool clearRenderer)
{
	if (clearRenderer)
		clear();
	m_batch.clear();
}

void Renderer::addToBatch(const Triangle &triangle)
{
	auto tri = triangle;

	Vector3 lines[2] = {tri.vertices[1].pos - tri.vertices[0].pos, tri.vertices[2].pos - tri.vertices[0].pos};
	Vector3 normal = lines[0].cross(lines[1]).normalize();
	if (normal.dot(tri.vertices[0].pos - m_camera) > 0.0)
		return;

	for (auto &vtx : tri.vertices) {
		vtx.pos *= m_projection;

		// Scale to screen
		vtx.pos += {1, 1, 0};
		vtx.pos.x *= m_surface.width() / 2.0;
		vtx.pos.y *= m_surface.height() / 2.0;
	}

	m_batch.append(tri);
}

void Renderer::endBatch()
{
	if (m_batch.empty())
		return;

	m_batch.sort([] (const Triangle &a, const Triangle &b) {
		return a.midPoint().z > b.midPoint().z;
	});

	for (auto p : m_batch) {
		this->trace(p);
	}
}

////////////////////////////////////////////////////////////////////////////////

}