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
	sgpPlayer = Acrylicor::SpawnGameObject("player");
	sgpEnemy1 = Acrylicor::SpawnGameObject("enemy");
	Acrylicor::LoadLevel("LevelFiles/level1.json");
	

	//Camera * camera = new Camera(Vector3D(0.0f, 0.0f, -10.0f), Vector3D(0, 0, -1));
}

void TestGameState::GameStateUpdate(double deltaTime)
{
	sgpPlayer->Update(deltaTime);
	sgpEnemy1->Update(deltaTime);
	//camera->Update();
}

void TestGameState::GameStateDraw(void)
{
	Acrylicor::RenderObject(*sgpPlayer);
	Acrylicor::RenderObject(*sgpEnemy1);
}

void TestGameState::GameStateFree(void)
{
	//delete sgpPlayer;
}

void TestGameState::GameStateUnload(void)
{
	Acrylicor::UnloadResources();
}
