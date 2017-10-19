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
#include "../InputManager.h"
#include "../Shader.h"

#include "Client.h"
using namespace std;

const int MESH_SIZE = 20;
const float THICKNESS = 0.5f;
const float PI = 4.0f*atan(1.0f);
const int TORUS_BUFFER_INDEX = 0;
const int SPHERE_BUFFER_INDEX = 1;
const int PLANE_BUFFER_INDEX = 2;
const float RATE = 360.0f / 5.0f;

Client::Client() : 
	cameraPosition(0.0f, 0.0f, 0.0f, 1.0f), 
	cameraLookat(0.0f, 0.0f, -1.0f, 0.0f),
	camXRot(0.0f), camYRot(0.0f),
	fov(80.0f),
	lightPosition(0, 10, 0, 0),
	lightColor(1, 1, 1, 1),
	ambientColor(0.1f, 0.1f, 0.1f, 1.0f)
{
	// (I) create shader program
	GLint value;

#pragma region Vertex Shader Definition
	const char *vertex_shader_text =
		"#version 130\n\
		attribute vec4 position;\
		attribute vec4 normal;\
		\
		uniform mat4 persp_matrix;\
		uniform mat4 view_matrix;\
		uniform mat4 model_matrix;\
		uniform mat4 normal_matrix;\
		uniform vec4 light_position;\
		\
		out vec4 normal_vector;\
		out vec4 light_vector;\
		\
		void main() {\
			vec4 P = model_matrix * position;\
			gl_Position = persp_matrix * view_matrix * P;\
			normal_vector = normal_matrix * normal;\
			light_vector = light_position - P;\
		}";
#pragma endregion
	Shader vshader = Shader(vertex_shader_text, value, VERTEX_SHADER);

#pragma region Fragment Shader Definition
	const char *fragment_shader_text =
		"#version 130\n\
		uniform vec3 light_color;\
		uniform vec3 diffuse_color;\
		uniform vec3 ambient_color;\
		uniform vec3 specular_color;\
		\
		in vec4 normal_vector;\
		in vec4 light_vector;\
		\
		out vec4 frag_color;\
		\
		void main(void) {\
			vec4 m = normalize(normal_vector);\
			vec4 L = normalize(light_vector);\
			vec4 v = normalize(m - (m - L));\
			vec4 H = normalize((v + L));\
			vec3 diffuse = max(dot(m,L),0) * diffuse_color * light_color;\
			vec3 specular = pow(dot(m,H), 60) * specular_color * light_color;\
			vec3 ambient = diffuse_color * ambient_color;\
			frag_color = vec4(diffuse + specular + ambient,1);\
		}";
#pragma endregion
	Shader fshader = Shader(fragment_shader_text, value, FRAGMENT_SHADER);

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

#pragma region Link Variables from Shaders
	aposition = glGetAttribLocation(program, "position");
	anormal = glGetAttribLocation(program, "normal");
	upersp_matrix = glGetUniformLocation(program, "persp_matrix");
	uview_matrix = glGetUniformLocation(program, "view_matrix");
	umodel_matrix = glGetUniformLocation(program, "model_matrix");
	unormal_matrix = glGetUniformLocation(program, "normal_matrix");

	ulight_color = glGetUniformLocation(program, "light_color");
	udiffuse_color = glGetUniformLocation(program, "diffuse_color");
	uambient_color = glGetUniformLocation(program, "ambient_color");
	uspecular_color = glGetUniformLocation(program, "specular_color");
	ulight_position = glGetUniformLocation(program, "light_position");
#pragma endregion

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
	return Matrix4x4(
		right.getX(),		right.getY(),		right.getZ(),		0.0f,
		up.getX(),			up.getY(),			up.getZ(),			0.0f,
		-forward.getX(),	-forward.getY(),	-forward.getZ(),	0.0f,
		0.0f,				0.0f,				0.0f,				1.0f
	);
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
	Vector3D forward = Vector3D::Normalize(cameraLookat);
	Vector3D right = getCameraRight();
	Vector3D up = getCameraUp(forward, right);

	Matrix4x4 rotationM = makeMatrixFromCameraVectors(right, up, forward);

	return rotationM * Matrix4x4::Translate(-1 * cameraPosition);
}

