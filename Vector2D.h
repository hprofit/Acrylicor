/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector2D.h
Purpose: Provides a 2 Dimensional Vector (with w coordinate for Homogeneous uses)
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 9/29/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2D 
{
private:
	float m_x, m_y, m_w;

public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(float x, float y, float w);
	Vector2D(Vector2D const& rhs);
	Vector2D& operator= (Vector2D rhs);
	~Vector2D();

	void Set(float x, float y);
	void Set(float x, float y, float w);
	float getX() const { return m_x; };
	void setX(float x) { m_x = x; };
	float getY() const { return m_y; };
	void setY(float y) { m_y = y; };
	float getW() const { return m_w; };
	void setW(float w) { m_w = w; };

	operator float*();
	bool operator== (const  Vector2D& other) const;
	bool operator!= (const  Vector2D& other) const;
	Vector2D operator+ (const Vector2D& other) const;
	Vector2D& operator+= (const Vector2D& other);
	Vector2D operator- (const Vector2D& other) const;
	Vector2D& operator-= (const Vector2D& other);
	Vector2D operator* (const float scalar) const;
	Vector2D operator/ (const float divisor) const;

	void Add(const Vector2D& other);
	void Sub(const Vector2D& other);
	void Mul(const float scalar);
	void Div(const float divisor);
	void Print();

	void Zero();
	void Negate();
	float SquareLength();
	float Length();
	void Normalize();
	float GetRadians();
	float GetDegrees();

	static float SquareDistance(const Vector2D& vector0, const Vector2D& vector1);
	static float Distance(const Vector2D& vector0, const Vector2D& vector1);
	static Vector2D Normalize(Vector2D& vector);
	static float Dot(const Vector2D& vector0, const Vector2D& vector1);
	static Vector2D AngleRadians(float radians);
	static Vector2D AngleDegrees(float degrees);
};

void Vector2DTests();

#endif