/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix4x4.h
Purpose: Provides a 4 by 4 Matrix and associated functionality
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 9/29/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#define _USE_MATH_DEFINES
#include "Vector3D.h"

class Matrix4x4
{
private:
	float m_matrix[4][4];

public:
	Matrix4x4();
	Matrix4x4(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3, float x4, float y4, float z4, float w4);
	Matrix4x4(const Matrix4x4 &other); // Copy Ctor
	Matrix4x4& operator= (const Matrix4x4 &other); // Assignment Operator
	~Matrix4x4();

	float Get(int row, int col);
	void Set(int row, int col, float val);
	void Transpose();
	void Zero();
	void Identity();
	void Print();

	static Matrix4x4 Zero4D();
	static Matrix4x4 Identity4D();

	bool operator== (const  Matrix4x4& other);
	bool operator!= (const  Matrix4x4& other);
	Matrix4x4 operator+ (const Matrix4x4& other);
	Matrix4x4 operator- (const Matrix4x4& other);
	Matrix4x4 operator* (const Matrix4x4& other);
	Matrix4x4 operator* (const float scalar);
	Matrix4x4 operator/ (const float divisor);
	
	Vector3D operator* (const Vector3D& other);
};

#endif