/*
** B, 2019
** Graphics / Renderer.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Surface;
	class Renderer;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Color.hpp"
#include "B/Position.hpp"
#include "B/Rect.hpp"
#include "B/String.hpp"
#include "B/Containers/Vector.hpp"
#include "B/Graphics/Drawable.hpp"
#include "B/Graphics/Renderable.hpp"
#include "B/Graphics/Surface.hpp"
#include "B/Math/Matrix.hpp"
#include "B/Rendering/Polygon.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class Renderer
{
public:
	Renderer(Surface &surface);
	~Renderer();

public:
	void clear(const Color &color = Color::Black);

	/// Text rendering functions
	void print(const String &text, const Position &pos, const Color &color = Color::White);

	/// Pixel rendering functions
	void plot(const Position &pos, const Color &color = Color::White);

	/// Un-filled simple rendering functions
	void trace(const Position &start, const Position &end, const Color &color = Color::White);
	void trace(const Vertex &start, const Vertex &end);
	void trace(const Rect &area, const Color &color = Color::White);
	template <usize S>
	void trace(const Polygon<S> &area);

	/// Filled simple rendering functions
	void fill(const Rect &area, const Color &color = Color::White);
	template <usize S>
	void fill(const Polygon<S> &area, const Color &color = Color::White);


	/*
	** Terminology:
	** We use 'draw' for 2d stuff, and 'render' for 3d stuff
	*/

	// Custom element drawing/rendering
	void draw(const Drawable &drawable) { drawable.draw(*this); }
	void render(const Renderable &renderable) { renderable.render(*this); }

	void beginBatch(bool clear = true);
	void addToBatch(const Triangle &polygon);
	void endBatch();


	const Surface &surface() const { return m_surface; }
	const Matrix &worldProjection() const { return m_projection; }
	// const Camera &worldCamera() const { return m_camera; }

private:
	Surface &m_surface;
	Vector<Triangle> m_batch;
	Matrix m_projection;
	Vector3 m_camera;
};

////////////////////////////////////////////////////////////////////////////////

}