#include "Matrix3x3.h"

#define EPSILON 0.0001

Matrix3x3::Matrix3x3() : Matrix(3, 3) {}

Matrix3x3::Matrix3x3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) : Matrix(3, 3)
{
	m_matrix[0][0] = x1;
	m_matrix[0][1] = y1;
	m_matrix[0][2] = z1;

	m_matrix[1][0] = x2;
	m_matrix[1][1] = y2;
	m_matrix[1][2] = z2;

	m_matrix[2][0] = x3;
	m_matrix[2][1] = y3;
	m_matrix[2][2] = z3;
}

Matrix3x3::~Matrix3x3(){}

void Matrix3x3::Transpose()
{
	Matrix3x3 transposed = Matrix3x3(
		0.0f, m_matrix[1][0], m_matrix[2][0],
		m_matrix[0][1], 0.0f, m_matrix[2][1],
		m_matrix[0][2], m_matrix[1][2], 0.0f
	);

	m_matrix[0][1] = transposed.m_matrix[0][1];
	m_matrix[0][2] = transposed.m_matrix[0][1];

	m_matrix[1][0] = transposed.m_matrix[1][0];
	m_matrix[1][2] = transposed.m_matrix[1][2];

	m_matrix[2][0] = transposed.m_matrix[2][0];
	m_matrix[2][1] = transposed.m_matrix[2][1];
}

