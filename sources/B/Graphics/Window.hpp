/*
** B, 2019
** Graphics / Window.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Window;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Color.hpp"
#include "B/Position.hpp"
#include "B/String.hpp"
#include "B/Graphics/Event.hpp"
#include "B/Graphics/Surface.hpp"
#include "B/Graphics/X11.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class Window : public Surface, public Positionable
{
public:
	Window();
	Window(const Size &size, const String &title);
	~Window();

	bool open(const Size &size, const String &title);
	bool open() const { return m_opened; }
	void close();
	void refresh();
	// void resize(const Size &size);
	// void move(const Position &size) override;
	// void toggleFullscreen();
	// void fullscreen(bool f);
	// bool fullscreen() const;
	void title(const String &title);
	const String &title() const { return m_title; }

	void dispatchEvents();

	/// Inherited from Surface
	bool init();
	void fini();
	const X11::Drawable &getXDrawable() const { return m_XBackBuffer; }
	const X11::GC &getXContext() const { return m_XGraphicContext; }

	Signal<> onClose;
	Signal<> onFocused;
	Signal<> onUnfocused;
	Signal<const WindowEvent &> onResize;
	Signal<const WindowEvent &> onMove;
	Signal<const KeyEvent &> onKeyDown;
	Signal<const KeyEvent &> onKeyUp;
	Signal<const MouseEvent &> onMouseIn;
	Signal<const MouseEvent &> onMouseOut;
	Signal<const MouseButtonEvent &> onMouseDown;
	Signal<const MouseButtonEvent &> onMouseUp;
	Signal<const MouseWheelEvent &> onMouseScroll;
	Signal<const MouseMoveEvent &> onMouseMove;

private:
	void initX11StaticData();
	void processX11Event(XEvent &xe);

private:
	static unsigned Instances;

	String m_title;
	bool m_opened;
	bool m_fullscreen;

	/// X11
	static int XScreen;
	static XVisualInfo XVisualInfos;

	X11::Window m_XWindow;
	Colormap m_XColormap;
	X11::GC m_XGraphicContext;
	XdbeBackBuffer m_XBackBuffer;
	XdbeSwapInfo m_XSwapInfos;

	X11::Atom m_wmProtocols;
	X11::Atom m_wmDeleteWindow;
	X11::Atom m_wmPing;
};

////////////////////////////////////////////////////////////////////////////////

}