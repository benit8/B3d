/*
** B, 2019
** Color.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Color;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Types.hpp"
#include "B/Containers/Vector.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

struct Color
{
	u8 r = 0;
	u8 g = 0;
	u8 b = 0;
	u8 a = 255;

	Color() = default;
	Color(u32 color);
	Color(u8 red, u8 green, u8 blue, u8 alpha = 255);

	///              [0-360]  [0-100]        [0-100]        [0-255]
	static Color HSB(u16 hue, u8 saturation, u8 brightness, u8 alpha = 255);

	u32 toInt() const;
	void inverse();
	Color inversed() const;
	Color interpolate(const Color &other, f64 factor = 0.5f) const;
	Vector<Color> getAllInterpolates(const Color &other, unsigned steps) const;

	operator u32() const { return toInt(); }
	bool operator ==(const Color &rhs) const;
	bool operator !=(const Color &rhs) const;

	static const Color Transparent;
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Magenta;
	static const Color Cyan;
	static const Color Yellow;
};

////////////////////////////////////////////////////////////////////////////////

}