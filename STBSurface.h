/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: STBSurface.h
Purpose: Structs for loading STB_Surfaces
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/30/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef STB_SURFACE_H
#define STB_SURFACE_H

#include <glew.h>

// Data captured by stbi_load
struct STB_Surface {
	unsigned char * data;
	int width;
	int height;
	int channels;
	bool hasAlpha;
	int tileX; // How many pixels wide is a single sprite on this sprite sheet
	int tileY; // How many pixels tall is a single sprite on this sprite sheet
};

struct SurfaceTextureBuffer {
	explicit SurfaceTextureBuffer(STB_Surface * _surface, GLuint _bufferId) :
		surface(_surface), bufferId(_bufferId) {};
	STB_Surface * surface;
	GLuint bufferId;
};

#endif