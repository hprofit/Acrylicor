#define _USE_MATH_DEFINES
#define EPSILON 0.0001f
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Math2D.h"

#define PASS "PASS"
#define FAIL "!!!!! FAIL !!!!!"

void Vector2DTests()
{
	printf("\n========== Running Vector2D tests ==========\n\n");

	Vector2D * createdVector = new Vector2D();
	printf("Created Vector(): %s\n", (createdVector->m_x == 0.0f && createdVector->m_y == 0.0f && createdVector->m_w == 1.0f) ? PASS : FAIL);
	delete createdVector;

	createdVector = new Vector2D(1.0f, 2.0f);
	printf("Created Vector(x, y): %s\n", (createdVector->m_x == 1.0f && createdVector->m_y == 2.0f && createdVector->m_w == 1.0f) ? PASS : FAIL);
	delete createdVector;

	createdVector = new Vector2D(2.0f, 3.0f, 0.0f);
	printf("Created Vector(x, y, w): %s\n", (createdVector->m_x == 2.0f && createdVector->m_y == 3.0f && createdVector->m_w == 0.0f) ? PASS : FAIL);
	delete createdVector;

	Vector2D v1, v2, v3, result;
	float scalar, angle;
	
	v1.m_x = 1.0f;		v1.m_y = 2.0f;
	v2.m_x = 1.0f;		v2.m_y = 2.0f;
	printf("Vector2D == equal: %s\n", (v1 == v2) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 2.0f;
	v2.m_x = 1.1f;		v2.m_y = 2.0f;
	printf("Vector2D == not equal: %s\n", (v1 == v2) ? FAIL : PASS);

	v1.m_x = 1.0f;		v1.m_y = 2.0f;
	v2.m_x = 2.0f;		v2.m_y = 3.0f;
	printf("Vector2D != not equal: %s\n", (v1 != v2) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 2.0f;
	v2.m_x = 1.0f;		v2.m_y = 2.0f;
	printf("Vector2D != equal: %s\n", (v1 != v2) ? FAIL : PASS);

	v1.m_x = 0.1f;		v1.m_y = 2.0f;
	v2.m_x = 1.0f;		v2.m_y = 3.5f;
	result.m_x = 1.1f;	result.m_y = 5.5f;
	printf("Vector2D +: %s\n", (v1 + v2 == result) ? PASS : FAIL);

	v1.m_x = -0.1f;		v1.m_y = 1.0f;
	v2.m_x = 1.0f;		v2.m_y = -2.0f;
	result.m_x = 0.9f;	result.m_y = -1.0f;
	printf("Vector2D +: %s\n", (v1 + v2 == result) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 2.0f;
	v2.m_x = 1.0f;		v2.m_y = -2.0f;
	result.m_x = 0.0f;	result.m_y = 4.0f;
	printf("Vector2D -: %s\n", (v1 - v2 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;
	v2.m_x = -2.0f;		v2.m_y = 2.0f;
	result.m_x = 0.0f;	result.m_y = 0.5f;
	printf("Vector2D -: %s\n", (v1 - v2 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;
	scalar = 2.0f;
	result.m_x = -4.0f;	result.m_y = 5.0f;
	printf("Vector2D *: %s\n", (v1 * scalar == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;
	scalar = 0.5f;
	result.m_x = -1.0f;	result.m_y = 1.25f;
	printf("Vector2D *: %s\n", (v1 * scalar == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 10.0f;
	scalar = 2.0f;
	result.m_x = -1.0f;	result.m_y = 5.0f;
	printf("Vector2D /: %s\n", (v1 / scalar == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 10.0f;
	scalar = 0.5f;
	result.m_x = -4.0f;	result.m_y = 20.0f;
	printf("Vector2D /: %s\n", (v1 / scalar == result) ? PASS : FAIL);

	v1.m_x = 0.1f;		v1.m_y = 2.0f;
	v2.m_x = 1.0f;		v2.m_y = 3.5f;
	result.m_x = 1.1f;	result.m_y = 5.5f;
	v1.Add(v2);
	printf("Vector2D Add: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -0.1f;		v1.m_y = 1.0f;
	v2.m_x = 1.0f;		v2.m_y = -2.0f;
	result.m_x = 0.9f;	result.m_y = -1.0f;
	v1.Add(v2);
	printf("Vector2D Add: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 2.0f;
	v2.m_x = 1.0f;		v2.m_y = -2.0f;
	result.m_x = 0.0f;	result.m_y = 4.0f;
	v1.Sub(v2);
	printf("Vector2D Sub: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;
	v2.m_x = -2.0f;		v2.m_y = 2.0f;
	result.m_x = 0.0f;	result.m_y = 0.5f;
	v1.Sub(v2);
	printf("Vector2D Sub: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;
	scalar = 2.0f;
	result.m_x = -4.0f;	result.m_y = 5.0f;
	v1.Mul(scalar);
	printf("Vector2D Mul: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;
	scalar = 0.5f;
	result.m_x = -1.0f;	result.m_y = 1.25f;
	v1.Mul(scalar);
	printf("Vector2D Mul: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 10.0f;
	scalar = 2.0f;
	result.m_x = -1.0f;	result.m_y = 5.0f;
	v1.Div(scalar);
	printf("Vector2D Div: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 10.0f;
	scalar = 0.5f;
	result.m_x = -4.0f;	result.m_y = 20.0f;
	v1.Div(scalar);
	printf("Vector2D Div: %s\n", (v1 == result) ? PASS : FAIL);
	
	v1.m_x = 1.0f;		v1.m_y = 1.0f;
	result.m_x = 0.0f;	result.m_y = 0.0f;
	v1.Zero();
	printf("Vector2D Zero: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 0.0f;		v1.m_y = 0.0f;		v1.m_w = 1.0f;
	result.m_x = 1.0f;	result.m_y = 2.0f;	result.m_w = 1.0f;
	v1.Set(1.0f, 2.0f);
	printf("Vector2D Set(x, y): %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 0.0f;		v1.m_y = 0.0f;		v1.m_w = 0.0f;
	result.m_x = 1.0f;	result.m_y = 2.0f;	result.m_w = 1.0f;
	v1.Set(1.0f, 2.0f, 1.0f);
	printf("Vector2D Set(x, y, w): %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = -1.0f;		v1.m_w = 1.0f;
	result.m_x = -1.0f;	result.m_y = 1.0f;	result.m_w = 1.0f;
	v1.Negate();
	printf("Vector2D Negate: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -1.0f;		v1.m_y = 0.0f;		v1.m_w = 1.0f;
	result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	v1.Negate();
	printf("Vector2D Negate: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;
	printf("Vector2D SquareLength: %s\n", (v1.SquareLength() == 25.0) ? PASS : FAIL);

	v1.m_x = -4.0f;		v1.m_y = 3.0f;
	printf("Vector2D Length: %s\n", (v1.Length() == 5.0) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;
	v2.m_x = 3.0f;		v2.m_y = -4.0f;
	printf("Vector2D SquareDistance: %s\n", (Vector2D::SquareDistance(v1, v2) == 100.0f) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;
	v2.m_x = 3.0f;		v2.m_y = -4.0f;
	printf("Vector2D Distance: %s\n", ((Vector2D::Distance(v1, v2) - 10.0f) < EPSILON) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;
	result.m_x = -0.6f;	result.m_y = 0.8f;
	v1.Normalize();
	printf("Vector2D Normalize: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 3.0f;		v1.m_y = -4.0f;
	v1.Normalize();
	printf("Vector2D Normalize Length Check: %s\n", (v1.Length() == 1.0f) ? PASS : FAIL);

	v1.m_x = 3.0f;		v1.m_y = -4.0f;
	result.m_x = 0.6f;	result.m_y = -0.8f;
	printf("Vector2D Normalize(vector): %s\n", (Vector2D::Normalize(v1) == result) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;
	printf("Vector2D Normalize(vector) Length Check: %s\n", (Vector2D::Normalize(v1).Length() == 1.0f) ? PASS : FAIL);

	v1.m_x = 2.0f;		v1.m_y = 3.0f;
	v2.m_x = 4.0f;		v2.m_y = 5.0f;
	printf("Vector2D Dot: %s\n", ((Vector2D::Dot(v1, v2) - 23.0f) < EPSILON) ? PASS : FAIL);

	result.m_x = 0.707106f;	result.m_y = 0.707106f;	result.m_w = 1.0f;
	angle = M_PI_4;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.m_x = 0.0f;	result.m_y = 1.0f;	result.m_w = 1.0f;
	angle = M_PI_2;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.m_x = -1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	angle = M_PI;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.m_x = -1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	angle = -M_PI;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.m_x = 0.0f;	result.m_y = -1.0f;	result.m_w = 1.0f;
	angle = 1.5f * M_PI;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	angle = 2.0f * M_PI;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	angle = 0.0f;
	printf("Vector2D AngleRadians (%f): %s\n", angle, (Vector2D::AngleRadians(angle) == result) ? PASS : FAIL);

	result.m_x = 0.707106f;	result.m_y = 0.707106f;	result.m_w = 1.0f;
	angle = 45.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.m_x = 0.0f;	result.m_y = 1.0f;	result.m_w = 1.0f;
	angle = 90.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.m_x = -1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	angle = 180.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.m_x = -1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	angle = -180.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.m_x = 0.0f;	result.m_y = -1.0f;	result.m_w = 1.0f;
	angle = 270.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	angle = 360.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);

	result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	angle = 0.0f;
	printf("Vector2D AngleDegrees (%f): %s\n", angle, (Vector2D::AngleDegrees(angle) == result) ? PASS : FAIL);
}

void Vector3DTests()
{
	printf("\n========== Running Vector3D tests ==========\n\n");

	Vector3D * createdVector = new Vector3D();
	printf("Created Vector(): %s\n", (createdVector->m_x == 0.0f && createdVector->m_y == 0.0f && createdVector->m_w == 1.0f) ? PASS : FAIL);
	delete createdVector;

	createdVector = new Vector3D(1.0f, 2.0f, 3.0f);
	printf("Created Vector(x, y): %s\n", (createdVector->m_x == 1.0f && createdVector->m_y == 2.0f && createdVector->m_z == 3.0f && createdVector->m_w == 1.0f) ? PASS : FAIL);
	delete createdVector;

	createdVector = new Vector3D(2.0f, 3.0f, 4.0f, 0.0f);
	printf("Created Vector(x, y, w): %s\n", (createdVector->m_x == 2.0f && createdVector->m_y == 3.0f && createdVector->m_z == 4.0f && createdVector->m_w == 0.0f) ? PASS : FAIL);
	delete createdVector;

	Vector3D v1, v2, v3, result;
	float scalar;//, angle;

	v1.m_x = 1.0f;		v1.m_y = 2.0f;		v1.m_z = 3.0f;
	v2.m_x = 1.0f;		v2.m_y = 2.0f;		v2.m_z = 3.0f;
	printf("Vector3D == equal: %s\n", (v1 == v2) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 2.0f;		v1.m_z = 3.0f;
	v2.m_x = 1.1f;		v2.m_y = 2.0f;		v2.m_z = 3.0f;
	printf("Vector3D == not equal: %s\n", (v1 == v2) ? FAIL : PASS);

	v1.m_x = 1.0f;		v1.m_y = 2.0f;		v1.m_z = 3.0f;
	v2.m_x = 2.0f;		v2.m_y = 3.0f;		v2.m_z = 4.0f;
	printf("Vector3D != not equal: %s\n", (v1 != v2) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 2.0f;		v1.m_z = 3.0f;
	v2.m_x = 1.0f;		v2.m_y = 2.0f;		v2.m_z = 3.0f;
	printf("Vector3D != equal: %s\n", (v1 != v2) ? FAIL : PASS);

	v1.m_x = 0.1f;		v1.m_y = 2.0f;		v1.m_z = 1.0f;
	v2.m_x = 1.0f;		v2.m_y = 3.5f;		v2.m_z = -3.0f;
	result.m_x = 1.1f;	result.m_y = 5.5f;	result.m_z = -2.0f;
	printf("Vector3D +: %s\n", (v1 + v2 == result) ? PASS : FAIL);

	v1.m_x = -0.1f;		v1.m_y = 1.0f;		v1.m_z = -1.0f;
	v2.m_x = 1.0f;		v2.m_y = -2.0f;		v2.m_z = 1.0f;
	result.m_x = 0.9f;	result.m_y = -1.0f;	result.m_z = 0.0f;
	printf("Vector3D +: %s\n", (v1 + v2 == result) ? PASS : FAIL);
	
	v1.m_x = 1.0f;		v1.m_y = 2.0f;		v1.m_z = -1.0f;
	v2.m_x = 1.0f;		v2.m_y = -2.0f;		v2.m_z = -1.0f;
	result.m_x = 0.0f;	result.m_y = 4.0f;	result.m_z = 0.0f;
	printf("Vector3D -: %s\n", (v1 - v2 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;		v1.m_z = 1.0f;
	v2.m_x = -2.0f;		v2.m_y = 2.0f;		v2.m_z = -1.0f;
	result.m_x = 0.0f;	result.m_y = 0.5f;	result.m_z = 2.0f;
	printf("Vector3D -: %s\n", (v1 - v2 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;		v1.m_z = 1.0f;
	scalar = 2.0f;
	result.m_x = -4.0f;	result.m_y = 5.0f;	result.m_z = 2.0f;
	printf("Vector3D *: %s\n", (v1 * scalar == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;		v1.m_z = 1.0f;
	scalar = 0.5f;
	result.m_x = -1.0f;	result.m_y = 1.25f;	result.m_z = 0.5f;
	printf("Vector3D *: %s\n", (v1 * scalar == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 10.0f;		v1.m_z = 4.5f;
	scalar = 2.0f;
	result.m_x = -1.0f;	result.m_y = 5.0f;	result.m_z = 2.25f;
	printf("Vector3D /: %s\n", (v1 / scalar == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 10.0f;		v1.m_z = 1.0f;
	scalar = 0.5f;
	result.m_x = -4.0f;	result.m_y = 20.0f;	result.m_z = 2.0f;
	printf("Vector3D /: %s\n", (v1 / scalar == result) ? PASS : FAIL);

	v1.m_x = 0.1f;		v1.m_y = 2.0f;		v1.m_z = 1.0f;
	v2.m_x = 1.0f;		v2.m_y = 3.5f;		v2.m_z = -3.0f;
	result.m_x = 1.1f;	result.m_y = 5.5f;	result.m_z = -2.0f;
	v1.Add(v2);
	printf("Vector3D Add: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -0.1f;		v1.m_y = 1.0f;		v1.m_z = -1.0f;
	v2.m_x = 1.0f;		v2.m_y = -2.0f;		v2.m_z = 1.0f;
	result.m_x = 0.9f;	result.m_y = -1.0f;	result.m_z = 0.0f;
	v1.Add(v2);
	printf("Vector3D Add: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 2.0f;		v1.m_z = -1.0f;
	v2.m_x = 1.0f;		v2.m_y = -2.0f;		v2.m_z = -1.0f;
	result.m_x = 0.0f;	result.m_y = 4.0f;	result.m_z = 0.0f;
	v1.Sub(v2);
	printf("Vector3D Sub: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;		v1.m_z = 1.0f;
	v2.m_x = -2.0f;		v2.m_y = 2.0f;		v2.m_z = -1.0f;
	result.m_x = 0.0f;	result.m_y = 0.5f;	result.m_z = 2.0f;
	v1.Sub(v2);
	printf("Vector3D Sub: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;		v1.m_z = 1.0f;
	scalar = 2.0f;
	result.m_x = -4.0f;	result.m_y = 5.0f;	result.m_z = 2.0f;
	v1.Mul(scalar);
	printf("Vector3D Mul: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 2.5f;		v1.m_z = 1.0f;
	scalar = 0.5f;
	result.m_x = -1.0f;	result.m_y = 1.25f;	result.m_z = 0.5f;
	v1.Mul(scalar);
	printf("Vector3D Mul: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 10.0f;		v1.m_z = 4.5f;
	scalar = 2.0f;
	result.m_x = -1.0f;	result.m_y = 5.0f;	result.m_z = 2.25f;
	v1.Div(scalar);
	printf("Vector3D Div: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -2.0f;		v1.m_y = 10.0f;		v1.m_z = 1.0f;
	scalar = 0.5f;
	result.m_x = -4.0f;	result.m_y = 20.0f;	result.m_z = 2.0f;
	v1.Div(scalar);
	printf("Vector3D Div: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 1.0f;		v1.m_z = 1.0f;
	result.m_x = 0.0f;	result.m_y = 0.0f;	result.m_z = 0.0f;
	v1.Zero();
	printf("Vector3D Zero: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 0.0f;		v1.m_y = 0.0f;		v1.m_z = 0.0f;		v1.m_w = 1.0f;
	result.m_x = 1.0f;	result.m_y = 2.0f;	result.m_z = 3.0f;	result.m_w = 1.0f;
	v1.Set(1.0f, 2.0f, 3.0f);
	printf("Vector3D Set(x, y, z): %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 0.0f;		v1.m_y = 0.0f;		v1.m_z = 0.0f;		v1.m_w = 1.0f;
	result.m_x = 1.0f;	result.m_y = 2.0f;	result.m_z = 3.0f;	result.m_w = 1.0f;
	v1.Set(1.0f, 2.0f, 3.0f, 1.0f);
	printf("Vector3D Set(x, y, z, w): %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = -1.0f;		v1.m_z = 1.0f;		v1.m_w = 1.0f;
	result.m_x = -1.0f;	result.m_y = 1.0f;	result.m_z = -1.0f;	result.m_w = 1.0f;
	v1.Negate();
	printf("Vector3D Negate: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -1.0f;		v1.m_y = 0.0f;		v1.m_z = -1.0f;		v1.m_w = 1.0f;
	result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_z = 1.0f;	result.m_w = 1.0f;
	v1.Negate();
	printf("Vector3D Negate: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;		v1.m_z = 5.0f;
	printf("Vector3D SquareLength: %s\n", (v1.SquareLength() == 50.0f) ? PASS : FAIL);

	v1.m_x = -4.0f;		v1.m_y = 3.0f;		v1.m_z = -5.0f;
	printf("Vector3D Length: %s\n", (v1.Length() == 7.0710678f) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;		v1.m_z = 5.0f;
	v2.m_x = 3.0f;		v2.m_y = -4.0f;		v2.m_z = -5.0f;
	printf("Vector3D SquareDistance: %s\n", (Vector3D::SquareDistance(v1, v2) == 200.0f) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;		v1.m_z = 5.0f;
	v2.m_x = 3.0f;		v2.m_y = -4.0f;		v2.m_z = -5.0f;
	printf("Vector3D Distance: %s\n", ((Vector3D::Distance(v1, v2) - 14.1421356f) < EPSILON) ? PASS : FAIL);

	v1.m_x = -3.0f;				v1.m_y = 4.0f;			v1.m_z = 5.0f;
	result.m_x = -0.424264f;	result.m_y = 0.565685f;	result.m_z = 0.707107f;
	v1.Normalize();
	printf("Vector3D Normalize: %s\n", (v1 == result) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;		v1.m_z = -5.0f;
	v1.Normalize();
	printf("Vector3D Normalize Length Check: %s\n", (v1.Length() == 1.0f) ? PASS : FAIL);

	v1.m_x = -3.0f;				v1.m_y = 4.0f;			v1.m_z = 5.0f;
	result.m_x = -0.424264f;	result.m_y = 0.565685f;	result.m_z = 0.707107f;
	printf("Vector3D Normalize(vector): %s\n", (Vector3D::Normalize(v1) == result) ? PASS : FAIL);

	v1.m_x = -3.0f;		v1.m_y = 4.0f;		v1.m_z = -5.0f;
	printf("Vector3D Normalize(vector) Length Check: %s\n", (Vector3D::Normalize(v1).Length() == 1.0f) ? PASS : FAIL);

	v1.m_x = 2.0f;		v1.m_y = 3.0f;		v1.m_z = 3.0f;
	v2.m_x = 4.0f;		v2.m_y = 5.0f;		v2.m_z = 3.0f;
	printf("Vector3D Dot: %s\n", ((Vector3D::Dot(v1, v2) - 32.0f) < EPSILON) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 0.0f;		v1.m_z = 0.0f;
	v2.m_x = 0.0f;		v2.m_y = 1.0f;		v2.m_z = 0.0f;
	result.m_x = 0.0f;	result.m_y = 0.0f;	result.m_z = 1.0f;
	printf("Vector3D Cross: %s\n", (Vector3D::Cross(v1, v2) == result) ? PASS : FAIL);

	v1.m_x = 1.0f;		v1.m_y = 0.0f;		v1.m_z = 0.0f;
	v2.m_x = 0.0f;		v2.m_y = 0.0f;		v2.m_z = -1.0f;
	result.m_x = 0.0f;	result.m_y = 1.0f;	result.m_z = 0.0f;
	printf("Vector3D Cross: %s\n", (Vector3D::Cross(v1, v2) == result) ? PASS : FAIL);

	v1.m_x = 0.0f;		v1.m_y = 1.0f;		v1.m_z = 0.0f;
	v2.m_x = 0.0f;		v2.m_y = 0.0f;		v2.m_z = 1.0f;
	result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_z = 0.0f;
	printf("Vector3D Cross: %s\n", (Vector3D::Cross(v1, v2) == result) ? PASS : FAIL);

	//result.m_x = 0.707106f;	result.m_y = 0.707106f;	result.m_w = 1.0f;
	//angle = M_PI_4;
	//printf("Vector3D AngleRadians (%f): %s\n", angle, (Vector3D::AngleRadians(angle) == result) ? PASS : FAIL);

	//result.m_x = 0.0f;	result.m_y = 1.0f;	result.m_w = 1.0f;
	//angle = M_PI_2;
	//printf("Vector3D AngleRadians (%f): %s\n", angle, (Vector3D::AngleRadians(angle) == result) ? PASS : FAIL);

	//result.m_x = -1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	//angle = M_PI;
	//printf("Vector3D AngleRadians (%f): %s\n", angle, (Vector3D::AngleRadians(angle) == result) ? PASS : FAIL);

	//result.m_x = -1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	//angle = -M_PI;
	//printf("Vector3D AngleRadians (%f): %s\n", angle, (Vector3D::AngleRadians(angle) == result) ? PASS : FAIL);

	//result.m_x = 0.0f;	result.m_y = -1.0f;	result.m_w = 1.0f;
	//angle = 1.5f * M_PI;
	//printf("Vector3D AngleRadians (%f): %s\n", angle, (Vector3D::AngleRadians(angle) == result) ? PASS : FAIL);

	//result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	//angle = 2.0f * M_PI;
	//printf("Vector3D AngleRadians (%f): %s\n", angle, (Vector3D::AngleRadians(angle) == result) ? PASS : FAIL);

	//result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	//angle = 0.0f;
	//printf("Vector3D AngleRadians (%f): %s\n", angle, (Vector3D::AngleRadians(angle) == result) ? PASS : FAIL);

	//result.m_x = 0.707106f;	result.m_y = 0.707106f;	result.m_w = 1.0f;
	//angle = 45.0f;
	//printf("Vector3D AngleDegrees (%f): %s\n", angle, (Vector3D::AngleDegrees(angle) == result) ? PASS : FAIL);

	//result.m_x = 0.0f;	result.m_y = 1.0f;	result.m_w = 1.0f;
	//angle = 90.0f;
	//printf("Vector3D AngleDegrees (%f): %s\n", angle, (Vector3D::AngleDegrees(angle) == result) ? PASS : FAIL);

	//result.m_x = -1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	//angle = 180.0f;
	//printf("Vector3D AngleDegrees (%f): %s\n", angle, (Vector3D::AngleDegrees(angle) == result) ? PASS : FAIL);

	//result.m_x = -1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	//angle = -180.0f;
	//printf("Vector3D AngleDegrees (%f): %s\n", angle, (Vector3D::AngleDegrees(angle) == result) ? PASS : FAIL);

	//result.m_x = 0.0f;	result.m_y = -1.0f;	result.m_w = 1.0f;
	//angle = 270.0f;
	//printf("Vector3D AngleDegrees (%f): %s\n", angle, (Vector3D::AngleDegrees(angle) == result) ? PASS : FAIL);

	//result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	//angle = 360.0f;
	//printf("Vector3D AngleDegrees (%f): %s\n", angle, (Vector3D::AngleDegrees(angle) == result) ? PASS : FAIL);

	//result.m_x = 1.0f;	result.m_y = 0.0f;	result.m_w = 1.0f;
	//angle = 0.0f;
	//printf("Vector3D AngleDegrees (%f): %s\n", angle, (Vector3D::AngleDegrees(angle) == result) ? PASS : FAIL);
}

void MatrixTests()
{
	printf("\n========== Running Matrix tests ==========\n\n");

	#pragma region Methods
	Matrix m0 = Matrix(4, 4);
	Matrix m1 = Matrix(4, 4);
	long i, j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = i * 2 + j;
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m1.m_matrix[i][j] = i + j * 2;
	
	m1.Transpose();
	printf("Matrix Transpose: %s\n", (m0 == m1) ? PASS : FAIL);

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = 0.0f;

	m1.Zero();
	printf("Matrix Zero: %s\n", (m0 == m1) ? PASS : FAIL);

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = i == j ? 1.0f : 0.0f;

	m1.Identity();
	printf("Matrix Identity: %s\n", (m0 == m1) ? PASS : FAIL);
	#pragma endregion Methods
	#pragma region StaticMethods
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = 0.0f;

	Matrix zero = Matrix::Zero(4, 4);
	printf("Matrix::Zero: %s\n", (zero == m0) ? PASS : FAIL);

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = i == j ? 1.0f : 0.0f;

	Matrix identity = Matrix::Identity(4);
	printf("Matrix::Identity: %s\n", (m0 == identity) ? PASS : FAIL);
	#pragma endregion StaticMethods
	#pragma region Operations
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m1.m_matrix[i][j] = i - j;
	printf("Matrix == Matrix equal: %s\n", (m0 == m0) ? PASS : FAIL);

	printf("Matrix == Matrix not equal: %s\n", (m0 == m1) ? FAIL : PASS);

	printf("Matrix != Matrix not equal: %s\n", (m0 != m1) ? PASS : FAIL);

	printf("Matrix != Matrix equal: %s\n", (m0 != m0) ? FAIL : PASS);

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m1.m_matrix[i][j] = -(i + j);

	printf("Matrix +: %s\n", (zero == m0 + m1) ? PASS : FAIL);

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m1.m_matrix[i][j] = i + j;

	printf("Matrix -: %s\n", (zero == m0 - m1) ? PASS : FAIL);


	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m1.m_matrix[i][j] = i + j;

	printf("Matrix * Matrix: %s\n", FAIL);// (zero == m0 * m1) ? PASS : FAIL);

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m1.m_matrix[i][j] = (i + j) * 2.0f;

	printf("Matrix * scalar: %s\n", ((m0 * 2.0f) == m1) ? PASS : FAIL);

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m1.m_matrix[i][j] = (i + j) / 2.0f;

	printf("Matrix / divisor: %s\n", ((m0 / 2.0f) == m1) ? PASS : FAIL);
	#pragma endregion Operations
	#pragma region Vector2D
	printf("\n========== Running Matrix - Vector2D tests ==========\n\n");

	Matrix x21 = Matrix(2, 1);
	Matrix x22 = Matrix(2, 2);
	Matrix x21Test = Matrix(2, 1);
	Vector2D v2 = Vector2D(1, 2);

	x21.m_matrix[0][0] = 1.0f;
	x21.m_matrix[1][0] = 2.0f;
	v2.m_x = 1.0f;	v2.m_y = 2.0f;
	printf("Matrix(2X1) == Vector2D equal: %s\n", (x21 == v2) ? PASS : FAIL);

	v2.m_x = 2.0f;	v2.m_y = 1.0f;
	printf("Matrix(2X1) == Vector2D not equal: %s\n", (x21 == v2) ? FAIL : PASS);

	v2.m_x = 0.0f;	v2.m_y = 0.0f;	v2.m_w = 0.0f;
	printf("Matrix(mXn) == Vector2D where (m != 2 and n != 1): %s\n", (x22 == v2) ? FAIL : PASS);

	v2.m_x = 2.0f;	v2.m_y = 1.0f;
	printf("Matrix(2X1) != Vector2D not equal: %s\n", (x21 != v2) ? PASS : FAIL);

	v2.m_x = 1.0f;	v2.m_y = 2.0f;
	printf("Matrix(2X1) != Vector2D equal: %s\n", (x21 != v2) ? FAIL : PASS);

	v2.m_x = 0.0f;	v2.m_y = 0.0f;	v2.m_w = 0.0f;
	printf("Matrix(mXn) != Vector2D where (m != 2 and n != 1): %s\n", (x22 != v2) ? PASS : FAIL);


	x21.m_matrix[0][0] = 1.0f;
	x21.m_matrix[1][0] = 2.0f;
	v2.m_x = 1.0f;	v2.m_y = 2.0f;

	x21Test.m_matrix[0][0] = 2.0f;
	x21Test.m_matrix[1][0] = 4.0f;
	printf("Matrix(2X1) + Vector2D: %s\n", ((x21 + v2) == x21Test) ? PASS : FAIL);

	try {
		x22 + v2;
		printf("Matrix(mXn) + Vector2D where n != 2: %s\n", FAIL);
	}
	catch (...) {
		printf("Matrix(mXn) + Vector2D where n != 2: %s\n", PASS);
	}


	x21.m_matrix[0][0] = 1.0f;
	x21.m_matrix[1][0] = 2.0f;
	v2.m_x = 1.0f;	v2.m_y = 2.0f;

	x21Test.m_matrix[0][0] = 0.0f;
	x21Test.m_matrix[1][0] = 0.0f;
	printf("Matrix(2X1) - Vector2D: %s\n", ((x21 - v2) == x21Test) ? PASS : FAIL);

	try {
		x22 - v2;
		printf("Matrix(mXn) - Vector2D where n != 2: %s\n", FAIL);
	}
	catch (...) {
		printf("Matrix(mXn) - Vector2D where n != 2: %s\n", PASS);
	}


	x22.m_matrix[0][0] = 1.0f;
	x22.m_matrix[0][1] = 2.0f;
	x22.m_matrix[1][0] = 3.0f;
	x22.m_matrix[1][1] = 4.0f;
	v2.m_x = 2.0f;	v2.m_y = 3.0f;

	x21Test.m_matrix[0][0] = 8.0f;
	x21Test.m_matrix[1][0] = 18.0f;
	printf("Matrix(2X2) * Vector2D: %s\n", ((x22 * v2) == x21Test) ? PASS : FAIL);

	try {
		x21 * v2;
		printf("Matrix(mXn) - Vector2D where n != 2: %s\n", FAIL);
	}
	catch (...) {
		printf("Matrix(mXn) - Vector2D where n != 2: %s\n", PASS);
	}

	#pragma endregion Vector2D
	#pragma region Vector3D
	printf("\n========== Running Matrix - Vector3D tests ==========\n\n");
	Matrix x31 = Matrix(3, 1);
	Matrix x33 = Matrix(3, 3);
	Matrix x31Test = Matrix(3, 1);
	Vector3D v3 = Vector3D(1, 2, 3);

	x31.m_matrix[0][0] = 1.0f;
	x31.m_matrix[1][0] = 2.0f;
	x31.m_matrix[2][0] = 3.0f;
	printf("Matrix(3X1) == Vector3D equal: %s\n", (x31 == v3) ? PASS : FAIL);

	x31.m_matrix[0][0] = 2.0f;
	printf("Matrix(3X1) == Vector3D not equal: %s\n", (x31 == v3) ? FAIL : PASS);

	v3.m_x = 0.0f;	v3.m_y = 0.0f;	v3.m_z = 0.0f;	v3.m_w = 0.0f;
	printf("Matrix(mXn) == Vector3D where (m != 3 and n != 1): %s\n", (x33 == v3) ? FAIL : PASS);

	x31.m_matrix[0][0] = 1.0f;
	x31.m_matrix[1][0] = 2.0f;
	x31.m_matrix[2][0] = 3.0f;
	printf("Matrix(3X1) != Vector3D not equal: %s\n", (x31 != v3) ? PASS : FAIL);

	v3.m_x = 1.0f;	v3.m_y = 2.0f;	v3.m_z = 3.0f;
	printf("Matrix(3X1) != Vector3D equal: %s\n", (x31 != v3) ? FAIL : PASS);

	v3.m_x = 0.0f;	v3.m_y = 0.0f;	v3.m_w = 0.0f;
	printf("Matrix(mXn) != Vector3D where (m != 3 and n != 1): %s\n", (x33 != v3) ? PASS : FAIL);


	x31.m_matrix[0][0] = 1.0f;
	x31.m_matrix[1][0] = 2.0f;
	x31.m_matrix[2][0] = 3.0f;
	v3.m_x = 1.0f;	v3.m_y = 2.0f;	v3.m_z = 3.0f;

	x31Test.m_matrix[0][0] = 2.0f;
	x31Test.m_matrix[1][0] = 4.0f;
	x31Test.m_matrix[2][0] = 6.0f;
	printf("Matrix(3X1) + Vector3D: %s\n", ((x31 + v3) == x31Test) ? PASS : FAIL);

	try {
		x33 + v3;
		printf("Matrix(mXn) + Vector3D where n != 3: %s\n", FAIL);
	}
	catch (...) {
		printf("Matrix(mXn) + Vector3D where n != 3: %s\n", PASS);
	}


	x31.m_matrix[0][0] = 1.0f;
	x31.m_matrix[1][0] = 2.0f;
	x31.m_matrix[2][0] = 3.0f;
	v3.m_x = 1.0f;	v3.m_y = 2.0f;	v3.m_z = 3.0f;

	x31Test.m_matrix[0][0] = 0.0f;
	x31Test.m_matrix[1][0] = 0.0f;
	x31Test.m_matrix[2][0] = 0.0f;
	printf("Matrix(3X1) - Vector3D: %s\n", ((x31 - v3) == x31Test) ? PASS : FAIL);

	try {
		x33 - v3;
		printf("Matrix(mXn) - Vector3D where n != 3: %s\n", FAIL);
	}
	catch (...) {
		printf("Matrix(mXn) - Vector3D where n != 3: %s\n", PASS);
	}


	x33.m_matrix[0][0] = 1.0f;
	x33.m_matrix[0][1] = 2.0f;
	x33.m_matrix[0][2] = 3.0f;

	x33.m_matrix[1][0] = 4.0f;
	x33.m_matrix[1][1] = 5.0f;
	x33.m_matrix[1][2] = 6.0f;

	x33.m_matrix[2][0] = 7.0f;
	x33.m_matrix[2][1] = 8.0f;
	x33.m_matrix[2][2] = 9.0f;
	v3.m_x = 1.0f;	v3.m_y = 2.0f;	v3.m_z = 3.0f;

	x31Test.m_matrix[0][0] = 14.0f;
	x31Test.m_matrix[1][0] = 32.0f;
	x31Test.m_matrix[2][0] = 50.0f;
	printf("Matrix(3X3) * Vector3D: %s\n", ((x33 * v3) == x31Test) ? PASS : FAIL);

	try {
		x31 * v3;
		printf("Matrix(mXn) - Vector3D where n != 3: %s\n", FAIL);
	}
	catch (...) {
		printf("Matrix(mXn) - Vector3D where n != 3: %s\n", PASS);
	}

	#pragma endregion Vector3D
}

void Matrix2x2Tests()
{
	printf("\n========== Running Matrix2x2 tests ==========\n\n");

	#pragma region Methods
	Matrix2x2 m0 = Matrix2x2();
	Matrix2x2 m1 = Matrix2x2();
	long i, j;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = i * 2 + j;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m1.m_matrix[i][j] = i + j * 2;

	m1.Transpose();
	printf("Matrix2x2 Transpose: %s\n", (m0 == m1) ? PASS : FAIL);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = 0.0f;

	m1.Zero();
	printf("Matrix2x2 Zero: %s\n", (m0 == m1) ? PASS : FAIL);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = i == j ? 1.0f : 0.0f;

	m1.Identity();
	printf("Matrix2x2 Identity: %s\n", (m0 == m1) ? PASS : FAIL);
	#pragma endregion Methods
	#pragma region StaticMethods
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = 0.0f;

	Matrix2x2 zero = Matrix2x2::Zero2D();
	printf("Matrix2x2::Zero: %s\n", (zero == m0) ? PASS : FAIL);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = i == j ? 1.0f : 0.0f;

	Matrix2x2 identity = Matrix2x2::Identity2D();
	printf("Matrix2x2::Identity: %s\n", (m0 == identity) ? PASS : FAIL);
	#pragma endregion StaticMethods
	#pragma region Operations
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m1.m_matrix[i][j] = i - j;
	printf("Matrix2x2 == Matrix2x2 equal: %s\n", (m0 == m0) ? PASS : FAIL);

	printf("Matrix2x2 == Matrix2x2 not equal: %s\n", (m0 == m1) ? FAIL : PASS);

	printf("Matrix2x2 != Matrix2x2 not equal: %s\n", (m0 != m1) ? PASS : FAIL);

	printf("Matrix2x2 != Matrix2x2 equal: %s\n", (m0 != m0) ? FAIL : PASS);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m1.m_matrix[i][j] = -(i + j);
	printf("Matrix2x2 + Matrix2x2: %s\n", (zero == m0 + m1) ? PASS : FAIL);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = i + j;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m1.m_matrix[i][j] = i + j;
	printf("Matrix2x2 - Matrix2x2: %s\n", (zero == m0 - m1) ? PASS : FAIL);

	/*for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m1.m_matrix[i][j] = i + j;
	Matrix2x2 result = Matrix2x2(1.0f, 2.0f, 5.0f, 11.0f);
	printf("Matrix2x2 * Matrix2x2: %s\n", (m0 * m1 == result) ? PASS : FAIL);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m1.m_matrix[i][j] = (i + j) * 2.0f;
	printf("Matrix2x2 * scalar: %s\n", ((m0 * 2.0f) == m1) ? PASS : FAIL);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m0.m_matrix[i][j] = i + j;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			m1.m_matrix[i][j] = (i + j) / 2.0f;
	printf("Matrix2x2 / divisor: %s\n", ((m0 / 2.0f) == m1) ? PASS : FAIL);
	#pragma endregion Operations
	#pragma region Vector2D
	printf("\n========== Running Matrix2x2 - Vector2D tests ==========\n\n");
	Matrix2x2 x22 = Matrix2x2();
	Vector2D v2 = Vector2D(1, 2);

	x22.m_matrix[0][0] = 1.0f;
	x22.m_matrix[0][1] = 2.0f;
	x22.m_matrix[1][0] = 3.0f;
	x22.m_matrix[1][1] = 4.0f;
	v2.m_x = 2.0f;	v2.m_y = 3.0f;

	Vector2D v2Test = Vector2D(8.0f, 18.0f);
	printf("Matrix2x2 * Vector2D: %s\n", (v2Test == (x22 * v2)) ? PASS : FAIL);
*/
	#pragma endregion Vector2D
}

void Matrix3x3Tests()
{
	printf("\n========== Running Matrix3x3 tests ==========\n\n");
}

void StaticCollisionTests()
{
	printf("\n========== Running Static Collision tests ==========\n\n");

	Vector2D v1 = Vector2D(10.0f, 10.0f), 
			 v2 = Vector2D(11.4f, 11.4f);
	float radius = 2.0f;
	
	//StaticPointToStaticCircle
	printf("StaticPointToStaticCircle Collision: %s\n", (StaticPointToStaticCircle(v2, v1, radius)) ? PASS : FAIL);

	v2.m_x = 12.f; v2.m_y = 12.f;
	printf("StaticPointToStaticCircle Non Collision: %s\n\n", (!StaticPointToStaticCircle(v2, v1, radius)) ? PASS : FAIL);

	//StaticPointToStaticRect
	v1.m_x = 1.0f;	v1.m_y = 1.0f;	//point
	v2.m_x = 0.0f;	v2.m_y = 0.0f;	//rect
	printf("StaticPointToStaticRect Collision: %s\n", (StaticPointToStaticRect(v1, v2, 2.0f, 2.0f) ? PASS : FAIL));
	printf("StaticPointToStaticRect Non Collision: %s\n\n", (!StaticPointToStaticRect(v1, v2, 1.0f, 1.0f) ? PASS : FAIL));

	//StaticCircleToStaticCircle
	v1.m_x = 2.0f;	v1.m_y = 0.0f;
	printf("StaticCircleToStaticCircle Collision Touch: %s\n", (StaticCircleToStaticCircle(v1, 1.0f, v2, 1.0f) ? PASS : FAIL));
	printf("StaticCircleToStaticCircle Collision: %s\n", (StaticCircleToStaticCircle(v1, 2.0f, v2, 1.0f) ? PASS : FAIL));
	printf("StaticCircleToStaticCircle Non Collision: %s\n\n", (!StaticCircleToStaticCircle(v1, 0.5f, v2, 1.0f) ? PASS : FAIL));

	//StaticRectToStaticRect
	v1.m_x = 2.0f;	v1.m_y = 2.0f;
	v2.m_x = 0.0f;	v2.m_y = 0.0f;
	printf("StaticRectToStaticRect Non Collision: %s\n", (!StaticRectToStaticRect(v1, 1.0f, 1.0f, v2, 1.0f, 1.0f) ? PASS : FAIL));
	printf("StaticRectToStaticRect Collision Touch: %s\n", (StaticRectToStaticRect(v1, 2.0f, 2.0f, v2, 2.0f, 2.0f) ? PASS : FAIL));
	printf("StaticRectToStaticRect Collision Intersect: %s\n", (StaticRectToStaticRect(v1, 3.0f, 3.0f, v2, 3.0f, 3.0f) ? PASS : FAIL));
}

int main(int argc, char ** argv)
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			if (strlen(*argv)>1)
			{
				switch (argv[i][1])
				{
				case 'v':
					if (strlen(argv[i]) > 2)
					{
						if (argv[i][2] == '2')
							Vector2DTests();
						else if (argv[i][2] == '3')
							Vector3DTests();
					}
					else {
						Vector2DTests();
						Vector3DTests();
					}
					break;
				case 'm':
					if (strlen(argv[i]) > 2)
					{
						switch (argv[i][2]) {
							case 'a':
								MatrixTests();
								break;
							case '2':
								Matrix2x2Tests();
								break;
							case '3':
								Matrix3x3Tests();
								break;
							default:
								printf("Unrecognized flag: %s", argv[i]);
								return 1;
						}
					}
					else 
					{
						MatrixTests();
						Matrix2x2Tests();
						Matrix3x3Tests();
					}
					break;
				case 's':
					StaticCollisionTests();
					break;
				default:
					printf("Unrecognized flag: %s", argv[i]);
					return 1;
				}
			}
		}
	}
	else
	{
		Vector2DTests();
		Vector3DTests();
		MatrixTests();
		Matrix2x2Tests();
		Matrix3x3Tests();
		StaticCollisionTests();
	}

	return 0;
}