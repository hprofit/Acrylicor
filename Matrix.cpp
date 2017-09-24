#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

#define EPSILON 0.0001

Matrix::Matrix(int rows, int cols)
{
	m_rows = rows;
	m_cols = cols;

	m_matrix = (float **)malloc(sizeof(float*) * rows);
	if (!m_matrix)
		throw "Not enough memory.";
	for(int row = 0; row < rows; row++) 
	{
		m_matrix[row] = (float *)malloc(sizeof(float) * cols);
		if (!m_matrix[row])
			throw "Not enough memory.";
	}
}

Matrix::Matrix(const Matrix &other)
{
	m_rows = other.m_rows;
	m_cols = other.m_cols;

	m_matrix = (float **)malloc(sizeof(float*) * m_rows);
	if (!m_matrix)
		throw "Not enough memory.";
	for (int row = 0; row < m_rows; row++)
	{
		m_matrix[row] = (float *)malloc(sizeof(float) * m_cols);
		if (!m_matrix[row])
			throw "Not enough memory.";
		for (int col = 0; col < m_cols; col++)
		{
			m_matrix[row][col] = other.m_matrix[row][col];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& other)
{
	// Free the original memory
	for (int row = 0; row < m_rows; row++)
	{
		free(m_matrix[row]);
	}
	free(m_matrix);

	// Re-set rows and columns
	m_rows = other.m_rows;
	m_cols = other.m_cols;

	// Re-allocate memory and set values
	m_matrix = (float **)malloc(sizeof(float*) * m_rows);
	if (!m_matrix)
		throw "Not enough memory.";
	for (int row = 0; row < m_rows; row++)
	{
		m_matrix[row] = (float *)malloc(sizeof(float) * m_cols);
		if (!m_matrix[row])
			throw "Not enough memory.";
		for (int col = 0; col < m_cols; col++)
		{
			m_matrix[row][col] = other.m_matrix[row][col];
		}
	}
	return *this;
}

Matrix::~Matrix()
{
	for (int row = 0; row < m_rows; row++)
	{
		free(m_matrix[row]);
	}
	free(m_matrix);
}

void Matrix::Transpose()
{
	// Make a copy of the Matrix's transposed form
	Matrix tmp = Matrix(m_cols, m_rows);
	for (int row = 0; row < m_rows; row++) 
	{
		for (int col = 0; col < m_cols; col++)
		{
			tmp.m_matrix[col][row] = m_matrix[row][col];
		}
	}
	// Free the original memory
	for (int row = 0; row < m_rows; row++)
	{
		free(m_matrix[row]);
	}
	free(m_matrix);
	// Flip rows and cols
	int rows = m_rows;
	m_rows = m_cols;
	m_cols = rows;

	// Re-initialize the Matrix's memory
	m_matrix = (float **)malloc(sizeof(float*) * m_rows);
	if (!m_matrix)
		throw "Not enough memory.";
	for (int row = 0; row < m_rows; row++)
	{
		m_matrix[row] = (float *)malloc(sizeof(float) * m_cols);
		if (!m_matrix[row])
			throw "Not enough memory.";
		// Copy tmp's values back into the Matrix
		for (int col = 0; col < m_cols; col++)
		{
			m_matrix[row][col] = tmp.m_matrix[row][col];
		}
	}
}

void Matrix::Print()
{
	for (int row = 0; row < m_rows; row++)
	{
		printf("(");
		for (int col = 0; col < m_cols; col++)
		{
			printf(" %f ", m_matrix[row][col]);
		}
		printf(")\n");
	}
	printf("\n");
}

void Matrix::Zero()
{
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			m_matrix[row][col] = 0.0f;
		}
	}
}

void Matrix::Identity()
{
	if (m_rows != m_cols)
		throw "Cannot create identity of a non-square Matrix.";

	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			m_matrix[row][col] = row == col ? 1.0f : 0.0f;
		}
	}
}

/* Matrix Operations */
bool Matrix::operator==(const Matrix& other)
{
	if (other.m_rows != m_rows || other.m_cols != m_cols) 
	{
		return false;
	}
	else 
	{ 
		float d = 0.0f;
		for (int row = 0; row < m_rows; row++)
		{
			for (int col = 0; col < m_cols; col++)
			{
				d += fabs(m_matrix[row][col] - other.m_matrix[row][col]);
			}
		}
		return d < EPSILON;
	}
}

bool Matrix::operator!=(const Matrix& other)
{
	if (other.m_rows != m_rows || other.m_cols != m_cols)
	{
		return true;
	}
	else
	{
		float d = 0.0f;
		for (int row = 0; row < m_rows; row++)
		{
			for (int col = 0; col < m_cols; col++)
			{
				d += fabs(m_matrix[row][col] - other.m_matrix[row][col]);
			}
		}
		return d >= EPSILON;
	}
}

Matrix Matrix::operator+(const Matrix& other)
{
	if (other.m_rows != m_rows || other.m_cols != m_cols)
		throw "Cannot add Matricies with differing numbers of rows or columns.";

	Matrix result = Matrix(m_rows, m_cols);
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			result.m_matrix[row][col] = m_matrix[row][col] + other.m_matrix[row][col];
		}
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& other)
{
	if (other.m_rows != m_rows || other.m_cols != m_cols)
		throw "Cannot subtract Matricies with differing numbers of rows or columns.";

	Matrix result = Matrix(m_rows, m_cols);
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			result.m_matrix[row][col] = m_matrix[row][col] - other.m_matrix[row][col];
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& other)
{
	// mXn * nXo
	// rowXcol * rowXcol
	if (other.m_rows != m_cols)
		throw "Cannot multiply Matricies with differing numbers of rows or columns.";

	// TODO: FIX 
	Matrix result = Matrix(m_rows, m_cols);
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			result.m_matrix[row][col] = 0.0f;
		}
	}
	return result;
}

