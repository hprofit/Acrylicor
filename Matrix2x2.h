#pragma once

#ifndef MATRIX2X2_H
#define MATRIX2X2_H

#define _USE_MATH_DEFINES
#include "Vector2D.h"
#include "math.h"
#include "Matrix.h"

class Matrix2x2 : public Matrix
{
public:
	Matrix2x2();
	Matrix2x2(float x1, float y1, float x2, float y2);
	Matrix2x2(const Matrix2x2 &other); // Copy Constructor
	Matrix2x2& operator= (const Matrix2x2 &other); // Assignment Operator
	~Matrix2x2();

	void Transpose();
	void Zero();
	void Identity();

	static Matrix2x2 Zero2D();
	static Matrix2x2 Identity2D();

	bool operator== (const  Matrix2x2& other);
	bool operator!= (const  Matrix2x2& other);
	Matrix2x2 operator+ (const Matrix2x2& other);
	Matrix2x2 operator- (const Matrix2x2& other);
	Matrix2x2 operator* (const Matrix2x2& other);
	Matrix2x2 operator* (const float scalar);
	Matrix2x2 operator/ (const float divisor);

	Vector2D operator* (const Vector2D& other);
};

#endif