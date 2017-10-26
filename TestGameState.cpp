// Necessary
#include <iostream>
#include "TestGameState.h"
#include "AcrylicorAPI.h"

// Don't like
#include "Mesh.h"

#include "RenderManager.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "SDL.h"

#include "GameObjectFactory.h"

static GameObject * sgpPlayer;

TestGameState::TestGameState()
{
}

TestGameState::~TestGameState()
{
}

void TestGameState::GameStateLoad(void)
{
	Acrylicor::LoadShaderProgram("ObjectFiles/defaultShader.json");
	Acrylicor::SelectShaderProgram("default");
	Acrylicor::LoadTexturesFromFile("ObjectFiles/textures.json");
}

void TestGameState::GameStateInit(void)
{
	sgpPlayer = GameObjectFactory::GetInstance().LoadGameObjectFromFile("ObjectFiles/player.json");
	//Camera * camera = new Camera(Vector3D(0.0f, 0.0f, -10.0f), Vector3D(0, 0, -1));
}

void TestGameState::GameStateUpdate(double deltaTime)
{
	sgpPlayer->Update(deltaTime);
	//camera->Update();
}

void TestGameState::GameStateDraw(void)
{
	Acrylicor::RenderObject(*sgpPlayer);
}

void TestGameState::GameStateFree(void)
{
	delete sgpPlayer;
}

void TestGameState::GameStateUnload(void)
{
	Acrylicor::UnloadResources();
}
