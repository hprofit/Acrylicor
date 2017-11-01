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
static GameObject * sgpEnemy1;
static GameObject * sgpEnemy2;

static Camera * sgpCamera;

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
	Acrylicor::LoadGameObjects("ObjectFiles/objects.json");
}

void TestGameState::GameStateInit(void)
{
	Acrylicor::LoadLevel("LevelFiles/level1.json");
	

	sgpCamera = new Camera(Vector3D(0.0f, 0.0f, 10.f), Vector3D(0, 0, -1), 0, 0, 105.f, CAM_PERSP);
}

void TestGameState::GameStateUpdate(double deltaTime)
{
	sgpCamera->Update();
	Acrylicor::UpdateGameObjects(deltaTime);
}

void TestGameState::GameStateDraw(void)
{
	Acrylicor::RenderGameObjects(*sgpCamera);
}

void TestGameState::GameStateFree(void)
{
	
}

void TestGameState::GameStateUnload(void)
{
	Acrylicor::UnloadResources();
}
