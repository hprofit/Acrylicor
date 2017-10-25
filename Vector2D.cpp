#include "Vector2D.h"
#include "AcrylicorTypedefs.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <algorithm>

Vector2D::Vector2D() : m_x(0.f), m_y(0.f), m_w(1.f) { }

Vector2D::Vector2D(float x, float y) : m_x(x), m_y(y), m_w(1.f) { }

Vector2D::Vector2D(float x, float y, float w) : m_x(x), m_y(y), m_w(w) { }

Vector2D::Vector2D(Vector2D const& rhs) : m_x(rhs.m_x), m_y(rhs.m_y), m_w(rhs.m_w) { }

Vector2D& Vector2D::operator=(Vector2D rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	m_w = rhs.m_w;
	return *this;
}

Vector2D::~Vector2D() { }

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

#pragma region Operator Overrides
bool Vector2D::operator==(const Vector2D& other) const
{
	return fabs(m_x - other.m_x) + fabs(m_y - other.m_y) + fabs(m_w - other.m_w) < EPSILON;
}

bool Vector2D::operator!=(const Vector2D& other) const
{
	return fabs(m_x - other.m_x) + fabs(m_y - other.m_y) + fabs(m_w - other.m_w) >= EPSILON;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	return Vector2D(
		m_x + other.m_x,
		m_y + other.m_y
	);
}

Vector2D& Vector2D::operator+=(const Vector2D & other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
	return Vector2D(
		m_x - other.m_x,
		m_y - other.m_y
	);
}

Vector2D& Vector2D::operator-=(const Vector2D & other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
	return *this;
}

Vector2D Vector2D::operator*(const float scalar) const
{
	return Vector2D(
		m_x * scalar,
		m_y * scalar
	);
}

Vector2D Vector2D::operator/(const float divisor) const
{
	return Vector2D(
		m_x / divisor,
		m_y / divisor
	);
}
#pragma endregion

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
	return sqrtf(SquareLength());
}

float Vector2D::SquareDistance(const Vector2D& vector0, const Vector2D& vector1)
{
	float x = vector1.m_x - vector0.m_x;
	float y = vector1.m_y - vector0.m_y;
	return x * x + y * y;
}

float Vector2D::Distance(const Vector2D& vector0, const Vector2D& vector1)
{
	return sqrtf(SquareDistance(vector0, vector1));
}

void Vector2D::Normalize()
{
	Div(Length());
}

float Vector2D::GetRadians()
{
	return atan2f(m_y, m_x);
}

float Vector2D::GetDegrees()
{
	return GetRadians() * DEG_TO_RAD;
}

#pragma region Static Methods

Vector2D Vector2D::Normalize(Vector2D& vector)
{
	float len = vector.Length();
	if (len == 0.0f)
		throw "Division by zero error!";
	return vector / len;
}

float Vector2D::Dot(const Vector2D& vector0, const Vector2D& vector1)
{
	return vector0.m_x * vector1.m_x + vector0.m_y * vector1.m_y;
}

Vector2D Vector2D::AngleRadians(float radians)
{
	return Vector2D(cosf(radians), sinf(radians));
}

Vector2D Vector2D::AngleDegrees(float degrees)
{
	return AngleRadians(degrees * DEG_TO_RAD);
}

#pragma endregion

