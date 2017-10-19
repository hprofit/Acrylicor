/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mesh.h
Purpose: Provides a collection of buffers that make up a Mesh
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 9/29/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vector3D.h"
#include <GL/glew.h>
#include <GL/gl.h>

struct Face {
	unsigned int index[3];
	explicit Face(unsigned int v1, unsigned int v2, unsigned int v3) { 
		index[0] = v1; index[1] = v2; index[2] = v3; 
	}
	unsigned int operator[](int i) const { return index[i]; }
	unsigned int& operator[](int i) { return index[i]; }
};

class Mesh
{
private:
	std::vector<Vector3D> m_vertices, m_normals;
	std::vector<Face> m_faces;
	GLuint m_vertexBuffer;

public:
	Mesh();
	~Mesh();

	void AddTriangle(Vector3D p1, Vector3D p2, Vector3D p3);
	void AddTriangle(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z);
	void FinishMesh();

	int vertextCount() const;
	Vector3D* vertexArray();
	Vector3D* normalArray();
	int faceCount() const;
	Face* faceArray();
	const GLuint& GetVertexBuffer() const { return m_vertexBuffer; }
};

#endif