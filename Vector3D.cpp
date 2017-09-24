#include <stdio.h>
#include <stdlib.h>
#include "Vector3D.h"

#define EPSILON 0.0001

Vector3D::Vector3D()
{
	m_x = m_y = m_z = 0.0f;	m_w = 1.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
	m_x = x;	m_y = y;	m_z = z;	m_w = 1.0f;
}

Vector3D::Vector3D(float x, float y, float z, float w)
{
	m_x = x;	m_y = y;	m_z = z;	m_w = w;
}

Vector3D::~Vector3D()
{

}

bool Vector3D::operator==(const Vector3D& other)
{
	double d = 0.0f;

	d += fabs(m_x - other.m_x);
	d += fabs(m_y - other.m_y);
	d += fabs(m_z - other.m_z);
	d += fabs(m_w - other.m_w);

	return d < EPSILON;
}

bool Vector3D::operator!=(const Vector3D& other)
{
	double d = 0.0f;

	d += fabs(m_x - other.m_x);
	d += fabs(m_y - other.m_y);
	d += fabs(m_z - other.m_z);
	d += fabs(m_w - other.m_w);

	return d >= EPSILON;
}

Vector3D Vector3D::operator+(const Vector3D& other)
{
	return Vector3D(
		m_x + other.m_x,
		m_y + other.m_y,
		m_z + other.m_z
	);
}

Vector3D Vector3D::operator-(const Vector3D& other)
{
	return Vector3D(
		m_x - other.m_x,
		m_y - other.m_y,
		m_z - other.m_z
	);
}

Vector3D Vector3D::operator*(const float scalar)
{
	return Vector3D(
		m_x * scalar,
		m_y * scalar,
		m_z * scalar
	);
}

Vector3D Vector3D::operator/(const float divisor)
{
	return Vector3D(
		m_x / divisor,
		m_y / divisor,
		m_z / divisor
	);
}

void Vector3D::Add(const Vector3D& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	m_z += other.m_z;
}

void Vector3D::Sub(const Vector3D& other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
	m_z -= other.m_z;
}

void Vector3D::Mul(const float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	m_z *= scalar;
}

void Vector3D::Div(const float divisor)
{
	if (divisor == 0.0f)
		throw "Division by zero error!";
	m_x /= divisor;
	m_y /= divisor;
	m_z /= divisor;
}

void Vector3D::Print()
{
	printf("(X: %f, Y: %f, Z: %f, W: %f)\n", m_x, m_y, m_z, m_w);
}

void Vector3D::Zero()
{
	m_x = m_y = m_z = 0.0f;
}

void Vector3D::Set(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void Vector3D::Set(float x, float y, float z, float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}

void Vector3D::Negate()
{
	m_x = -m_x;
	m_y = -m_y;
	m_z = -m_z;
}

float Vector3D::SquareLength()
{
	return m_x * m_x + m_y * m_y + m_z * m_z;
}

float Vector3D::Length()
{
	return sqrt(SquareLength());
}

float Vector3D::SquareDistance(const Vector3D& vector0, const Vector3D& vector1)
{
	float x = vector1.m_x - vector0.m_x;
	float y = vector1.m_y - vector0.m_y;
	float z = vector1.m_z - vector0.m_z;
	return x * x + y * y + z * z;
}

float Vector3D::Distance(const Vector3D& vector0, const Vector3D& vector1)
{
	return sqrt(SquareDistance(vector0, vector1));
}

void Vector3D::Normalize()
{
	Div(Length());
}

Vector3D Vector3D::Normalize(Vector3D& vector)
{
	float length = vector.Length();
	if (length == 0.0f)
		throw "Division by zero error!";
	return vector / length;
}

float Vector3D::Dot(const Vector3D& vector0, const Vector3D& vector1)
{
	return vector0.m_x * vector1.m_x + vector0.m_y * vector1.m_y + vector0.m_z * vector1.m_z;
}

Vector3D Vector3D::Cross(const Vector3D& vector0, const Vector3D& vector1)
{
	return Vector3D(
		vector0.m_y * vector1.m_z - vector0.m_z * vector1.m_y,
		vector0.m_z * vector1.m_x - vector0.m_x * vector1.m_z,
		vector0.m_x * vector1.m_y - vector0.m_y * vector1.m_x
	);
}

Vector3D Vector3D::AngleRadians(float radians, Vector3D& axis)
{
	axis.Print();
	printf("radians: %f", radians);
	return Vector3D();
}

Vector3D Vector3D::AngleDegrees(float degrees, Vector3D& axis)
{
	return AngleRadians(degrees * M_PI / 180.0f, axis);
}