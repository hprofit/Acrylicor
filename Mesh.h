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
#include "Matrix3x3.h"

struct Face {
	unsigned index[3];
	unsigned operator[](int i) const { return index[i]; }
	unsigned& operator[](int i) { return index[i]; }
};

class Mesh
{
private:
	std::vector<Matrix3x3> vertices, normals;
	std::vector<Face> faces;

public:
	Mesh(int mesh_size);
	~Mesh();

	int vertextCount(void);
	Vector3D* vertexArray(void);
	Vector3D* normalArray(void);
	int faceCount(void);
	Face* faceArray(void);
};

#endif