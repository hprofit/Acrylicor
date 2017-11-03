#include "TestGameState.h"
#include "AcrylicorAPI.h"

TestGameState::TestGameState()
{
}

TestGameState::~TestGameState()
{
}

void TestGameState::GameStateLoad(void)
{
	Acrylicor::LoadShaderProgram("ObjectFiles/defaultShader.json");
	Acrylicor::LoadShaderProgram("ObjectFiles/tileShader.json");
	Acrylicor::LoadShaderProgram("ObjectFiles/scrollingTileShader.json");

	Acrylicor::SelectShaderProgram("default");

	Acrylicor::LoadTexturesFromFile("ObjectFiles/textures.json");

	Acrylicor::LoadGameObjects("ObjectFiles/objects.json");
}

void TestGameState::GameStateInit(void)
{
	Acrylicor::LoadLevel("LevelFiles/level1.json");
}

void TestGameState::GameStateUpdate(double deltaTime)
{
	Acrylicor::UpdateGameObjects(deltaTime);
}

void TestGameState::GameStateDraw(void)
{
	Acrylicor::RenderGameObjects();
}

void TestGameState::GameStateFree(void)
{
	
}

void TestGameState::GameStateUnload(void)
{
	Acrylicor::UnloadResources();
}