void Client::draw(double dt) {
	const Vector3D Y_AXIS(0, 1, 0, 0);
	const Vector3D X_AXIS(1, 0, 0, 0);
	const Matrix4x4 VIEW_M = calculateViewMatrix();
	Color color;

	for (int i = 0; i < 1; i++) {
		color.r = 1.0f;
		color.g = 0.0f;
		color.b = 0.0f;
		color.a = 1.0f;
		renderBuffer(TORUS_BUFFER_INDEX, color, 1.0f, Matrix4x4::Rotate(0, Y_AXIS), VIEW_M, Vector3D(0, 5.0, -50, 0));
	}
	for (int i = 0; i < 1; i++) {
		color.r = 0.0f;
		color.g = 1.0f;
		color.b = 0.0f;
		color.a = 1.0f;
		renderBuffer(SPHERE_BUFFER_INDEX, color, 1.0f, Matrix4x4::Rotate(0, Y_AXIS), VIEW_M, Vector3D(0, -5, -50, 0));
	}
	
	color.r = 1.0f;
	color.g = 0.5f;
	color.b = 0.5f;
	color.a = 1.0f;
	renderBuffer(PLANE_BUFFER_INDEX, color, 40.0f, Matrix4x4::Rotate(-45, X_AXIS), VIEW_M, Vector3D(0, 10, -70, 0));

	time += dt;
}

void Client::renderBuffer(int bufferIndex, const Color& diffuseColor, float scalar, const Matrix4x4& rotationM, const Matrix4x4& viewM, const Vector3D& position) {
	// set shader uniform variable values
	glUseProgram(program);

	glUniform3f(ulight_color, lightColor.r, lightColor.g, lightColor.b);
	glUniform3f(uspecular_color, lightColor.r, lightColor.g, lightColor.b);
	glUniform3f(uambient_color, ambientColor.r, ambientColor.g, ambientColor.b);

	Matrix4x4 P = Matrix4x4::Perspective(fov, aspect, 0.1f);
	glUniformMatrix4fv(upersp_matrix, 1, true, (float*)&P);
	glUniformMatrix4fv(uview_matrix, 1, true, (float*)&viewM);
	Matrix4x4 M = Matrix4x4::Translate(position)
				* rotationM
				* Matrix4x4::Scale(scalar);
	Matrix4x4 N = Matrix4x4::Transpose3x3(Matrix4x4::Inverse3x3(M));
	glUniformMatrix4fv(umodel_matrix, 1, true, (float*)&M);
	glUniformMatrix4fv(unormal_matrix, 1, true, (float*)&N);

	// Generate color for each object
	glUniform3f(udiffuse_color, diffuseColor.r, diffuseColor.g, diffuseColor.b);

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

void Client::keypress(double dt) {
	float moveSpeed = 10.0;
	Vector3D right = getCameraRight();
	InputManager& iManager = InputManager::GetInstance();
	if (iManager.IsKeyPressed(ACR_W) || iManager.IsKeyPressed(ACR_UP)) {
		cameraPosition = cameraPosition + (cameraLookat * moveSpeed * dt);
	}

	if (iManager.IsKeyPressed(ACR_S) || iManager.IsKeyPressed(ACR_DOWN)) {
		cameraPosition = cameraPosition + (cameraLookat * -moveSpeed * dt);
	}
	
	if (iManager.IsKeyPressed(ACR_A) || iManager.IsKeyPressed(ACR_LEFT)) {
		cameraPosition = cameraPosition + (right * -moveSpeed * dt);
	}

	if (iManager.IsKeyPressed(ACR_D) || iManager.IsKeyPressed(ACR_RIGHT)) {
		cameraPosition = cameraPosition + (right * moveSpeed * dt);
	}

	if (iManager.IsKeyPressed(ACR_E))
		fov += 5.0f;
	else if (iManager.IsKeyPressed(ACR_E))
		fov -= 5.0f;

	if (iManager.IsKeyPressed(ACR_R)) {
		cameraPosition = Vector3D(0.0f, 0.0f, 0.0f, 1.0f);
		cameraLookat = Vector3D(0.0f, 0.0f, -1.0f, 0.0f);
		camXRot = camYRot = 0.0f;
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

