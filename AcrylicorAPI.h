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

#include "AcrylicorTypedefs.h"
#include "STBSurface.h"
#include "GameObject.h"

class Mesh;

namespace Acrylicor {
	struct AcryProps {
		int windowHeight = 600;
		int windowWidth = 800;
		String windowTitle = "Acrylicor";
		bool debugMode = false;
		String debugShader = "lineShader";
	};

	int Initialize(String configFileName);

	/*!
		Start up the Acrylicor engine
	*/
	int Initialize(AcryProps props);

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
	Creates and returns a Mesh pointer
	*/
	Mesh * CreateMesh(String meshName);

	/*!
	Parses a json file for key - image file pairs
	*/
	void LoadTexturesFromFile(String fileName);

	void UnloadResources();

	GameObject * LoadGameObject(String fileName);
	void LoadGameObjects(String fileName);
	void LoadLevel(String fileName);

	/*!
	Parses a json file for a key - program name pair as well as paths to the corresponding 
	shader files and relevant variables to link
	*/
	void LoadShaderProgram(String fileName);

	void SelectShaderProgram(String programName);

	void UpdateGameObjects(double deltaTime);
	void RenderGameObjects();
	void CleanUpGameObjects();
}

#endif