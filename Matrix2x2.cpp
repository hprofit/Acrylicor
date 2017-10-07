#include "Matrix2x2.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define EPSILON 0.0001
#define PASS "PASS"
#define FAIL "!!!!! FAIL !!!!!"

Matrix2x2::Matrix2x2() {}

Matrix2x2::Matrix2x2(float x1, float y1, float x2, float y2) 
{
	m_matrix[0][0] = x1;
	m_matrix[0][1] = y1;
	m_matrix[1][0] = x2;
	m_matrix[1][1] = y2;
}

Matrix2x2::Matrix2x2(const Matrix2x2 &other)
{
	m_matrix[0][0] = other.m_matrix[0][0];
	m_matrix[0][1] = other.m_matrix[0][1];
	m_matrix[1][0] = other.m_matrix[1][0];
	m_matrix[1][1] = other.m_matrix[1][1];
}

Matrix2x2& Matrix2x2::operator=(const Matrix2x2& other) // Copy ctor
{
	m_matrix[0][0] = other.m_matrix[0][0];
	m_matrix[0][1] = other.m_matrix[0][1];
	m_matrix[1][0] = other.m_matrix[1][0];
	m_matrix[1][1] = other.m_matrix[1][1];
	return *this;
}

Matrix2x2::~Matrix2x2(){}

float Matrix2x2::Get(int row, int col)
{
	if (row < 0 || row > 1 || col < 0 || col > 1)
		throw "Invalid row or column access.";
	return m_matrix[row][col];
}

void Matrix2x2::Set(int row, int col, float val)
{
	if (row < 0 || row > 1 || col < 0 || col > 1)
		throw "Invalid row or column access.";
	m_matrix[row][col] = val;
}

void Matrix2x2::Transpose()
{
	float tmp = m_matrix[1][0];

	m_matrix[1][0] = m_matrix[0][1];
	m_matrix[0][1] = tmp;
}

void Matrix2x2::Zero()
{
	m_matrix[0][0] = 0.0f;
	m_matrix[0][1] = 0.0f;
	m_matrix[1][0] = 0.0f;
	m_matrix[1][1] = 0.0f;
}

void Matrix2x2::Identity()
{
	m_matrix[0][0] = 1.0f;
	m_matrix[0][1] = 0.0f;
	m_matrix[1][0] = 0.0f;
	m_matrix[1][1] = 1.0f;
}

void Matrix2x2::Print()
{
	printf("( %f %f )\n", m_matrix[0][0], m_matrix[0][1]);
	printf("( %f %f )\n", m_matrix[1][0], m_matrix[1][1]);
	printf("\n");
}


/* Static Matrix2x2 Functions */
Matrix2x2 Matrix2x2::Zero2D()
{
	return Matrix2x2(0.0f, 0.0f, 0.0f, 0.0f);
}

Matrix2x2 Matrix2x2::Identity2D()
{
	return Matrix2x2(
		1.0f, 0.0f, 
		0.0f, 1.0f
	);
}


/* Matrix2x2 Operations */
bool Matrix2x2::operator==(const Matrix2x2& other)
{
	double d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	return d < EPSILON;
}

bool Matrix2x2::operator!=(const Matrix2x2& other)
{
	double d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	return d >= EPSILON;
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other)
{
	return Matrix2x2(
		m_matrix[0][0] + other.m_matrix[0][0], m_matrix[0][1] + other.m_matrix[0][1],
		m_matrix[1][0] + other.m_matrix[1][0], m_matrix[1][1] + other.m_matrix[1][1]
	);
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other)
{
	return Matrix2x2(
		m_matrix[0][0] - other.m_matrix[0][0], m_matrix[0][1] - other.m_matrix[0][1],
		m_matrix[1][0] - other.m_matrix[1][0], m_matrix[1][1] - other.m_matrix[1][1]
	);
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2& other)
{
	return Matrix2x2(
		(m_matrix[0][0] * other.m_matrix[0][0]) + (m_matrix[0][1] * other.m_matrix[1][0]),
		(m_matrix[0][0] * other.m_matrix[0][1]) + (m_matrix[0][1] * other.m_matrix[1][1]),

		(m_matrix[1][0] * other.m_matrix[0][0]) + (m_matrix[1][1] * other.m_matrix[1][0]),
		(m_matrix[1][0] * other.m_matrix[0][1]) + (m_matrix[1][1] * other.m_matrix[1][1])
	);
}

Matrix2x2 Matrix2x2::operator*(const float scalar)
{
	return Matrix2x2(
		m_matrix[0][0] * scalar, m_matrix[0][1] * scalar,
		m_matrix[1][0] * scalar, m_matrix[1][1] * scalar
	);
}

Matrix2x2 Matrix2x2::operator/(const float divisor)
{
	if (divisor == 0.0f)
		throw "Division by zero error!";

	return Matrix2x2(
		m_matrix[0][0] / divisor, m_matrix[0][1] / divisor,
		m_matrix[1][0] / divisor, m_matrix[1][1] / divisor
	);
}

/* Vector2D operations */
Vector2D Matrix2x2::operator*(const Vector2D& other)
{
	return Vector2D(
		m_matrix[0][0] * other.getX() + m_matrix[0][1] * other.getY(),
		m_matrix[1][0] * other.getX() + m_matrix[1][1] * other.getY()
	);
}