/* Static Matrix3x3 Functions */
Matrix3x3 Matrix3x3::Zero3D()
{
	return Matrix3x3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

Matrix3x3 Matrix3x3::Identity3D()
{
	return Matrix3x3(
		1.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 1.0f
	);
}


/* Matrix3x3 Operations */
bool Matrix3x3::operator==(const Matrix3x3& other)
{
	float d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);
	d += fabs(m_matrix[0][2] - other.m_matrix[0][2]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	d += fabs(m_matrix[1][2] - other.m_matrix[1][2]);

	d += fabs(m_matrix[2][0] - other.m_matrix[2][0]);
	d += fabs(m_matrix[2][1] - other.m_matrix[2][1]);
	d += fabs(m_matrix[2][2] - other.m_matrix[2][2]);
	return d < EPSILON;
}

bool Matrix3x3::operator!=(const Matrix3x3& other)
{
	float d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);
	d += fabs(m_matrix[0][2] - other.m_matrix[0][2]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	d += fabs(m_matrix[1][2] - other.m_matrix[1][2]);

	d += fabs(m_matrix[2][0] - other.m_matrix[2][0]);
	d += fabs(m_matrix[2][1] - other.m_matrix[2][1]);
	d += fabs(m_matrix[2][2] - other.m_matrix[2][2]);
	return d >= EPSILON;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other)
{
	return Matrix3x3(
		m_matrix[0][0] + other.m_matrix[0][0], m_matrix[0][1] + other.m_matrix[0][1], m_matrix[0][2] + other.m_matrix[0][2],
		m_matrix[1][0] + other.m_matrix[1][0], m_matrix[1][1] + other.m_matrix[1][1], m_matrix[1][2] + other.m_matrix[1][2],
		m_matrix[2][0] + other.m_matrix[2][0], m_matrix[2][1] + other.m_matrix[2][1], m_matrix[2][2] + other.m_matrix[2][2]
	);
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other)
{
	return Matrix3x3(
		m_matrix[0][0] - other.m_matrix[0][0], m_matrix[0][1] - other.m_matrix[0][1], m_matrix[0][2] - other.m_matrix[0][2],
		m_matrix[1][0] - other.m_matrix[1][0], m_matrix[1][1] - other.m_matrix[1][1], m_matrix[1][2] - other.m_matrix[1][2],
		m_matrix[2][0] - other.m_matrix[2][0], m_matrix[2][1] - other.m_matrix[2][1], m_matrix[2][2] - other.m_matrix[2][2]
	);
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other)
{
	Matrix3x3 result = Matrix3x3();

	result.m_matrix[0][0] = (m_matrix[0][0] * other.m_matrix[0][0]) + (m_matrix[0][1] * other.m_matrix[1][0]) + (m_matrix[0][2] * other.m_matrix[2][0]);
	result.m_matrix[0][1] = (m_matrix[0][0] * other.m_matrix[0][1]) + (m_matrix[0][1] * other.m_matrix[1][1]) + (m_matrix[0][2] * other.m_matrix[2][1]);
	result.m_matrix[0][2] = (m_matrix[0][0] * other.m_matrix[0][2]) + (m_matrix[0][1] * other.m_matrix[1][2]) + (m_matrix[0][2] * other.m_matrix[2][2]);

	result.m_matrix[1][0] = (m_matrix[1][0] * other.m_matrix[0][0]) + (m_matrix[1][1] * other.m_matrix[1][0]) + (m_matrix[1][2] * other.m_matrix[2][0]);
	result.m_matrix[1][1] = (m_matrix[1][0] * other.m_matrix[0][1]) + (m_matrix[1][1] * other.m_matrix[1][1]) + (m_matrix[1][2] * other.m_matrix[2][1]);
	result.m_matrix[1][2] = (m_matrix[1][0] * other.m_matrix[0][2]) + (m_matrix[1][1] * other.m_matrix[1][2]) + (m_matrix[1][2] * other.m_matrix[2][2]);

	result.m_matrix[2][0] = (m_matrix[2][0] * other.m_matrix[0][0]) + (m_matrix[2][1] * other.m_matrix[1][0]) + (m_matrix[2][2] * other.m_matrix[2][0]);
	result.m_matrix[2][1] = (m_matrix[2][0] * other.m_matrix[0][1]) + (m_matrix[2][1] * other.m_matrix[1][1]) + (m_matrix[2][2] * other.m_matrix[2][1]);
	result.m_matrix[2][2] = (m_matrix[2][0] * other.m_matrix[0][2]) + (m_matrix[2][1] * other.m_matrix[1][2]) + (m_matrix[2][2] * other.m_matrix[2][2]);

	return result;
}

Matrix3x3 Matrix3x3::operator*(const float scalar)
{
	return Matrix3x3(
		m_matrix[0][0] * scalar, m_matrix[0][1] * scalar, m_matrix[0][2] * scalar,
		m_matrix[1][0] * scalar, m_matrix[1][1] * scalar, m_matrix[1][2] * scalar,
		m_matrix[2][0] * scalar, m_matrix[2][1] * scalar, m_matrix[2][2] * scalar
	);
}

Matrix3x3 Matrix3x3::operator/(const float divisor)
{
	if (divisor == 0.0f)
		throw "Division by zero error!";

	return Matrix3x3(
		m_matrix[0][0] / divisor, m_matrix[0][1] / divisor, m_matrix[0][2] / divisor,
		m_matrix[1][0] / divisor, m_matrix[1][1] / divisor, m_matrix[1][2] / divisor,
		m_matrix[2][0] / divisor, m_matrix[2][1] / divisor, m_matrix[2][2] / divisor
	);
}


/* Vector2D operations */
Vector2D Matrix3x3::operator*(const Vector2D& other)
{
	return Vector2D(
		m_matrix[0][0] * other.m_x + m_matrix[0][1] * other.m_y + m_matrix[0][2] * other.m_w,
		m_matrix[1][0] * other.m_x + m_matrix[1][1] * other.m_y + m_matrix[1][2] * other.m_w,
		m_matrix[2][0] * other.m_x + m_matrix[2][1] * other.m_y + m_matrix[2][2] * other.m_w
	);
}


/* Vector3D operations */
Vector3D Matrix3x3::operator*(const Vector3D& other)
{
	return Vector3D(
		m_matrix[0][0] * other.m_x + m_matrix[0][1] * other.m_y + m_matrix[0][2] * other.m_z,
		m_matrix[1][0] * other.m_x + m_matrix[1][1] * other.m_y + m_matrix[1][2] * other.m_z,
		m_matrix[2][0] * other.m_x + m_matrix[2][1] * other.m_y + m_matrix[2][2] * other.m_z
	);
}
