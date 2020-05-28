/*
** B, 2019
** SimpleApplication.cpp
*/

#include "B/SimpleApplication.hpp"
#include "B/Platform/Time.hpp"
#include <cassert>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

SimpleApplication::~SimpleApplication()
{
	if (m_window && m_window->open())
		m_window->close();
}

////////////////////////////////////////////////////////////////////////////////

int SimpleApplication::run()
{
	onCreate.emit();
	if (!m_window)
		throw std::logic_error("You must instanciate a window in the onCreate signal");

	m_running = true;

	f64 updateTimer = 0;
	f64 last = getTime();
	while (running() && m_window->open()) {
		f64 now = getTime();
		f64 elapsed = now - last;
		last = now;

		updateTimer += elapsed;
		onUpdate.emit(elapsed);

		bool shouldRender = false;
		while (updateTimer >= m_frameTime) {
			m_window->dispatchEvents();
			onStaticUpdate.emit(elapsed);
			updateTimer -= m_frameTime;
			shouldRender = true;
		}

		if (shouldRender) {
			m_renderer->beginBatch();
			onRender.emit(m_renderer);
			m_renderer->endBatch();
			m_window->refresh();
		}
	}

	onDestroy.emit();

	return EXIT_SUCCESS;
}


std::shared_ptr<Window> SimpleApplication::createWindow(const Size &size, const String &title)
{
	if (!m_window || !m_window->open())
		m_window = std::make_shared<Window>(size, title);
	return m_window;
}

std::shared_ptr<Renderer> SimpleApplication::createRenderer(Surface &target)
{
	if (!m_renderer)
		m_renderer = std::make_shared<Renderer>(target);
	return m_renderer;
}

////////////////////////////////////////////////////////////////////////////////

}