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
	/*! struct AcryProps */
	struct AcryProps {
		int windowHeight = 600;				/** Default height of the game window */
		int windowWidth = 800;				/** Default width of the game window */
		String windowTitle = "Acrylicor";	/** Default name of the game window */
		bool debugMode = false;				/** Indicates if the engine should run in debug mode or not */
		String debugShader = "lineShader";	/** Name of the shader to use when drawing debug lines to the screen. Note: Shader must be loaded by user */
	};

	//! int Initialize(String configFileName)
	/*!
	\param configFileName The config json file to use for setup, must include file path
	\return Error code: 0 - everything went well, non-zero - something went wrong
	*/
	int Initialize(String configFileName);

	//! int Initialize(AcryProps props)
	/*!
	\param props AcryProps configuration struct to initialize the game engine with
	\return Error code: 0 - everything went well, non-zero - something went wrong
	*/
	int Initialize(AcryProps props);

	//! double FrameStart()
	/*!
	Starts the game frame. Calls various start and update methods on managers.
	\return Delta Time - time elapsed over the duration of the last frame
	*/
	double FrameStart();

	//! void FrameEnd()
	/*!
	Ends the game frame. Calls various end and update methods on managers.
	*/
	void FrameEnd();

	//! void RenderObject(GameObject& gameObject)
	/*!
	Renders a given GameObject
	*/
	void RenderObject(GameObject& gameObject);

	//! Mesh * CreateMesh(String meshName)
	/*!
	Creates a Mesh object and maps it to the given name
	\param meshName - String name representing the Mesh to be created, used for resource management
	\return pointer to the mesh created
	*/
	Mesh * CreateMesh(String meshName);

	//! void LoadTexturesFromFile(String fileName)
	/*!
	Given a json file + file path, will parse the json and load texture images with the given data
	\param fileName - The json file containing what textures to load, must include file path
	*/
	void LoadTexturesFromFile(String fileName);

	//! void UnloadResources()
	/*!
	Calls to unload all currently loaded resources. Meshes, textures, game object archetypes, etc.
	*/
	void UnloadResources();

	//! void LoadGameObjects(String fileName)
	/*!
	Parses a given json file which in turn should list other json files each containing a game object archetype. 
	Each archetype is loaded into the engine for use in creation later.
	\param fileName - The json file containing what game object archetypess to load, must include file path
	*/
	void LoadGameObjects(String fileName);

	//! void LoadLevel(String fileName)
	/*!
	Parses a given json file for what game objects to load in this level. Level file can specify overrides for any 
	components already on the game object archetype but will not add new ones.
	\param fileName - The json file containing what game level to load, must include file path
	*/
	void LoadLevel(String fileName);

	void LoadLevelConfig(String fileName);

	void LoadCurrentLevel();

	//! void LoadShaderProgram(String fileName)
	/*!
	Parses a given json file for the name of the shader, the file path and names of the vertex and fragment shaders,
	and any attributes and uniforms associated with those shaders
	\param fileName - The json file containing shader information, must include file path
	*/
	void LoadShaderProgram(String fileName);

	//! void UpdateGameObjects(double deltaTime)
	/*!
	Calls various update methods on managers
	\param deltaTime - Duration of the previous frame
	*/
	void UpdateGameObjects(double deltaTime);

	//! void RenderGameObjects()
	/*!
	Renders all currently living game objects
	*/
	void RenderGameObjects();

	//! void CleanUpGameObjects()
	/*!
	Destroys all currently living game objects and resets the GameObject Manager
	*/
	void CleanUpGameObjects();
}

#endif