#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

#define _USE_MATH_DEFINES
#include "math.h"

class Vector3D
{
public:
	float m_x, m_y, m_z, m_w;

	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(float x, float y, float z, float w);
	~Vector3D();

	bool operator== (const  Vector3D& other);
	bool operator!= (const  Vector3D& other);
	Vector3D operator+ (const Vector3D& other);
	Vector3D operator- (const Vector3D& other);
	Vector3D operator* (const float scalar);
	Vector3D operator/ (const float divisor);

	void Add(const Vector3D& other);
	void Sub(const Vector3D& other);
	void Mul(const float scalar);
	void Div(const float divisor);
	void Print();
	char * asString();

	void Zero();
	void Set(float x, float y, float z);
	void Set(float x, float y, float z, float w);
	void Negate();
	float SquareLength();
	float Length();
	static float SquareDistance(const Vector3D& vector0, const Vector3D& vector1);
	static float Distance(const Vector3D& vector0, const Vector3D& vector1);
	void Normalize();
	static Vector3D Normalize(Vector3D& vector);
	static float Dot(const Vector3D& vector0, const Vector3D& vector1);
	static Vector3D Cross(const Vector3D& vector0, const Vector3D& vector1);
	static Vector3D AngleRadians(float radians, Vector3D& axis);
	static Vector3D AngleDegrees(float degrees, Vector3D& axis);
};

#endif