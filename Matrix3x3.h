/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix3x3.h
Purpose: Provides a 3 by 3 Matrix and associated functionality
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 9/29/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#define _USE_MATH_DEFINES
#include "Vector2D.h"
#include "Vector3D.h"

class Matrix3x3
{
private:
	float m_matrix[3][3];

public:
	Matrix3x3();
	Matrix3x3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	Matrix3x3(const Matrix3x3 &other); // Copy Ctor
	Matrix3x3& operator= (const Matrix3x3 &other); // Assignment Operator
	~Matrix3x3();

	float Get(int row, int col);
	void Set(int row, int col, float val);
	void Transpose();
	void Zero();
	void Identity();
	void Print();

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

void Matrix3x3Tests();
#endif