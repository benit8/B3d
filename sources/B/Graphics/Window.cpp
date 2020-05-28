/*
** B, 2019
** Graphics / Window.cpp
*/

#include "B/Graphics/Window.hpp"

#include <cstring>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

unsigned Window::Instances = 0;
int Window::XScreen = 0;
XVisualInfo Window::XVisualInfos;

////////////////////////////////////////////////////////////////////////////////

Window::Window()
: m_title("")
, m_opened(false)
, m_fullscreen(false)
{
	this->initX11StaticData();
	Instances++;
}

Window::Window(const Size &size, const String &title)
: m_title(title)
, m_opened(false)
, m_fullscreen(false)
{
	this->initX11StaticData();

	if (!this->open(size, title))
		throw std::runtime_error("Could not create window");

	Instances++;
}

Window::~Window()
{
	this->close();

	Instances--;
	if (Instances == 0) {
		XCloseDisplay(X11::display());
	}
}

////////////////////////////////////////////////////////////////////////////////

bool Window::open(const Size &dimensions, const String &title)
{
	if (m_opened)
		return true;

	this->setSize(dimensions);

	m_XColormap = XCreateColormap(X11::display(), RootWindow(X11::display(), XVisualInfos.screen), XVisualInfos.visual, AllocNone);

	XSetWindowAttributes attr;
	attr.background_pixel = 0xFF000000;
	attr.border_pixel = 0;
	attr.event_mask = FocusChangeMask | ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | EnterWindowMask | LeaveWindowMask;
	attr.colormap = m_XColormap;

	m_XWindow = XCreateWindow(X11::display(), RootWindow(X11::display(), XVisualInfos.screen), 0, 0, width(), height(), 0, XVisualInfos.depth, InputOutput, XVisualInfos.visual, CWBackPixel | CWBorderPixel | CWColormap | CWEventMask, &attr);
	if (!m_XWindow)
		return false;

	this->title(title);

	// Atoms
	X11::Atom atoms[3];
	atoms[0] = m_wmProtocols = XInternAtom(X11::display(), "WM_PROTOCOLS", False);
	atoms[1] = m_wmDeleteWindow = XInternAtom(X11::display(), "WM_DELETE_WINDOW", False);
	atoms[2] = m_wmPing = XInternAtom(X11::display(), "_NET_WM_PING", True);
	XSetWMProtocols(X11::display(), m_XWindow, &atoms[0], 3);


	// Double buffer
	m_XBackBuffer = XdbeAllocateBackBufferName(X11::display(), m_XWindow, XdbeCopied);
	m_XSwapInfos.swap_window = m_XWindow;
	m_XSwapInfos.swap_action = XdbeCopied;

	// Display window to screen
	XMapWindow(X11::display(), m_XWindow);
	XSync(X11::display(), False);
	m_opened = true;

	XFlush(X11::display());

	return true;
}

void Window::close()
{
	if (!m_opened)
		return;

	XUnmapWindow(X11::display(), m_XWindow);
	m_opened = false;

	// Surface::stop();
	XdbeDeallocateBackBufferName(X11::display(), m_XBackBuffer);
	XFreeColormap(X11::display(), m_XColormap);
	XDestroyWindow(X11::display(), m_XWindow);
}

void Window::refresh()
{
	XdbeBeginIdiom(X11::display());
	XdbeSwapBuffers(X11::display(), &m_XSwapInfos, 1);
	XdbeEndIdiom(X11::display());
	XFlush(X11::display());
}

void Window::title(const String &title)
{
	if (!m_opened)
		return;

	XStoreName(X11::display(), m_XWindow, title.cStr());
	m_title = title;
}

////////////////////////////////////////////////////////////////////////////////

void Window::dispatchEvents()
{
	while (m_opened && XPending(X11::display()) > 0) {
		XEvent xe;
		XNextEvent(X11::display(), &xe);
		this->processX11Event(xe);
	}
}

////////////////////////////////////////////////////////////////////////////////

bool Window::init()
{
	m_XGraphicContext = XCreateGC(X11::display(), m_XWindow, 0, NULL);

	XSetBackground(X11::display(), m_XGraphicContext, 0xFF000000);
	XSetForeground(X11::display(), m_XGraphicContext, 0xFFFFFFFF);
	XSetFillStyle(X11::display(), m_XGraphicContext, FillSolid);
	XSetLineAttributes(X11::display(), m_XGraphicContext, 1, LineSolid, CapButt, JoinBevel);

	XFlush(X11::display());
	return true;
}

void Window::fini()
{
	XFreeGC(X11::display(), m_XGraphicContext);
}

////////////////////////////////////////////////////////////////////////////////

void Window::initX11StaticData()
{
	if (XMatchVisualInfo(X11::display(), X11::screen(), 32, TrueColor, &XVisualInfos) == 0)
		throw std::runtime_error("Failed to match visual infos");
}

