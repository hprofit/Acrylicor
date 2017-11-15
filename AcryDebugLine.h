/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AcryDebugLine.h
Purpose: A line containing two vertecies for debug drawing.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/13/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef DEBUG_LINE_H
#define DEBUG_LINE_H

#include "Vector3D.h"
#include <glew.h>
#include <GL/gl.h>

enum COLOR: unsigned long {
	WHITE =		0xFFFFFFFF,
	BLACK =		0x000000FF,
	RED =		0xFF0000FF,
	GREEN =		0x00FF00FF,
	BLUE =		0x0000FFFF,
	YELLOW =	0xFFFF00FF,
	PURPLE =	0xFF00FFFF,
	CYAN =		0x00FFFFFF,
	ORANGE =	0xFF8800FF
};

class AcryDebugLine
{
private:
	Vector3D* m_vertices;
	unsigned long* m_vertColors;
	GLuint m_vertexBuffer;
	GLuint m_colorBuffer;

public:
	AcryDebugLine(float p1x, float p1y, float p1z, unsigned long c1, float p2x, float p2y, float p2z, unsigned long c2);
	~AcryDebugLine();

	int vertexCount() const;
	Vector3D* vertexArray();
	const GLuint& GetVertexBuffer() const;


	int colorCount() const;
	unsigned long* colorArray();
	const GLuint& GetColorBuffer() const;

	void SetColor0(unsigned long c0);
	void SetColor1(unsigned long c1);
	void SetColor(unsigned long color);
	void SetColors(unsigned long c0, unsigned long c1);
};

#endif
