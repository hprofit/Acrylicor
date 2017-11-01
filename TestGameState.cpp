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
	//sgpPlayer = Acrylicor::SpawnGameObject("player");
	//sgpEnemy1 = Acrylicor::SpawnGameObject("enemy");
	Acrylicor::LoadLevel("LevelFiles/level1.json");
	

	sgpCamera = new Camera(Vector3D(0.0f, 0.0f, -10.0f), Vector3D(0, 0, -1), CAM_PERSP);
}

void TestGameState::GameStateUpdate(double deltaTime)
{
	//sgpPlayer->Update(deltaTime);
	//sgpEnemy1->Update(deltaTime);
	sgpCamera->Update();
}

void TestGameState::GameStateDraw(void)
{
	//Acrylicor::RenderObject(*sgpCamera, *sgpPlayer);
	//Acrylicor::RenderObject(*sgpCamera, *sgpEnemy1);
}

void TestGameState::GameStateFree(void)
{
	//delete sgpPlayer;
	//delete sgpEnemy1;
}

void TestGameState::GameStateUnload(void)
{
	Acrylicor::UnloadResources();
}