void Window::processX11Event(XEvent &xe)
{
	switch (xe.type)
	{
		// Close button / Ping from WM
		case ClientMessage:
		{
			if (xe.xclient.message_type == m_wmProtocols) {
				if (xe.xclient.format == 32 && xe.xclient.data.l[0] == (long)m_wmDeleteWindow) {
					onClose.emit();
				}
				else if (m_wmPing != None && xe.xclient.format == 32 && xe.xclient.data.l[0] == (long)m_wmPing) {
					xe.xclient.window = DefaultRootWindow(X11::display());
					// Reply to ping
					XSendEvent(X11::display(), DefaultRootWindow(X11::display()), False, SubstructureNotifyMask | SubstructureRedirectMask, &xe);
				}
			}
			break;
		}

		// Resize/Move event
		case ConfigureNotify:
		{
			// Resized
			if ((unsigned)xe.xconfigure.width != width() || (unsigned)xe.xconfigure.height != height()) {
				WindowEvent e(Event::Resize);
				e.size.width = xe.xconfigure.width;
				e.size.height = xe.xconfigure.height;
				this->setSize(e.size);
				onResize.emit(e);
			}
			// Moved
			else if (xe.xconfigure.x != x() || xe.xconfigure.y != y()) {
				WindowEvent e(Event::Move);
				e.position.x = xe.xconfigure.x;
				e.position.y = xe.xconfigure.y;
				this->setPosition(e.position);
				onMove.emit(e);
			}
			break;
		}

		case FocusIn:
		{
			// Event e(Event::Focused);
			onFocused.emit(/*e*/);

			// Remove urgency (notification) flag from hints
			XWMHints *hints = XGetWMHints(X11::display(), m_XWindow);
			if (hints != NULL) {
				hints->flags &= ~XUrgencyHint;
				XSetWMHints(X11::display(), m_XWindow, hints);
				XFree(hints);
			}

			break;
		}

		case FocusOut:
		{
			// Event e(Event::Unfocused);
			onUnfocused.emit(/*e*/);
			break;
		}

		case KeyPress:
		{
			KeyEvent e(Event::KeyDown);
			Keyboard::eventFromX11Event(xe.xkey, e);
			onKeyDown.emit(e);
			break;
		}

		case KeyRelease:
		{
			KeyEvent e(Event::KeyUp);
			Keyboard::eventFromX11Event(xe.xkey, e);
			onKeyUp.emit(e);
			break;
		}

		case ButtonPress:
		{
			switch (xe.xbutton.button) {
				case 1: case 2: case 3: case 8: case 9: {
					MouseButtonEvent e(Event::MouseDown);
					e.position = {xe.xbutton.x, xe.xbutton.y};
					e.button = static_cast<Mouse::Button>(xe.xbutton.button);
					onMouseDown.emit(e);
					break;
				}
				case 4: case 5: {
					MouseWheelEvent e(Event::MouseScroll);
					e.position = {xe.xbutton.x, xe.xbutton.y};
					e.wheel = Mouse::Vertical;
					e.delta = (xe.xbutton.button == 4) ? 1 : -1;
					onMouseScroll.emit(e);
					break;
				}
				case 6: case 7: {
					MouseWheelEvent e(Event::MouseScroll);
					e.position = {xe.xbutton.x, xe.xbutton.y};
					e.wheel = Mouse::Horizontal;
					e.delta = (xe.xbutton.button == 7) ? 1 : -1;
					onMouseScroll.emit(e);
					break;
				}
				default:
					break;
			}
			break;
		}

		case ButtonRelease:
		{
			switch (xe.xbutton.button) {
				case 1: case 2: case 3: case 8: case 9: {
					MouseButtonEvent e(Event::MouseUp);
					e.position = {xe.xbutton.x, xe.xbutton.y};
					e.button = static_cast<Mouse::Button>(xe.xbutton.button);
					onMouseUp.emit(e);
					break;
				}
			}
			break;
		}

		case MotionNotify:
		{
			static Position lastPos;
			if (lastPos.x == xe.xmotion.x && lastPos.y == xe.xmotion.y)
				break;

			MouseMoveEvent e;
			e.position = {xe.xmotion.x, xe.xmotion.y};
			e.diff = e.position - lastPos;
			onMouseMove.emit(e);

			lastPos = e.position;
			break;
		}

		case EnterNotify:
		{
			if (xe.xcrossing.mode == NotifyNormal) {
				MouseEvent e(Event::MouseIn);
				e.position = {xe.xcrossing.x, xe.xcrossing.y};
				onMouseIn.emit(e);
			}
			break;
		}

		case LeaveNotify:
		{
			if (xe.xcrossing.mode == NotifyNormal) {
				MouseEvent e(Event::MouseOut);
				e.position = {xe.xcrossing.x, xe.xcrossing.y};
				onMouseOut.emit(e);
			}
			break;
		}

	}
}

////////////////////////////////////////////////////////////////////////////////

}