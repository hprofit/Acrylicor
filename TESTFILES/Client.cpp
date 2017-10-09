/* Start Header -------------------------------------------------------
File Name: Client.cpp
Purpose: Provides the initialization and rendering functionality.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Author: Holden Profit
- End Header --------------------------------------------------------*/

#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "Torus.h"
#include "Plane.h"
#include "Sphere.h"

#include "Client.h"
using namespace std;

const int MESH_SIZE = 20;
const float THICKNESS = 0.5f;
const float PI = 4.0f*atan(1.0f);
const int TORUS_BUFFER_INDEX = 0;
const int SPHERE_BUFFER_INDEX = 1;
const int PLANE_BUFFER_INDEX = 2;
const float RATE = 360.0f / 5.0f;

Client::Client(int which) : 
	cameraPosition(0.0f, 0.0f, 0.0f, 1.0f), 
	cameraLookat(0.0f, 0.0f, -1.0f, 0.0f),
	camXRot(0.0f), camYRot(0.0f),
	fov(80.0f)
{
	// (I) create shader program
	GLint value;

	// (I.A) compile fragment shader
	const char *fragment_shader_text =
		"#version 130\n\
		in vec4 vcolor;\
		out vec4 frag_color;\
		void main(void) {\
		frag_color = vcolor;\
		}";
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragment_shader_text, 0);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		cerr << "fragment shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(fshader, 1024, 0, buffer);
		cerr << buffer << endl;
	}

	// (I.B) compile vertex shader
	const char *vertex_shader_text =
		"#version 130\n\
		attribute vec4 position;\
		attribute vec4 normal;\
		uniform mat4 persp_matrix;\
		uniform mat4 view_matrix;\
		uniform mat4 model_matrix;\
		uniform mat4 normal_matrix;\
		uniform vec4 color;\
		out vec4 vcolor;\
		void main() {\
			gl_Position = persp_matrix * view_matrix * model_matrix * position;\
			vec4 m = normal_matrix * normal;\
			float f = max(0,m.z)/length(m);\
			vcolor = vec4(f*color.xyz,color.w);\
		}";
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vertex_shader_text, 0);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		cerr << "vertex shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		cerr << buffer << endl;
	}

	// (I.C) link shaders
	program = glCreateProgram();
	glAttachShader(program, fshader);
	glAttachShader(program, vshader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &value);
	if (!value) {
		cerr << "vertex shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		cerr << buffer << endl;
	}

	// (II) get shader variable locations
	aposition = glGetAttribLocation(program, "position");
	anormal = glGetAttribLocation(program, "normal");
	upersp_matrix = glGetUniformLocation(program, "persp_matrix");
	uview_matrix = glGetUniformLocation(program, "view_matrix");
	umodel_matrix = glGetUniformLocation(program, "model_matrix");
	unormal_matrix = glGetUniformLocation(program, "normal_matrix");
	ucolor = glGetUniformLocation(program, "color");

	// Load the meshes into individual buffers
	initializeBuffersForMeshAtIndex(Torus(THICKNESS, MESH_SIZE), TORUS_BUFFER_INDEX);
	initializeBuffersForMeshAtIndex(Sphere(MESH_SIZE), SPHERE_BUFFER_INDEX);
	initializeBuffersForMeshAtIndex(Plane(MESH_SIZE), PLANE_BUFFER_INDEX);

	// (IV) enable use of z-buffer
	glEnable(GL_DEPTH_TEST);

	aspect = 1;
	time = 0;
}

Client::~Client(void) {
	// delete the shader program
	glUseProgram(0);
	GLuint shaders[2];
	GLsizei count;
	glGetAttachedShaders(program, 2, &count, shaders);
	for (int i = 0; i < count; ++i)
		glDeleteShader(shaders[i]);
	glDeleteProgram(program);

	// delete the vertex, normal, and face buffers
	for (int i = 0; i < numberOfUniqueMeshes; i++) {
		glDeleteBuffers(1, &vertex_buffer_arr[i]);
		glDeleteBuffers(1, &normal_buffer_arr[i]);
		glDeleteBuffers(1, &face_buffer_arr[i]);
	}
}

