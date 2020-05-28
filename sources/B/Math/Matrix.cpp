/*
** B, 2019
** Math / Matrix.cpp
*/

#include "B/Math/Matrix.hpp"
#include <cmath>
#include <cfloat>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

Matrix::Matrix()
{
	this->identity();
}

Matrix::Matrix(const Matrix &other)
{
	*this = other;
}


void Matrix::setTranslated(const Vector3 &vec)
{
	this->identity();
	this->m[0][3] = vec.x;
	this->m[1][3] = vec.y;
	this->m[2][3] = vec.z;
}

void Matrix::setRotated(const Vector3 &vec)
{
	this->identity();
	Matrix x, y, z;
	x.setRotatedX(vec.x);
	y.setRotatedY(vec.y);
	z.setRotatedZ(vec.z);
	*this = x * y * z;
}

void Matrix::setRotatedX(f64 theta)
{
	this->identity();
	this->m[1][1] = cos(theta);
	this->m[1][2] = -sin(theta);
	this->m[2][1] = sin(theta);
	this->m[2][2] = cos(theta);
}

void Matrix::setRotatedY(f64 theta)
{
	this->identity();
	this->m[0][0] = cos(theta);
	this->m[0][2] = -sin(theta);
	this->m[2][0] = sin(theta);
	this->m[2][2] = cos(theta);
}

void Matrix::setRotatedZ(f64 theta)
{
	this->identity();
	this->m[0][0] = cos(theta);
	this->m[0][1] = -sin(theta);
	this->m[1][0] = sin(theta);
	this->m[1][1] = cos(theta);
}

void Matrix::setScaled(const Vector3 &vec)
{
	this->identity();
	this->m[0][0] = vec.x;
	this->m[1][1] = vec.y;
	this->m[2][2] = vec.z;
}



Matrix &Matrix::identity()
{
	for (unsigned i = 0; i < 4; ++i)
		this->m[i][i] = 1.0;
	return *this;
}

Matrix &Matrix::translate(const Vector3 &vec)
{
	this->m[0][3] += vec.x;
	this->m[1][3] += vec.y;
	this->m[2][3] += vec.z;
	return *this;
}

Matrix &Matrix::rotate(const Vector3 &vec)
{
	return rotateX(vec.x).rotateY(vec.y).rotateZ(vec.z);
}

Matrix &Matrix::rotateX(f64 theta)
{
	this->m[1][1] *= cos(theta);
	this->m[1][2] *= -sin(theta);
	this->m[2][1] *= sin(theta);
	this->m[2][2] *= cos(theta);
	return *this;
}

Matrix &Matrix::rotateY(f64 theta)
{
	this->m[0][0] *= cos(theta);
	this->m[0][2] *= -sin(theta);
	this->m[2][0] *= sin(theta);
	this->m[2][2] *= cos(theta);
	return *this;
}

Matrix &Matrix::rotateZ(f64 theta)
{
	this->m[0][0] *= cos(theta);
	this->m[0][1] *= -sin(theta);
	this->m[1][0] *= sin(theta);
	this->m[1][1] *= cos(theta);
	return *this;
}

Matrix &Matrix::scale(const Vector3 &vec)
{
	this->m[0][0] *= vec.x;
	this->m[1][1] *= vec.y;
	this->m[2][2] *= vec.z;
	return *this;
}

Matrix &Matrix::inverse()
{
	Matrix ret;

	ret.m[0][0] = this->m[0][0];
	ret.m[1][0] = this->m[0][1];
	ret.m[2][0] = this->m[0][2];
	ret.m[3][0] = 0.0;

	ret.m[0][1] = this->m[1][0];
	ret.m[1][1] = this->m[1][1];
	ret.m[2][1] = this->m[1][2];
	ret.m[3][1] = 0.0;

	ret.m[0][2] = this->m[2][0];
	ret.m[1][2] = this->m[2][1];
	ret.m[2][2] = this->m[2][2];
	ret.m[3][2] = 0.0;

	ret.m[0][3] = -(this->m[0][3] * ret.m[0][0] + this->m[1][3] * ret.m[0][1] + this->m[2][3] * ret.m[0][2]);
	ret.m[1][3] = -(this->m[0][3] * ret.m[1][0] + this->m[1][3] * ret.m[1][1] + this->m[2][3] * ret.m[1][2]);
	ret.m[2][3] = -(this->m[0][3] * ret.m[2][0] + this->m[1][3] * ret.m[2][1] + this->m[2][3] * ret.m[2][2]);
	ret.m[3][3] = 1.0;

	return *this = ret;
}

////////////////////////////////////////////////////////////////////////////////

Matrix &Matrix::operator =(const Matrix &rhs)
{
	for (unsigned i = 0; i < 4; ++i)
		for (unsigned j = 0; j < 4; ++j)
			this->m[i][j] = rhs.m[i][j];
	return *this;
}

////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::operator *(const Matrix &rhs) const
{
	Matrix res;

	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			res.m[i][j] = 0;
			for (unsigned k = 0; k < 4; ++k)
				res.m[i][j] += this->m[i][k] * rhs.m[k][j];
		}
	}

	return res;
}

Matrix &Matrix::operator *=(const Matrix &rhs)
{
	*this = rhs * (*this);
	return *this;
}

Vector3 Matrix::operator *(const Vector3 &rhs) const
{
	Vector3 res(
		rhs.x * m[0][0] + rhs.y * m[0][1] + rhs.z * m[0][2] + m[0][3],
		rhs.x * m[1][0] + rhs.y * m[1][1] + rhs.z * m[1][2] + m[1][3],
		rhs.x * m[2][0] + rhs.y * m[2][1] + rhs.z * m[2][2] + m[2][3]
	);

	double w = rhs.x * m[3][0] + rhs.y * m[3][1] + rhs.z * m[3][2] + m[3][3];
	if (fabs(w) > DBL_EPSILON) // if (w != 0)
		res /= w;

	return res;
}

////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::projection(f64 aspectRatio, f64 fov)
{
	const f64 near = 0.1;
	const f64 far = 1000.0;
	f64 tanHalfFOV = tan((fov / 180.0 * M_PI) / 2.0);
	f64 range = near - far;

	Matrix proj;
	proj.m[0][0] = 1.0 / (aspectRatio * tanHalfFOV);
	proj.m[1][1] = 1.0 / tanHalfFOV;
	proj.m[2][2] = (-near - far) / range;
	proj.m[2][3] = 2 * far * near / range;
	proj.m[3][2] = 1.0;
	proj.m[3][3] = 0.0;
	return proj;
}

Matrix Matrix::translated(const Vector3 &vec)
{
	Matrix m;
	m.setTranslated(vec);
	return m;
}

Matrix Matrix::rotated(const Vector3 &vec)
{
	Matrix m;
	m.setRotated(vec);
	return m;
}

Matrix Matrix::rotatedX(f64 theta)
{
	Matrix m;
	m.setRotatedX(theta);
	return m;
}

Matrix Matrix::rotatedY(f64 theta)
{
	Matrix m;
	m.setRotatedY(theta);
	return m;
}

Matrix Matrix::rotatedZ(f64 theta)
{
	Matrix m;
	m.setRotatedZ(theta);
	return m;
}

Matrix Matrix::scaled(const Vector3 &vec)
{
	Matrix m;
	m.setScaled(vec);
	return m;
}


////////////////////////////////////////////////////////////////////////////////

}