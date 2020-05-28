/*
** B, 2019
** Graphics / X11.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xdbe.h>

////////////////////////////////////////////////////////////////////////////////

namespace X11
{
	typedef ::Atom Atom;
	typedef ::Display Display;
	typedef ::Drawable Drawable;
	typedef ::GC GC;
	typedef ::Window Window;

	////////////////////////////////////////////////////////////

	X11::Display *display();
	int screen();
};