#include <stdio.h>
#include <stdlib.h>
#include "Vector2D.h"

#define EPSILON 0.0001

Vector2D::Vector2D() 
{
	m_x = m_y = 0.0f;	m_w = 1.0f;
}

Vector2D::Vector2D(float x, float y)
{
	m_x = x;	m_y = y;	m_w = 1.0f;
}

Vector2D::Vector2D(float x, float y, float w)
{
	m_x = x;	m_y = y;	m_w = w;
}

Vector2D::~Vector2D()
{

}

bool Vector2D::operator==(const Vector2D& other)
{
	float d = 0.0f;

	d += fabs(m_x - other.m_x);
	d += fabs(m_y - other.m_y);
	d += fabs(m_w - other.m_w);

	return d < EPSILON;
}

bool Vector2D::operator!=(const Vector2D& other)
{
	float d = 0.0f;

	d += fabs(m_x - other.m_x);
	d += fabs(m_y - other.m_y);
	d += fabs(m_w - other.m_w);

	return d >= EPSILON;
}

Vector2D Vector2D::operator+(const Vector2D& other)
{
	return Vector2D(
		m_x + other.m_x,
		m_y + other.m_y
	);
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
	return Vector2D(
		m_x - other.m_x,
		m_y - other.m_y
	);
}

Vector2D Vector2D::operator*(const float scalar)
{
	return Vector2D(
		m_x * scalar,
		m_y * scalar
	);
}

Vector2D Vector2D::operator/(const float divisor)
{
	return Vector2D(
		m_x / divisor,
		m_y / divisor
	);
}

void Vector2D::Add(const Vector2D& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
}

void Vector2D::Sub(const Vector2D& other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
}

void Vector2D::Mul(const float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
}

void Vector2D::Div(const float divisor)
{
	if (divisor == 0.0f)
		throw "Division by zero error!";
	m_x /= divisor;
	m_y /= divisor;
}

void Vector2D::Print()
{
	printf("(X: %f, Y: %f, W: %f)\n", m_x, m_y, m_w);
}

void Vector2D::Zero()
{
	m_x = m_y = 0.0f;
}

void Vector2D::Set(float x, float y)
{
	m_x = x;
	m_y = y;
}

void Vector2D::Set(float x, float y, float w)
{
	m_x = x;
	m_y = y;
	m_w = w;
}

void Vector2D::Negate()
{
	m_x = -m_x;
	m_y = -m_y;
}

float Vector2D::SquareLength()
{
	return m_x * m_x + m_y * m_y;
}

float Vector2D::Length()
{
	return sqrt(SquareLength());
}

float Vector2D::SquareDistance(const Vector2D& vector0, const Vector2D& vector1)
{
	float x = vector1.m_x - vector0.m_x;
	float y = vector1.m_y - vector0.m_y;
	return x * x + y * y;
}

float Vector2D::Distance(const Vector2D& vector0, const Vector2D& vector1)
{
	return sqrt(SquareDistance(vector0, vector1));
}

void Vector2D::Normalize()
{
	Div(Length());
}

Vector2D Vector2D::Normalize(Vector2D& vector)
{
	return vector / vector.Length();
}

float Vector2D::Dot(const Vector2D& vector0, const Vector2D& vector1)
{
	return vector0.m_x * vector1.m_x + vector0.m_y * vector1.m_y;
}

Vector2D Vector2D::AngleRadians(float radians)
{
	return Vector2D(cos(radians), sin(radians));
}

Vector2D Vector2D::AngleDegrees(float degrees)
{
	return AngleRadians(degrees * M_PI / 180.0f);
}