void Client::initializeBuffersForMeshAtIndex(Mesh3D& mesh, int index) {
	face_counts[index] = mesh.faceCount();

	// (III.A) vertex buffer
	glGenBuffers(1, &vertex_buffer_arr[index]);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_arr[index]);
	int vertex_buffer_size = sizeof(Vector3D)*mesh.vertexCount();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, mesh.vertexArray(), GL_STATIC_DRAW);

	// (III.B) normal buffer
	glGenBuffers(1, &normal_buffer_arr[index]);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_arr[index]);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, mesh.normalArray(), GL_STATIC_DRAW);

	// (III.C) face buffer
	glGenBuffers(1, &face_buffer_arr[index]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer_arr[index]);
	int face_buffer_size = sizeof(Mesh3D::Face)*face_counts[index];
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, mesh.faceArray(), GL_STATIC_DRAW);
}

Matrix4x4 Client::makeMatrixFromCameraVectors(const Vector3D& right, const Vector3D& up, const Vector3D& forward)
{
	Matrix4x4 rotationM;
	rotationM.Set(0, 0, right.getX());
	rotationM.Set(0, 1, right.getY());
	rotationM.Set(0, 2, right.getZ());
	rotationM.Set(0, 3, 0.0f);

	rotationM.Set(1, 0, up.getX());
	rotationM.Set(1, 1, up.getY());
	rotationM.Set(1, 2, up.getZ());
	rotationM.Set(1, 3, 0.0f);

	rotationM.Set(2, 0, -forward.getX());
	rotationM.Set(2, 1, -forward.getY());
	rotationM.Set(2, 2, -forward.getZ());
	rotationM.Set(2, 3, 0.0f);

	rotationM.Set(3, 0, 0.0f);
	rotationM.Set(3, 1, 0.0f);
	rotationM.Set(3, 2, 0.0f);
	rotationM.Set(3, 3, 1.0f);

	return rotationM;
}

Vector3D Client::getCameraRight()
{
	Vector3D globalUp(0, 1, 0, 0);
	Vector3D lCrossR = Vector3D::Cross(cameraLookat, globalUp);
	float lenLCrossR = lCrossR.Length();
	return lenLCrossR != 0.0f ? lCrossR * (1.0f / lenLCrossR): Vector3D(0, 0, 1, 0);
}

Vector3D Client::getCameraUp(const Vector3D& forward, const Vector3D& right)
{
	return Vector3D::Cross(forward * -1, right);
}

Matrix4x4 Client::calculateViewMatrix()
{
	Vector3D globalUp(0, 1, 0, 0);
	Vector3D lCrossR = Vector3D::Cross(cameraLookat, globalUp);
	float lenLCrossR = lCrossR.Length();
	Vector3D forward = Vector3D::Normalize(cameraLookat);
	Vector3D right = getCameraRight();
	Vector3D up = getCameraUp(forward, right);

	Matrix4x4 rotationM = makeMatrixFromCameraVectors(right, up, forward);

	return rotationM * Matrix4x4::Translate(-1 * cameraPosition);
}

