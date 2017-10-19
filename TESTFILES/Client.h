/* Start Header -------------------------------------------------------
File Name: Client.h
Purpose: Provides the API for the Client class.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Author: Holden Profit
- End Header --------------------------------------------------------*/

#pragma once

#ifndef CS541_CLIENT_H
#define CS541_CLIENT_H

#include "GL/glew.h"
#include "Mesh3D.h"
#include "../Vector3D.h"
#include "../Matrix4x4.h"

struct Color {
	float r, g, b, a;
	explicit Color(float R = 0.0f, float G = 0.0f, float B = 0.0f, float A = 0.0f)
		: r(R), g(G), b(B), a(A) {}
};

class Client {
public:
	Client();
	~Client(void);
	void draw(double dt);
	void keypress(double dt);
	void resize(int W, int H);
	void mousedrag(int x, int y, bool lbutton);
private:
	Vector3D cameraPosition;
	Vector3D cameraLookat;
	float camXRot, camYRot;
	float fov;
	Vector3D lightPosition;
	Color lightColor;
	Color ambientColor;

	const static int numberOfUniqueMeshes = 3;
	GLuint vertex_buffer_arr[numberOfUniqueMeshes],
		normal_buffer_arr[numberOfUniqueMeshes],
		face_buffer_arr[numberOfUniqueMeshes];
	int face_counts[numberOfUniqueMeshes];
	GLint program,
		aposition,
		anormal,
		upersp_matrix,
		uview_matrix,
		umodel_matrix,
		unormal_matrix,
		ulight_position,
		ulight_color,
		udiffuse_color,
		uambient_color,
		uspecular_color;
	int face_count;
	double time;
	float aspect;

	void initializeBuffersForMeshAtIndex(Mesh3D& mesh, int index);
	Matrix4x4 makeMatrixFromCameraVectors(const Vector3D& right, const Vector3D& up, const Vector3D& forward);
	Vector3D getCameraRight(void);
	Vector3D getCameraUp(const Vector3D& forward, const Vector3D& right);
	Matrix4x4 calculateViewMatrix(void);
	void renderBuffer(int bufferIndex, const Color& diffuseColor, float scalar, const Matrix4x4& rotationM, const Matrix4x4& viewM, const Vector3D& position);
};


#endif

