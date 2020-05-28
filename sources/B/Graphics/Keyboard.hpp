/*
** B, 2019
** Graphics / Keyboard.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Keyboard;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Graphics/Event.hpp"

#include <X11/Xlib.h>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class Keyboard
{
public:
	/*
	 *  Mask        | Value | Key
	 *  ------------+-------+------------
	 *  ShiftMask   |  0x01 | Shift
	 *  LockMask    |  0x02 | Caps Lock
	 *  ControlMask |  0x04 | Ctrl
	 *  Mod1Mask    |  0x08 | Alt
	 *  Mod2Mask    |  0x10 | Num Lock
	 *  Mod3Mask    |  0x20 | Scroll Lock
	 *  Mod4Mask    |  0x40 | Windows
	 *  Mod5Mask    |  0x80 | Alt Gr
	 */
	enum Modifiers
	{
		NoMod  = 0,
		Ctrl   = ControlMask,
		Caps   = LockMask,
		Shift  = ShiftMask,
		Alt    = Mod1Mask,
		Num    = Mod2Mask,
		Scroll = Mod3Mask,
		Super  = Mod4Mask,
		AltGr  = Mod5Mask
	};

	typedef const char * Key;

	static void eventFromX11Event(XKeyEvent &xkey, KeyEvent &e);
	friend class Window;
};

////////////////////////////////////////////////////////////////////////////////

}