#include "Matrix4x4.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define EPSILON 0.0001
#define PASS "PASS"
#define FAIL "!!!!! FAIL !!!!!"

Matrix4x4::Matrix4x4() {}

Matrix4x4::Matrix4x4(
	float x1, float y1, float z1, float w1, 
	float x2, float y2, float z2, float w2, 
	float x3, float y3, float z3, float w3, 
	float x4, float y4, float z4, float w4)
{
	m_matrix[0][0] = x1;
	m_matrix[0][1] = y1;
	m_matrix[0][2] = z1;
	m_matrix[0][3] = w1;

	m_matrix[1][0] = x2;
	m_matrix[1][1] = y2;
	m_matrix[1][2] = z2;
	m_matrix[1][3] = w2;

	m_matrix[2][0] = x3;
	m_matrix[2][1] = y3;
	m_matrix[2][2] = z3;
	m_matrix[2][3] = w3;

	m_matrix[3][0] = x4;
	m_matrix[3][1] = y4;
	m_matrix[3][2] = z4;
	m_matrix[3][3] = w4;
}

Matrix4x4::Matrix4x4(const Matrix4x4 &other)
{
	m_matrix[0][0] = other.m_matrix[0][0];
	m_matrix[0][1] = other.m_matrix[0][1];
	m_matrix[0][2] = other.m_matrix[0][2];
	m_matrix[0][3] = other.m_matrix[0][3];

	m_matrix[1][0] = other.m_matrix[1][0];
	m_matrix[1][1] = other.m_matrix[1][1];
	m_matrix[1][2] = other.m_matrix[1][2];
	m_matrix[1][3] = other.m_matrix[1][3];

	m_matrix[2][0] = other.m_matrix[2][0];
	m_matrix[2][1] = other.m_matrix[2][1];
	m_matrix[2][2] = other.m_matrix[2][2];
	m_matrix[2][3] = other.m_matrix[2][3];

	m_matrix[3][0] = other.m_matrix[3][0];
	m_matrix[3][1] = other.m_matrix[3][1];
	m_matrix[3][2] = other.m_matrix[3][2];
	m_matrix[3][3] = other.m_matrix[3][3];
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other) // Copy ctor
{
	m_matrix[0][0] = other.m_matrix[0][0];
	m_matrix[0][1] = other.m_matrix[0][1];
	m_matrix[0][2] = other.m_matrix[0][2];
	m_matrix[0][3] = other.m_matrix[0][3];

	m_matrix[1][0] = other.m_matrix[1][0];
	m_matrix[1][1] = other.m_matrix[1][1];
	m_matrix[1][2] = other.m_matrix[1][2];
	m_matrix[1][3] = other.m_matrix[1][3];

	m_matrix[2][0] = other.m_matrix[2][0];
	m_matrix[2][1] = other.m_matrix[2][1];
	m_matrix[2][2] = other.m_matrix[2][2];
	m_matrix[2][3] = other.m_matrix[2][3];

	m_matrix[3][0] = other.m_matrix[3][0];
	m_matrix[3][1] = other.m_matrix[3][1];
	m_matrix[3][2] = other.m_matrix[3][2];
	m_matrix[3][3] = other.m_matrix[3][3];
	return *this;
}

Matrix4x4::~Matrix4x4() {}

float Matrix4x4::Get(int row, int col)
{
	if (row < 0 || row > 3 || col < 0 || col > 3)
		throw "Invalid row or column access.";
	return m_matrix[row][col];
}

void Matrix4x4::Set(int row, int col, float val)
{
	if (row < 0 || row > 3 || col < 0 || col > 3)
		throw "Invalid row or column access.";
	m_matrix[row][col] = val;
}

void Matrix4x4::Transpose()
{
	Matrix4x4 transposed = Matrix4x4(
		0.0f,			m_matrix[1][0], m_matrix[2][0], m_matrix[3][0],
		m_matrix[0][1], 0.0f,			m_matrix[2][1], m_matrix[3][1],
		m_matrix[0][2], m_matrix[1][2], 0.0f,			m_matrix[3][2],
		m_matrix[0][3], m_matrix[1][3], m_matrix[2][3], 0.0f
	);

	m_matrix[0][1] = transposed.m_matrix[0][1];
	m_matrix[0][2] = transposed.m_matrix[0][2];
	m_matrix[0][3] = transposed.m_matrix[0][3];

	m_matrix[1][0] = transposed.m_matrix[1][0];
	m_matrix[1][2] = transposed.m_matrix[1][2];
	m_matrix[1][3] = transposed.m_matrix[1][3];

	m_matrix[2][0] = transposed.m_matrix[2][0];
	m_matrix[2][1] = transposed.m_matrix[2][1];
	m_matrix[2][3] = transposed.m_matrix[2][3];

	m_matrix[3][0] = transposed.m_matrix[3][0];
	m_matrix[3][1] = transposed.m_matrix[3][1];
	m_matrix[3][2] = transposed.m_matrix[3][2];
}

