/*
** B, 2019
** Color.cpp
*/

#include "B/Color.hpp"

#include <cfloat>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

const Color Color::Transparent(  0,   0,   0,   0);
const Color Color::Black      (  0,   0,   0, 255);
const Color Color::White      (255, 255, 255, 255);
const Color Color::Red        (255,   0,   0, 255);
const Color Color::Green      (  0, 255,   0, 255);
const Color Color::Blue       (  0,   0, 255, 255);
const Color Color::Magenta    (255,   0, 255, 255);
const Color Color::Yellow     (255, 255,   0, 255);
const Color Color::Cyan       (  0, 255, 255, 255);

////////////////////////////////////////////////////////////////////////////////

Color::Color(u32 color)
: r((color & 0x00FF0000) >> 16)
, g((color & 0x0000FF00) >> 8)
, b((color & 0x000000FF))
, a((color & 0xFF000000) >> 24)
{}

Color::Color(u8 red, u8 green, u8 blue, u8 alpha)
: r(red)
, g(green)
, b(blue)
, a(alpha)
{}


u32 Color::toInt() const
{
	return a << 24 | r << 16 | g << 8 | b;
}

Color &Color::inverse()
{
	this->r = 255 - this->r;
	this->g = 255 - this->g;
	this->b = 255 - this->b;
	return *this;
}

Color Color::inversed() const
{
	return Color(
		255 - this->r,
		255 - this->g,
		255 - this->b,
		this->a
	);
}

Color Color::interpolate(const Color &other, f64 mix) const
{
	f64 mag0 = sqrt(this->r * this->r + this->g * this->g + this->b * this->b);
	f64 mag1 = sqrt(other.r * other.r + other.g * other.g + other.b * other.b);

	f64 mixed[3] = {
		this->r * (1 - mix) + other.r * mix,
		this->g * (1 - mix) + other.g * mix,
		this->b * (1 - mix) + other.b * mix
	};

	f64 mag = mag0 * (1 - mix) + mag1 * mix;
	f64 scale = mag / sqrt(mixed[0] * mixed[0] + mixed[1] * mixed[1] + mixed[2] * mixed[2]);

	auto compClamp = [] (f64 v) -> u8 {
		return max(0, min((int)round(v), 255));
	};

	return Color(
		compClamp(mixed[0] * scale),
		compClamp(mixed[1] * scale),
		compClamp(mixed[2] * scale)
	);
}

Vector<Color> Color::getAllInterpolates(const Color &other, unsigned steps) const
{
	Vector<Color> interpolated;
	interpolated.reserve(steps);
	f64 factor = 1.0 / (steps - 1);

	for (unsigned i = 0; i < steps; ++i)
		interpolated.append(this->interpolate(other, i * factor));
	return interpolated;
}

////////////////////////////////////////////////////////////////////////////////

bool Color::operator ==(const Color &rhs) const
{
	return (r == rhs.r) && (g == rhs.g) && (b == rhs.b) && (a == rhs.a);
}

bool Color::operator !=(const Color &rhs) const
{
	return !(*this == rhs);
}

////////////////////////////////////////////////////////////////////////////////

///              [0-360]  [0-100] [0-100] [0-255]
Color Color::HSB(u16 hue, u8 sat, u8 bri, u8 a)
{
	const f32 h = hue / 60.f;  // [0-6]
	const f32 s = sat / 100.f; // [0-1]
	const f32 b = bri * 2.55f; // [0-255]

	if (s < FLT_EPSILON)
		return Color(b, b, b, a);
	i32 sector = (i32)h;
	f32 tints[3] = {
		b * (1 - s),
		b * (1 - s * (h - sector)),
		b * (1 - s * (1 + sector - h))
	};

	switch (sector) {
		case 1 : return Color(tints[1], b, tints[0], a);
		case 2 : return Color(tints[0], b, tints[2], a);
		case 3 : return Color(tints[0], tints[1], b, a);
		case 4 : return Color(tints[2], tints[0], b, a);
		case 5 : return Color(b, tints[0], tints[1], a);
		default: return Color(b, tints[2], tints[0], a);
	}
}

////////////////////////////////////////////////////////////////////////////////

}