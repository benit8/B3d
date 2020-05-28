/*
** B, 2019
** SimpleApplication.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class SimpleApplication;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/String.hpp"
#include "B/Containers/Vector.hpp"
#include "B/Graphics/Window.hpp"
#include "B/Graphics/Renderer.hpp"
#include "B/Utils/EventListener.hpp"

#include <memory>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class SimpleApplication
{
public:
	SimpleApplication() = default;
	~SimpleApplication();

	int run();
	bool running() const { return m_running; }
	void close() { m_running = false; }

	std::shared_ptr<Window> createWindow(const Size &, const String &);
	std::shared_ptr<Renderer> createRenderer(Surface &);

	std::shared_ptr<Window> window() const { return m_window; }
	std::shared_ptr<Renderer> renderer() const { return m_renderer; }

	// std::shared_ptr<Window> addWindow(const Size &size, const String &title);
	// std::shared_ptr<Window> window(unsigned i = 0) const;

	Signal<> onCreate;
	Signal<f64&> onUpdate;
	Signal<f64&> onStaticUpdate;
	Signal<std::shared_ptr<Renderer>> onRender;
	Signal<> onDestroy;

private:
	std::shared_ptr<Window> m_window;
	std::shared_ptr<Renderer> m_renderer;
	bool m_running = false;

	const f64 m_frameTime = 1.0 / 60.0;
};

////////////////////////////////////////////////////////////////////////////////

}