void Matrix4x4::Zero()
{
	m_matrix[0][0] = 0.0f;
	m_matrix[0][1] = 0.0f;
	m_matrix[0][2] = 0.0f;
	m_matrix[0][3] = 0.0f;

	m_matrix[1][0] = 0.0f;
	m_matrix[1][1] = 0.0f;
	m_matrix[1][2] = 0.0f;
	m_matrix[1][3] = 0.0f;

	m_matrix[2][0] = 0.0f;
	m_matrix[2][1] = 0.0f;
	m_matrix[2][2] = 0.0f;
	m_matrix[2][3] = 0.0f;

	m_matrix[3][0] = 0.0f;
	m_matrix[3][1] = 0.0f;
	m_matrix[3][2] = 0.0f;
	m_matrix[3][3] = 0.0f;
}

void Matrix4x4::Identity()
{
	m_matrix[0][0] = 1.0f;
	m_matrix[0][1] = 0.0f;
	m_matrix[0][2] = 0.0f;
	m_matrix[0][3] = 0.0f;

	m_matrix[1][0] = 0.0f;
	m_matrix[1][1] = 1.0f;
	m_matrix[1][2] = 0.0f;
	m_matrix[1][3] = 0.0f;

	m_matrix[2][0] = 0.0f;
	m_matrix[2][1] = 0.0f;
	m_matrix[2][2] = 1.0f;
	m_matrix[2][3] = 0.0f;

	m_matrix[3][0] = 0.0f;
	m_matrix[3][1] = 0.0f;
	m_matrix[3][2] = 0.0f;
	m_matrix[3][3] = 1.0f;
}

void Matrix4x4::Print()
{
	printf("( %f %f %f %f )\n", m_matrix[0][0], m_matrix[0][1], m_matrix[0][2], m_matrix[0][3]);
	printf("( %f %f %f %f )\n", m_matrix[1][0], m_matrix[1][1], m_matrix[1][2], m_matrix[1][3]);
	printf("( %f %f %f %f )\n", m_matrix[2][0], m_matrix[2][1], m_matrix[2][2], m_matrix[2][3]);
	printf("( %f %f %f %f )\n", m_matrix[3][0], m_matrix[3][1], m_matrix[3][2], m_matrix[3][3]);
	printf("\n");
}


