/*
** B, 2019
** Graphics / Keyboard.cpp
*/

#include "B/Graphics/Event.hpp"
#include "B/Graphics/Keyboard.hpp"

#include <X11/Xutil.h>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

static const struct
{
	KeySym keysym;
	Keyboard::Key key;
}
KeySymToKey[] = {
	{XK_Shift_L, "lshift"},
	{XK_Shift_R, "rshift"},
	{XK_Control_L, "lcontrol"},
	{XK_Control_R, "rcontrol"},
	{XK_Caps_Lock, "capslock"},
	{XK_Alt_L, "lalt"},
	{XK_Alt_R, "ralt"},
	{XK_Super_L, "lsuper"},
	{XK_Super_R, "rsuper"},
	{XK_Hyper_L, "lhyper"},
	{XK_Hyper_R, "rhyper"},

	{XK_Menu, "menu"},
	{XK_ISO_Level3_Shift, "altgr"},
	{XK_Scroll_Lock, "scrolllock"},
	{XK_Num_Lock, "numlock"},
	{XK_Escape, "escape"},
	{XK_space, "space"},
	{XK_Return, "return"},
	{XK_BackSpace, "backspace"},
	{XK_Tab, "tab"},
	{XK_Prior, "pageup"},
	{XK_Next, "pagedown"},
	{XK_End, "end"},
	{XK_Home, "home"},
	{XK_Print, "print"},
	{XK_Insert, "insert"},
	{XK_Delete, "delete"},
	{XK_KP_Add, "add"},
	{XK_KP_Subtract, "subtract"},
	{XK_KP_Multiply, "multiply"},
	{XK_KP_Divide, "divide"},
	{XK_Pause, "pause"},
	{XK_Left, "left"},
	{XK_Up, "up"},
	{XK_Down, "down"},
	{XK_Right, "right"},
	{XK_KP_Insert, "insert"},
	{XK_KP_End, "end"},
	{XK_KP_Down, "down"},
	{XK_KP_Page_Down, "pagedown"},
	{XK_KP_Left, "left"},
	{XK_KP_Begin, "begin"},
	{XK_KP_Right, "right"},
	{XK_KP_Home, "home"},
	{XK_KP_Up, "up"},
	{XK_KP_Page_Up, "pageup"},
	{XK_KP_Enter, "return"},
	{XK_KP_Delete, "delete"},

	{XK_F1, "f1"},
	{XK_F2, "f2"},
	{XK_F3, "f3"},
	{XK_F4, "f4"},
	{XK_F5, "f5"},
	{XK_F6, "f6"},
	{XK_F7, "f7"},
	{XK_F8, "f8"},
	{XK_F9, "f9"},
	{XK_F10, "f10"},
	{XK_F11, "f11"},
	{XK_F12, "f12"},
	{XK_F13, "f13"},
	{XK_F14, "f14"},
	{XK_F15, "f15"},

	{NoSymbol, NULL}
};

////////////////////////////////////////////////////////////////////////////////

static KeySym lookupKeysymToBuffer(XKeyEvent &xkey, String &buffer)
{
	static XComposeStatus status;
	char symBuf[8] = {0};
	KeySym sym = NoSymbol;

	XLookupString(&xkey, symBuf, sizeof(symBuf), &sym, &status);

	for (size_t i = 0; KeySymToKey[i].keysym != NoSymbol; ++i) {
		if (KeySymToKey[i].keysym == sym) {
			buffer += KeySymToKey[i].key;
			return sym;
		}
	}

	buffer += symBuf;
	return sym;
}

void Keyboard::eventFromX11Event(XKeyEvent &xkey, KeyEvent &e)
{
	e.mods = static_cast<Modifiers>(xkey.state);

	xkey.state &= ~(ControlMask | Mod1Mask | Mod4Mask);
	KeySym sym = lookupKeysymToBuffer(xkey, e.key);

	// If the key is a modifier we only fetch its symbol and don't do anything
	// about the combination. A comb like "control rshift" is not relevant.
	if ((XK_Shift_L <= sym && sym <= XK_Hyper_R) || (XK_ISO_Lock <= sym && sym <= XK_ISO_Last_Group_Lock))
		return;


	if (e.mods & Ctrl)  e.comb += "control ";
	if (e.mods & Shift) e.comb += "shift ";
	if (e.mods & Alt)   e.comb += "alt ";
	if (e.mods & AltGr) e.comb += "altgr ";
	if (e.mods & Super) e.comb += "super ";

	xkey.state &= ~(ShiftMask | Mod5Mask);
	lookupKeysymToBuffer(xkey, e.comb);

	// If the comb ends with a space, this means that no keysym was written to
	// the buffer and there's only modifiers in it.
	e.comb.trimRight();
}

////////////////////////////////////////////////////////////////////////////////

}