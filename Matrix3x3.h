#pragma once

#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#define _USE_MATH_DEFINES
#include "Vector2D.h"
#include "Vector3D.h"
#include "math.h"
#include "Matrix.h"

class Matrix3x3 : public Matrix
{
public:
	Matrix3x3();
	Matrix3x3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	~Matrix3x3();

	void Transpose();

	static Matrix3x3 Zero3D();
	static Matrix3x3 Identity3D();

	bool operator== (const  Matrix3x3& other);
	bool operator!= (const  Matrix3x3& other);
	Matrix3x3 operator+ (const Matrix3x3& other);
	Matrix3x3 operator- (const Matrix3x3& other);
	Matrix3x3 operator* (const Matrix3x3& other);
	Matrix3x3 operator* (const float scalar);
	Matrix3x3 operator/ (const float divisor);

	Vector2D operator* (const Vector2D& other);

	Vector3D operator* (const Vector3D& other);
};

#endif