/* Static Matrix4x4 Functions */
Matrix4x4 Matrix4x4::Zero4D()
{
	return Matrix4x4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

Matrix4x4 Matrix4x4::Identity4D()
{
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}


/* Matrix4x4 Operations */
bool Matrix4x4::operator==(const Matrix4x4& other)
{
	double d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);
	d += fabs(m_matrix[0][2] - other.m_matrix[0][2]);
	d += fabs(m_matrix[0][3] - other.m_matrix[0][3]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	d += fabs(m_matrix[1][2] - other.m_matrix[1][2]);
	d += fabs(m_matrix[1][3] - other.m_matrix[1][3]);

	d += fabs(m_matrix[2][0] - other.m_matrix[2][0]);
	d += fabs(m_matrix[2][1] - other.m_matrix[2][1]);
	d += fabs(m_matrix[2][2] - other.m_matrix[2][2]);
	d += fabs(m_matrix[2][3] - other.m_matrix[2][3]);

	d += fabs(m_matrix[3][0] - other.m_matrix[3][0]);
	d += fabs(m_matrix[3][1] - other.m_matrix[3][1]);
	d += fabs(m_matrix[3][2] - other.m_matrix[3][2]);
	d += fabs(m_matrix[3][3] - other.m_matrix[3][3]);
	return d < EPSILON;
}

bool Matrix4x4::operator!=(const Matrix4x4& other)
{
	double d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);
	d += fabs(m_matrix[0][2] - other.m_matrix[0][2]);
	d += fabs(m_matrix[0][3] - other.m_matrix[0][3]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	d += fabs(m_matrix[1][2] - other.m_matrix[1][2]);
	d += fabs(m_matrix[1][3] - other.m_matrix[1][3]);

	d += fabs(m_matrix[2][0] - other.m_matrix[2][0]);
	d += fabs(m_matrix[2][1] - other.m_matrix[2][1]);
	d += fabs(m_matrix[2][2] - other.m_matrix[2][2]);
	d += fabs(m_matrix[2][3] - other.m_matrix[2][3]);

	d += fabs(m_matrix[3][0] - other.m_matrix[3][0]);
	d += fabs(m_matrix[3][1] - other.m_matrix[3][1]);
	d += fabs(m_matrix[3][2] - other.m_matrix[3][2]);
	d += fabs(m_matrix[3][3] - other.m_matrix[3][3]);
	return d >= EPSILON;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other)
{
	return Matrix4x4(
		m_matrix[0][0] + other.m_matrix[0][0], m_matrix[0][1] + other.m_matrix[0][1], m_matrix[0][2] + other.m_matrix[0][2], m_matrix[0][3] + other.m_matrix[0][3],
		m_matrix[1][0] + other.m_matrix[1][0], m_matrix[1][1] + other.m_matrix[1][1], m_matrix[1][2] + other.m_matrix[1][2], m_matrix[1][3] + other.m_matrix[1][3],
		m_matrix[2][0] + other.m_matrix[2][0], m_matrix[2][1] + other.m_matrix[2][1], m_matrix[2][2] + other.m_matrix[2][2], m_matrix[2][3] + other.m_matrix[2][3],
		m_matrix[3][0] + other.m_matrix[3][0], m_matrix[3][1] + other.m_matrix[3][1], m_matrix[3][2] + other.m_matrix[3][2], m_matrix[3][3] + other.m_matrix[3][3]
	);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other)
{
	return Matrix4x4(
		m_matrix[0][0] - other.m_matrix[0][0], m_matrix[0][1] - other.m_matrix[0][1], m_matrix[0][2] - other.m_matrix[0][2], m_matrix[0][3] - other.m_matrix[0][3],
		m_matrix[1][0] - other.m_matrix[1][0], m_matrix[1][1] - other.m_matrix[1][1], m_matrix[1][2] - other.m_matrix[1][2], m_matrix[1][3] - other.m_matrix[1][3],
		m_matrix[2][0] - other.m_matrix[2][0], m_matrix[2][1] - other.m_matrix[2][1], m_matrix[2][2] - other.m_matrix[2][2], m_matrix[2][3] - other.m_matrix[2][3],
		m_matrix[3][0] - other.m_matrix[3][0], m_matrix[3][1] - other.m_matrix[3][1], m_matrix[3][2] - other.m_matrix[3][2], m_matrix[3][3] - other.m_matrix[3][3]
	);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other)
{
	return Matrix4x4(
		(m_matrix[0][0] * other.m_matrix[0][0]) + (m_matrix[0][1] * other.m_matrix[1][0]) + (m_matrix[0][2] * other.m_matrix[2][0]) + (m_matrix[0][3] * other.m_matrix[3][0]),
		(m_matrix[0][0] * other.m_matrix[0][1]) + (m_matrix[0][1] * other.m_matrix[1][1]) + (m_matrix[0][2] * other.m_matrix[2][1]) + (m_matrix[0][3] * other.m_matrix[3][1]),
		(m_matrix[0][0] * other.m_matrix[0][2]) + (m_matrix[0][1] * other.m_matrix[1][2]) + (m_matrix[0][2] * other.m_matrix[2][2]) + (m_matrix[0][3] * other.m_matrix[3][2]),
		(m_matrix[0][0] * other.m_matrix[0][3]) + (m_matrix[0][1] * other.m_matrix[1][3]) + (m_matrix[0][2] * other.m_matrix[2][3]) + (m_matrix[0][3] * other.m_matrix[3][3]),

		(m_matrix[1][0] * other.m_matrix[0][0]) + (m_matrix[1][1] * other.m_matrix[1][0]) + (m_matrix[1][2] * other.m_matrix[2][0]) + (m_matrix[1][3] * other.m_matrix[3][0]),
		(m_matrix[1][0] * other.m_matrix[0][1]) + (m_matrix[1][1] * other.m_matrix[1][1]) + (m_matrix[1][2] * other.m_matrix[2][1]) + (m_matrix[1][3] * other.m_matrix[3][1]),
		(m_matrix[1][0] * other.m_matrix[0][2]) + (m_matrix[1][1] * other.m_matrix[1][2]) + (m_matrix[1][2] * other.m_matrix[2][2]) + (m_matrix[1][3] * other.m_matrix[3][2]),
		(m_matrix[1][0] * other.m_matrix[0][3]) + (m_matrix[1][1] * other.m_matrix[1][3]) + (m_matrix[1][2] * other.m_matrix[2][3]) + (m_matrix[1][3] * other.m_matrix[3][3]),

		(m_matrix[2][0] * other.m_matrix[0][0]) + (m_matrix[2][1] * other.m_matrix[1][0]) + (m_matrix[2][2] * other.m_matrix[2][0]) + (m_matrix[2][3] * other.m_matrix[3][0]),
		(m_matrix[2][0] * other.m_matrix[0][1]) + (m_matrix[2][1] * other.m_matrix[1][1]) + (m_matrix[2][2] * other.m_matrix[2][1]) + (m_matrix[2][3] * other.m_matrix[3][1]),
		(m_matrix[2][0] * other.m_matrix[0][2]) + (m_matrix[2][1] * other.m_matrix[1][2]) + (m_matrix[2][2] * other.m_matrix[2][2]) + (m_matrix[2][3] * other.m_matrix[3][2]),
		(m_matrix[2][0] * other.m_matrix[0][3]) + (m_matrix[2][1] * other.m_matrix[1][3]) + (m_matrix[2][2] * other.m_matrix[2][3]) + (m_matrix[2][3] * other.m_matrix[3][3]),

		(m_matrix[3][0] * other.m_matrix[0][0]) + (m_matrix[3][1] * other.m_matrix[1][0]) + (m_matrix[3][2] * other.m_matrix[2][0]) + (m_matrix[3][3] * other.m_matrix[3][0]),
		(m_matrix[3][0] * other.m_matrix[0][1]) + (m_matrix[3][1] * other.m_matrix[1][1]) + (m_matrix[3][2] * other.m_matrix[2][1]) + (m_matrix[3][3] * other.m_matrix[3][1]),
		(m_matrix[3][0] * other.m_matrix[0][2]) + (m_matrix[3][1] * other.m_matrix[1][2]) + (m_matrix[3][2] * other.m_matrix[2][2]) + (m_matrix[3][3] * other.m_matrix[3][2]),
		(m_matrix[3][0] * other.m_matrix[0][3]) + (m_matrix[3][1] * other.m_matrix[1][3]) + (m_matrix[3][2] * other.m_matrix[2][3]) + (m_matrix[3][3] * other.m_matrix[3][3])
	);
}

Matrix4x4 Matrix4x4::operator*(const float scalar)
{
	return Matrix4x4(
		m_matrix[0][0] * scalar, m_matrix[0][1] * scalar, m_matrix[0][2] * scalar, m_matrix[0][3] * scalar,
		m_matrix[1][0] * scalar, m_matrix[1][1] * scalar, m_matrix[1][2] * scalar, m_matrix[1][3] * scalar,
		m_matrix[2][0] * scalar, m_matrix[2][1] * scalar, m_matrix[2][2] * scalar, m_matrix[2][3] * scalar,
		m_matrix[3][0] * scalar, m_matrix[3][1] * scalar, m_matrix[3][2] * scalar, m_matrix[3][3] * scalar
	);
}

Matrix4x4 Matrix4x4::operator/(const float divisor)
{
	if (divisor == 0.0f)
		throw "Division by zero error!";

	return Matrix4x4(
		m_matrix[0][0] / divisor, m_matrix[0][1] / divisor, m_matrix[0][2] / divisor, m_matrix[0][3] / divisor,
		m_matrix[1][0] / divisor, m_matrix[1][1] / divisor, m_matrix[1][2] / divisor, m_matrix[1][3] / divisor,
		m_matrix[2][0] / divisor, m_matrix[2][1] / divisor, m_matrix[2][2] / divisor, m_matrix[2][3] / divisor,
		m_matrix[3][0] / divisor, m_matrix[3][1] / divisor, m_matrix[3][2] / divisor, m_matrix[3][3] / divisor
	);
}


/* Vector3D operations */
Vector3D Matrix4x4::operator*(const Vector3D& other)
{
	return Vector3D(
		m_matrix[0][0] * other.getX() + m_matrix[0][1] * other.getY() + m_matrix[0][2] * other.getZ() + m_matrix[0][3] * other.getW(),
		m_matrix[1][0] * other.getX() + m_matrix[1][1] * other.getY() + m_matrix[1][2] * other.getZ() + m_matrix[1][3] * other.getW(),
		m_matrix[2][0] * other.getX() + m_matrix[2][1] * other.getY() + m_matrix[2][2] * other.getZ() + m_matrix[2][3] * other.getW(),
		m_matrix[3][0] * other.getX() + m_matrix[3][1] * other.getY() + m_matrix[3][2] * other.getZ() + m_matrix[3][3] * other.getW()
	);
}
