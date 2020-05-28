/*
** B, 2019
** Size.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B
{

struct Size
{
	unsigned width = 0;
	unsigned height = 0;

	Size() = default;
	Size(Size &&) = default;
	Size(const Size &) = default;

	Size(unsigned w, unsigned h)
	: width(w)
	, height(h)
	{}

	Size &operator =(Size &&) = default;
	Size &operator =(const Size &) = default;

	bool operator ==(const Size &rhs) const { return width == rhs.width && height == rhs.height; }
	bool operator !=(const Size &rhs) const { return !(*this == rhs); }
	Size operator +(const Size &rhs) const { return Size(width + rhs.width, height + rhs.height); }
	Size operator -(const Size &rhs) const { return Size(width - rhs.width, height - rhs.height); }
	void operator +=(const Size &rhs) { width += rhs.width; height += rhs.height; }
	void operator -=(const Size &rhs) { width -= rhs.width; height -= rhs.height; }
};

////////////////////////////////////////////////////////////////////////////////

class Sizeable
{
public:
	Sizeable()
	{}

	Sizeable(unsigned w, unsigned h)
	: m_size(w, h)
	{}

	Sizeable(const Size &size)
	: m_size(size)
	{}

	virtual const Size &size() const { return m_size; }
	virtual void setSize(const Size &size) { m_size = size; }
	virtual void grow(const Size &size) { setSize(m_size + size); }
	virtual void shrink(const Size &size) { setSize(m_size - size); }

	unsigned width() const { return size().width; }
	unsigned height() const { return size().height; }
	void setSize(unsigned width, unsigned height) { setSize({width, height}); }
	void setWidth(unsigned w) { setSize(w, height()); }
	void setHeight(unsigned h) { setSize(width(), h); }
	void grow(unsigned width, unsigned height) { grow({width, height}); }
	void shrink(unsigned width, unsigned height) { shrink({width, height}); }

protected:
	Size m_size;
};

}