Matrix Matrix::operator*(const float scalar)
{
	Matrix result = Matrix(m_rows, m_cols);
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			result.m_matrix[row][col] = m_matrix[row][col] * scalar;
		}
	}
	return result;
}

Matrix Matrix::operator/(const float divisor)
{
	if (divisor == 0.0f)
		throw "Division by zero error!";
	Matrix result = Matrix(m_rows, m_cols);
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			result.m_matrix[row][col] = m_matrix[row][col] / divisor;
		}
	}
	return result;
}

/* Vector2D operations */
bool Matrix::operator==(const Vector2D& other)
{
	if (m_rows != 2 || m_cols != 1)
	{
		return false;
	}
	else
	{
		float d = 0.0f;
		d += fabs(m_matrix[0][0] - other.m_x);
		d += fabs(m_matrix[1][0] - other.m_y);
		return d < EPSILON;
	}
}

bool Matrix::operator!=(const Vector2D& other)
{
	if (m_rows != 2 || m_cols != 1)
	{
		return true;
	}
	else
	{
		float d = 0.0f;
		d += fabs(m_matrix[0][0] - other.m_x);
		d += fabs(m_matrix[1][0] - other.m_y);
		return d >= EPSILON;
	}
}

Matrix Matrix::operator+(const Vector2D& other)
{
	if (m_rows != 2 || m_cols != 1)
		throw "Cannot add Matricies and Vector2D if the Matrix does not have 2 rows and 1 column.";

	Matrix result = Matrix(2, 1);
	result.m_matrix[0][0] = m_matrix[0][0] + other.m_x;
	result.m_matrix[1][0] = m_matrix[1][0] + other.m_y;
	return result;
}

Matrix Matrix::operator-(const Vector2D& other)
{
	if (m_rows != 2 || m_cols != 1)
		throw "Cannot subtract Matricies and Vector2D if the Matrix does not have 2 rows and 1 column.";

	Matrix result = Matrix(2, 1);
	result.m_matrix[0][0] = m_matrix[0][0] - other.m_x;
	result.m_matrix[1][0] = m_matrix[1][0] - other.m_y;
	return result;
}

Matrix Matrix::operator*(const Vector2D& other)
{
	// mXn * nXo
	// mX2 * 2X1
	if (m_cols != 2)
		throw "Cannot subtract Matricies and Vector2D if the Matrix does not have 2 columns.";

	Matrix result = Matrix(m_rows, 1);
	for (int row = 0; row < m_rows; row++)
	{
		result.m_matrix[row][0] = m_matrix[row][0] * other.m_x + m_matrix[row][1] * other.m_y;
	}
	return result;
}


/* Vector3D operations */
bool Matrix::operator==(const Vector3D& other)
{
	if (m_rows != 3 || m_cols != 1)
	{
		return false;
	}
	else
	{
		float d = 0.0f;
		d += fabs(m_matrix[0][0] - other.m_x);
		d += fabs(m_matrix[1][0] - other.m_y);
		d += fabs(m_matrix[2][0] - other.m_z);
		return d < EPSILON;
	}
}

bool Matrix::operator!=(const Vector3D& other)
{
	if (m_rows != 3 || m_cols != 1)
	{
		return true;
	}
	else
	{
		float d = 0.0f;
		d += fabs(m_matrix[0][0] - other.m_x);
		d += fabs(m_matrix[1][0] - other.m_y);
		d += fabs(m_matrix[2][0] - other.m_z);
		return d >= EPSILON;
	}
}

Matrix Matrix::operator+(const Vector3D& other)
{
	if (m_rows != 3 || m_cols != 1)
		throw "Cannot add Matricies and Vector3D if the Matrix does not have 3 rows and 1 column.";

	Matrix result = Matrix(3, 1);
	result.m_matrix[0][0] = m_matrix[0][0] + other.m_x;
	result.m_matrix[1][0] = m_matrix[1][0] + other.m_y;
	result.m_matrix[2][0] = m_matrix[2][0] + other.m_z;
	return result;
}

Matrix Matrix::operator-(const Vector3D& other)
{
	if (m_rows != 3 || m_cols != 1)
		throw "Cannot subtract Matricies and Vector3D if the Matrix does not have 3 rows and 1 column.";

	Matrix result = Matrix(3, 1);
	result.m_matrix[0][0] = m_matrix[0][0] - other.m_x;
	result.m_matrix[1][0] = m_matrix[1][0] - other.m_y;
	result.m_matrix[2][0] = m_matrix[2][0] - other.m_z;
	return result;
}

Matrix Matrix::operator*(const Vector3D& other)
{
	// mXn * nXo
	// mX3 * 3X1
	if (m_cols != 3)
		throw "Cannot subtract Matricies and Vector3D if the Matrix does not have 3 columns.";

	Matrix result = Matrix(m_rows, 1);
	for (int row = 0; row < m_rows; row++)
	{
		result.m_matrix[row][0] = m_matrix[row][0] * other.m_x + m_matrix[row][1] * other.m_y + m_matrix[row][2] * other.m_z;
	}
	return result;
}


/* Static Matrix Functions */
Matrix Matrix::Zero(int rows, int cols)
{
	Matrix zero = Matrix(rows, cols);

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			zero.m_matrix[row][col] = 0.0f;
		}
	}

	return zero;
}

Matrix Matrix::Identity(int rows_cols)
{
	Matrix identity = Matrix(rows_cols, rows_cols);

	for (int row = 0; row < rows_cols; row++)
	{
		for (int col = 0; col < rows_cols; col++)
		{
			identity.m_matrix[row][col] = row == col ? 1.0f : 0.0f;
		}
	}

	return identity;
}
