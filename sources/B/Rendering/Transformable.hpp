/*
** B, 2019
** Rendering / Transformable.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	class Transformable;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Math/Matrix.hpp"
#include "B/Math/Vector3.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

class Transformable
{
public:
	Transformable() = default;
	virtual ~Transformable() = default;

	Transformable &translate(const Vector3 &factors);
	Transformable &rotate(const Vector3 &factors);
	Transformable &rotateX(f64 theta);
	Transformable &rotateY(f64 theta);
	Transformable &rotateZ(f64 theta);
	Transformable &scale(const Vector3 &factors);
	Transformable &scale(f64 factor);

	void transform(Vector3 &vector) const;

private:
	Matrix m_translation;
	Matrix m_rotation;
	Matrix m_scale;
};

////////////////////////////////////////////////////////////////////////////////

}