#if TEST_MODE
void Vector2DTests()
{
	printf("\n========== Running Vector2D tests ==========\n\n");

	Vector2D * createdVector = new Vector2D();
	printf("Created Vector(): %s\n", (createdVector->getX() == 0.0f && createdVector->getY() == 0.0f && createdVector->getW() == 1.0f) ? PASS : FAIL);
	delete createdVector;

	createdVector = new Vector2D(1.0f, 2.0f);
	printf("Created Vector(x, y): %s\n", (createdVector->getX() == 1.0f && createdVector->getY() == 2.0f && createdVector->getW() == 1.0f) ? PASS : FAIL);
	delete createdVector;

	createdVector = new Vector2D(2.0f, 3.0f, 0.0f);
	printf("Created Vector(x, y, w): %s\n", (createdVector->getX() == 2.0f && createdVector->getY() == 3.0f && createdVector->getW() == 0.0f) ? PASS : FAIL);
	delete createdVector;

	Vector2D v1, v2, v3, result;
	float scalar;
	double angle;

	v1.Set(1.0f, 2.0f);
	v2.Set(1.0f, 2.0f);
	printf("Vector2D == equal: %s\n", (v1 == v2) ? PASS : FAIL);

	v2.Set(1.1f, 2.0f);
	printf("Vector2D == not equal: %s\n", (v1 == v2) ? FAIL : PASS);

	v2.Set(2.0f, 3.0f);
	printf("Vector2D != not equal: %s\n", (v1 != v2) ? PASS : FAIL);

	v2.Set(1.0f, 2.0f);
	printf("Vector2D != equal: %s\n", (v1 != v2) ? FAIL : PASS);

	v1.Set(0.1f, 2.0f);
	v2.Set(1.0f, 3.5f);
	result.Set(1.1f, 5.5f);
	printf("Vector2D +: %s\n", (v1 + v2 == result) ? PASS : FAIL);

	v1.Set(-0.1f, 1.0f);
	v2.Set(1.0f, -2.0f);
	result.Set(0.9f, -1.0f);
	printf("Vector2D +: %s\n", (v1 + v2 == result) ? PASS : FAIL);

	v1.Set(1.0f, 2.0f);
	v2.Set(1.0f, -2.0f);
	result.Set(0.0f, 4.0f);
	printf("Vector2D -: %s\n", (v1 - v2 == result) ? PASS : FAIL);

	v1.Set(-2.0f, 2.5f);
	v2.Set(-2.0f, 2.0f);
	result.Set(0.0f, 0.5f);
	printf("Vector2D -: %s\n", (v1 - v2 == result) ? PASS : FAIL);

	scalar = 2.0f;
	result.Set(-4.0f, 5.0f);
	printf("Vector2D *: %s\n", (v1 * scalar == result) ? PASS : FAIL);

	scalar = 0.5f;
	result.Set(-1.0f, 1.25f);
	printf("Vector2D *: %s\n", (v1 * scalar == result) ? PASS : FAIL);

	scalar = 2.0f;
	result.Set(-1.0f, 1.25f);
	printf("Vector2D /: %s\n", (v1 / scalar == result) ? PASS : FAIL);

	v1.Set(-2.0f, 10.0f);
	scalar = 0.5f;
	result.Set(-4.0f, 20.0f);
	printf("Vector2D /: %s\n", (v1 / scalar == result) ? PASS : FAIL);

	v1.Set(0.1f, 2.0f);
	v2.Set(1.0f, 3.5f);
	result.Set(1.1f, 5.5f);
	v1.Add(v2);
	printf("Vector2D Add: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(-0.1f, 1.0f);
	v2.Set(1.0f, -2.0f);
	result.Set(0.9f, -1.0f);
	v1.Add(v2);
	printf("Vector2D Add: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(1.0f, 2.0f);
	v2.Set(1.0f, -2.0f);
	result.Set(0.0f, 4.0f);
	v1.Sub(v2);
	printf("Vector2D Sub: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(-2.0f, 2.5f);
	v2.Set(-2.0f, 2.0f);
	result.Set(0.0f, 0.5f);
	v1.Sub(v2);
	printf("Vector2D Sub: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(-2.0f, 2.5f);
	scalar = 2.0f;
	result.Set(-4.0f, 5.0f);
	v1.Mul(scalar);
	printf("Vector2D Mul: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(-2.0f, 2.5f);
	scalar = 0.5f;
	result.Set(-1.0f, 1.25f);
	v1.Mul(scalar);
	printf("Vector2D Mul: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(-2.0f, 10.0f);
	scalar = 2.0f;
	result.Set(-1.0f, 5.0f);
	v1.Div(scalar);
	printf("Vector2D Div: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(-2.0f, 10.0f);
	scalar = 0.5f;
	result.Set(-4.0f, 20.0f);
	v1.Div(scalar);
	printf("Vector2D Div: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(1.0f, 1.0f);
	result.Set(0.0f, 0.0f);
	v1.Zero();
	printf("Vector2D Zero: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(1.0f, 0.0f, 1.0f);
	result.Set(1.0f, 2.0f, 1.0f);
	v1.Set(1.0f, 2.0f);
	printf("Vector2D Set(x, y): %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(0.0f, 0.0f, 0.0f);
	result.Set(1.0f, 2.0f, 1.0f);
	v1.Set(1.0f, 2.0f, 1.0f);
	printf("Vector2D Set(x, y, w): %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(1.0f, -1.0f, 1.0f);
	result.Set(-1.0f, 1.0f, 1.0f);
	v1.Negate();
	printf("Vector2D Negate: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(-1.0f, 0.0f, 1.0f);
	result.Set(1.0f, 0.0f, 1.0f);
	v1.Negate();
	printf("Vector2D Negate: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(-3.0f, 4.0f);
	printf("Vector2D SquareLength: %s\n", (v1.SquareLength() == 25.0) ? PASS : FAIL);

	v1.Set(-4.0f, 3.0f);
	printf("Vector2D Length: %s\n", (v1.Length() == 5.0) ? PASS : FAIL);

	v1.Set(-3.0f, 4.0f);
	v2.Set(3.0f, -4.0f);
	printf("Vector2D SquareDistance: %s\n", (Vector2D::SquareDistance(v1, v2) == 100.0f) ? PASS : FAIL);

	printf("Vector2D Distance: %s\n", ((Vector2D::Distance(v1, v2) - 10.0f) < EPSILON) ? PASS : FAIL);

	result.Set(-0.6f, 0.8f);
	v1.Normalize();
	printf("Vector2D Normalize: %s\n", (v1 == result) ? PASS : FAIL);

	v1.Set(3.0f, -4.0f);
	v1.Normalize();
	printf("Vector2D Normalize Length Check: %s\n", (v1.Length() == 1.0f) ? PASS : FAIL);

	v1.Set(3.0f, -4.0f);
	result.Set(0.6f, -0.8f);
	printf("Vector2D Normalize(vector): %s\n", (Vector2D::Normalize(v1) == result) ? PASS : FAIL);

	v1.Set(-3.0f, 4.0f);
	printf("Vector2D Normalize(vector) Length Check: %s\n", (Vector2D::Normalize(v1).Length() == 1.0f) ? PASS : FAIL);

	v1.Set(2.0f, 3.0f);
	v2.Set(4.0f, 5.0f);
	printf("Vector2D Dot: %s\n", ((Vector2D::Dot(v1, v2) - 23.0f) < EPSILON) ? PASS : FAIL);

	result.Set(0.707106f, 0.707106f, 1.0f);
	angle = PI_4;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.Set(0.0f, 1.0f, 1.0f);
	angle = PI_2;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.Set(-1.0f, 0.0f, 1.0f);
	angle = PI;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.Set(-1.0f, 0.0f, 1.0f);
	angle = -PI;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.Set(0.0f, -1.0f, 1.0f);
	angle = 1.5f * PI;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.Set(1.0f, 0.0f, 1.0f);
	angle = 2.0f * PI;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.Set(1.0f, 0.0f, 1.0f);
	angle = 0.0f;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.Set(0.707106f, 0.707106f, 1.0f);
	angle = 45.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.Set(0.0f, 1.0f, 1.0f);
	angle = 90.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.Set(-1.0f, 0.0f, 1.0f);
	angle = 180.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.Set(-1.0f, 0.0f, 1.0f);
	angle = -180.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.Set(0.0f, -1.0f, 1.0f);
	angle = 270.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.Set(1.0f, 0.0f, 1.0f);
	angle = 360.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.Set(1.0f, 0.0f, 1.0f);
	angle = 0.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);
}
#endif