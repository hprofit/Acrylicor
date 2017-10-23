/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AcrylicorAPI.h
Purpose: Exposes general purpose methods for the Acrylicor engine.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/22/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef ACRYLICOR_API_H
#define ACRYLICOR_API_H

#include "GameObject.h"
#include "Camera.h"
#include "Mesh.h"

namespace Acrylicor {
	/*!
		Start up the Acrylicor engine
	*/
	int Initialize();

	/*!
	Called at the beginning of every game loop
	*/
	double FrameStart();
	/*!
	Called at the end of every game loop
	*/
	void FrameEnd();

	/*!
	Will render a single gameObject using a default camera view
	*/
	void RenderObject(GameObject& gameObject);

	/*!
	Will render a single gameObject with a given camera
	*/
	void RenderObject(Camera& camera, GameObject& gameObject);

	/*!
	Creates and returns a Mesh pointer
	*/
	Mesh * CreateMesh(const char * meshName);
}

#endif