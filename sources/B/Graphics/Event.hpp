/*
** B, 2019
** Graphics / Event.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	struct Event;

	struct WindowEvent;
	struct KeyEvent;
	struct MouseEvent;
	struct MouseButtonEvent;
	struct MouseWheelEvent;
	struct MouseMoveEvent;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/String.hpp"
#include "B/Position.hpp"
#include "B/Size.hpp"
#include "B/Graphics/Mouse.hpp"
#include "B/Graphics/Keyboard.hpp"
#include "B/Utils/EventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

struct Event
{
	enum Type
	{
		NoEvent = 0,
		Close,
		Resize,
		Move,
		Focused,
		Unfocused,
		KeyDown,
		KeyUp,
		MouseMove,
		MouseScroll,
		MouseDown,
		MouseUp,
		MouseIn,
		MouseOut,
	};

public:
	Event() = default;
	~Event() = default;

	Event(Type t)
	: type(t)
	{}

	Type type = NoEvent;
};

struct WindowEvent : public Event
{
	WindowEvent(Event::Type t)
	: Event(t)
	{}

	Position position; // Window position
	Size size;         // Window resize
};

struct KeyEvent : public Event
{
	KeyEvent(Event::Type t)
	: Event(t)
	{}

	Keyboard::Modifiers mods = Keyboard::Modifiers::NoMod; // Mask containing Ctrl, Shift, Alt, System keys states
	String key;                                            // Representation of the key (eg. "a", "0", "return")
	String comb;                                           // Key combination (eg. "control shift space")

	inline bool noMods() const { return mods == Keyboard::Modifiers::NoMod; }
	inline bool ctrl()   const { return mods & Keyboard::Modifiers::Ctrl; }
	inline bool caps()   const { return mods & Keyboard::Modifiers::Caps; }
	inline bool shift()  const { return mods & Keyboard::Modifiers::Shift; }
	inline bool alt()    const { return mods & Keyboard::Modifiers::Alt; }
	inline bool num()    const { return mods & Keyboard::Modifiers::Num; }
	inline bool scroll() const { return mods & Keyboard::Modifiers::Scroll; }
	inline bool super()  const { return mods & Keyboard::Modifiers::Super; }
	inline bool altgr()  const { return mods & Keyboard::Modifiers::AltGr; }
};

struct MouseEvent : public Event
{
	MouseEvent(Event::Type t)
	: Event(t)
	{}

	Position position; // Mouse position
};

struct MouseButtonEvent : public MouseEvent
{
	MouseButtonEvent(Event::Type t)
	: MouseEvent(t)
	{}

	Mouse::Button button = Mouse::NoButton; // Mouse button
};

struct MouseWheelEvent : public MouseEvent
{
	MouseWheelEvent(Event::Type t)
	: MouseEvent(t)
	{}

	Mouse::Wheel wheel = Mouse::NoWheel; // Mouse wheel type
	i8 delta           = 0;              // Mouse wheel direction
};

struct MouseMoveEvent : public MouseEvent
{
	MouseMoveEvent()
	: MouseEvent(Event::MouseMove)
	{}

	Position diff; // Mouse movement difference
};

////////////////////////////////////////////////////////////////////////////////

}