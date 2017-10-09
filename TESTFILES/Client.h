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
};

class Client {
public:
	Client(int which=0);
	~Client(void);
	void draw(double dt);
	void keypress(SDL_Keycode kc, float dt);
	void resize(int W, int H);
	void mousedrag(int x, int y, bool lbutton);
private:
	Vector3D cameraPosition;
	Vector3D cameraLookat;
	float camXRot, camYRot;
	float fov;

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
		ucolor;
	int face_count;
	float time;
	float aspect;

	void initializeBuffersForMeshAtIndex(Mesh3D& mesh, int index);
	Matrix4x4 makeMatrixFromCameraVectors(const Vector3D& right, const Vector3D& up, const Vector3D& forward);
	Vector3D getCameraRight(void);
	Vector3D getCameraUp(const Vector3D& forward, const Vector3D& right);
	Matrix4x4 calculateViewMatrix(void);
	void renderBuffer(int bufferIndex, Color color, float scalar, const Matrix4x4& rotationM, const Matrix4x4& viewM, Vector3D position);
};


#endif

