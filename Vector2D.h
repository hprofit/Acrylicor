#pragma once

#ifndef VECTOR2_H
#define VECTOR2_H

#define _USE_MATH_DEFINES
#include "math.h"

class Vector2D 
{
public:
	float m_x, m_y, m_w;

	Vector2D();
	Vector2D(float x, float y);
	Vector2D(float x, float y, float w);
	~Vector2D();

	bool operator== (const  Vector2D& other);
	bool operator!= (const  Vector2D& other);
	Vector2D operator+ (const Vector2D& other);
	Vector2D operator- (const Vector2D& other);
	Vector2D operator* (const float scalar);
	Vector2D operator/ (const float divisor);

	void Add(const Vector2D& other);
	void Sub(const Vector2D& other);
	void Mul(const float scalar);
	void Div(const float divisor);
	void Print();
	char * asString();

	void Zero();
	void Set(float x, float y);
	void Set(float x, float y, float w);
	void Negate();
	float SquareLength();
	float Length();
	static float SquareDistance(const Vector2D& vector0, const Vector2D& vector1);
	static float Distance(const Vector2D& vector0, const Vector2D& vector1);
	void Normalize();
	static Vector2D Normalize(Vector2D& vector);
	static float Dot(const Vector2D& vector0, const Vector2D& vector1);
	static Vector2D AngleRadians(float radians);
	static Vector2D AngleDegrees(float degrees);
};

#endif