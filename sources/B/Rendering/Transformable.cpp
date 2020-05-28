/*
** B, 2019
** Rendering / Transformable.cpp
*/

#include "B/Rendering/Transformable.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

Transformable &Transformable::translate(const Vector3 &factors)
{
	auto m = Matrix::translated(factors);
	m_translation *= m;
	return *this;
}

Transformable &Transformable::rotate(const Vector3 &factors)
{
	Matrix m;
	m.setRotated(factors);
	m_rotation *= m;
	return *this;
}

Transformable &Transformable::rotateX(f64 theta)
{
	Matrix m;
	m.setRotatedX(theta);
	m_rotation *= m;
	return *this;
}

Transformable &Transformable::rotateY(f64 theta)
{
	Matrix m;
	m.setRotatedY(theta);
	m_rotation *= m;
	return *this;
}

Transformable &Transformable::rotateZ(f64 theta)
{
	Matrix m;
	m.setRotatedZ(theta);
	m_rotation *= m;
	return *this;
}

Transformable &Transformable::scale(const Vector3 &factors)
{
	Matrix m;
	m.setScaled(factors);
	m_scale *= m;
	return *this;
}

Transformable &Transformable::scale(f64 factor)
{
	Matrix m;
	m.setScaled(Vector3(factor));
	m_scale *= m;
	return *this;
}


void Transformable::transform(Vector3 &vector) const
{
	Matrix transform = m_translation * m_rotation * m_scale;
	vector *= transform;
}

////////////////////////////////////////////////////////////////////////////////

}