void Client::draw(double dt) {
	// clear frame buffer and z-buffer
	glClearColor(0.9f, 0.9f, 0.9f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	const Vector3D Y_AXIS(0, 1, 0, 0);
	const Vector3D X_AXIS(1, 0, 0, 0);
	const Matrix4x4 VIEW_M = calculateViewMatrix();

	for (int i = 0; i < 20; i++) {
		Color color; 
		color.r = 1.0 * i / 20.0f;
		color.g = 1.0 - 1.0 * i / 20.0f;
		color.b = 1.0 * i / 20.0f;
		color.a = 1.0f;
		renderBuffer(TORUS_BUFFER_INDEX, color, 1.0f, Matrix4x4::Rotate(RATE*time, Y_AXIS), VIEW_M, Vector3D(-30 + i * 3, 5, -50, 0));
	}
	for (int i = 0; i < 40; i++) {
		Color color;
		color.r = 1.0 * i / 20.0f;
		color.g = 1.0 * i / 20.0f;
		color.b = 1.0 - 1.0 * i / 20.0f;
		color.a = 1.0f;
		renderBuffer(SPHERE_BUFFER_INDEX, color, 1.0f, Matrix4x4::Rotate(0, Y_AXIS), VIEW_M, Vector3D(-40 + i * 2, -5, -50, 0));
	}
	
	Color color;
	color.r = 1.0f;
	color.g = 0.5f;
	color.b = 0.5f;
	color.a = 1.0f;
	renderBuffer(PLANE_BUFFER_INDEX, color, 40.0f, Matrix4x4::Rotate(-45, X_AXIS), VIEW_M, Vector3D(0, 10, -70, 0));

	time += dt;
}

void Client::renderBuffer(int bufferIndex, Color color, float scalar, const Matrix4x4& rotationM, const Matrix4x4& viewM, Vector3D position) {
	// set shader uniform variable values
	glUseProgram(program);
	Matrix4x4 P = Matrix4x4::Perspective(fov, aspect, 0.1f);
	glUniformMatrix4fv(upersp_matrix, 1, true, (float*)&P);
	//Matrix4x4 V = scale(1);
	//glUniformMatrix4fv(uview_matrix, 1, true, (float*)&V);
	glUniformMatrix4fv(uview_matrix, 1, true, (float*)&viewM);
	const float RATE = 360.0f / 5.0f;
	const Vector3D AXIS(0, 1, 0, 0);
	Matrix4x4 M = Matrix4x4::Translate(position)
				* rotationM
				* Matrix4x4::Scale(scalar);
	Matrix4x4 N = Matrix4x4::Transpose3x3(Matrix4x4::Inverse3x3(M));
	glUniformMatrix4fv(umodel_matrix, 1, true, (float*)&M);
	glUniformMatrix4fv(unormal_matrix, 1, true, (float*)&N);

	// Generate color for each object
	glUniform4f(ucolor, color.r, color.g, color.b, color.a);

	// set shader attributes
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_arr[bufferIndex]); // <- select buffer
	glVertexAttribPointer(aposition, 4, GL_FLOAT, false, 0, 0); // <- load it to memory
	glEnableVertexAttribArray(aposition); // <- enable
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_arr[bufferIndex]);
	glVertexAttribPointer(anormal, 4, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(anormal);

	// draw the mesh
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer_arr[bufferIndex]);
	glDrawElements(GL_TRIANGLES, 3 * face_counts[bufferIndex], GL_UNSIGNED_INT, 0);
}

void Client::keypress(SDL_Keycode kc, float dt) {
	// respond to keyboard input
	//   kc: SDL keycode (e.g., SDLK_SPACE, SDLK_a, SDLK_s
	float moveSpeed = 1.0;
	Vector3D right = getCameraRight();
	switch (kc) {
		case SDLK_w:
		case SDLK_UP:
			cameraPosition = cameraPosition + (cameraLookat * moveSpeed);
			break;
		case SDLK_s:
		case SDLK_DOWN:
			cameraPosition = cameraPosition + (cameraLookat * -moveSpeed);
			break;
		case SDLK_a:
		case SDLK_LEFT:
			cameraPosition = cameraPosition + (right * -moveSpeed);
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			cameraPosition = cameraPosition + (right * moveSpeed);
			break;


		case SDLK_e:
			fov += 5.0f;
			break;
		case SDLK_q:
			fov -= 5.0f;
			break;

		case SDLK_r:
			cameraPosition = Vector3D(0.0f, 0.0f, 0.0f, 1.0f);
			cameraLookat = Vector3D(0.0f, 0.0f, -1.0f, 0.0f);
			camXRot = camYRot = 0.0f;
			break;
	}

	fov = min(fov, 120.0f);
	fov = max(fov, 80.0f);
}

void Client::resize(int W, int H) {
	aspect = float(W) / float(H);
	glViewport(0, 0, W, H);
}

void Client::mousedrag(int x, int y, bool left_button) {
	// respond to mouse click
	//   (x,y): click location (in window coordinates)
	Vector3D defaultLookat(0.0f, 0.0f, -1.0f, 0.0f);
	Vector3D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
	Vector3D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
	camXRot -= x;
	camYRot -= y;
	Matrix4x4 rot = Matrix4x4::Rotate(camXRot, yAxis) *  Matrix4x4::Rotate(camYRot, xAxis);
	cameraLookat = rot * defaultLookat;
}

