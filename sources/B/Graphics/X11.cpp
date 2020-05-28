/*
** B, 2019
** Graphics / X11.cpp
*/

#include "B/Graphics/X11.hpp"

#include <cassert>

////////////////////////////////////////////////////////////////////////////////

X11::Display *X11::display()
{
	static X11::Display *connection = nullptr;

	if (connection == nullptr) {
		connection = XOpenDisplay(NULL);
		assert(connection != nullptr);
	}

	return connection;
}

int X11::screen()
{
	return DefaultScreen(X11::display());
}