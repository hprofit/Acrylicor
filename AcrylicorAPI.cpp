#include "AcrylicorAPI.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "FrameRateController.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "json.hpp"
#include <iostream>
#include "JsonReader.h"

static FrameRateController& frameRateCtrl = FrameRateController::GetInstance();
static WindowManager& windowMngr = WindowManager::GetInstance();
static RenderManager& renderMngr = RenderManager::GetInstance();
static InputManager& inputMngr = InputManager::GetInstance();
static ResourceManager& resourceMngr = ResourceManager::GetInstance();
static GameObjectFactory& gameObjectFactory = GameObjectFactory::GetInstance();
static GameObjectManager& gameObjectMngr = GameObjectManager::GetInstance();

int Acrylicor::Initialize(AcryProps props)
{
	WindowManager::GetInstance().SetWindowSize(props.windowWidth, props.windowHeight);
	WindowManager::GetInstance().SetWindowTitle(props.windowTitle);

	RenderManager& renderManager = RenderManager::GetInstance();
	if (!renderManager.Init())
		return 1;

	Mesh * quad = CreateMesh("quad");

	quad->AddVertex(
		-0.5f, -0.5f, 0.0f, .0f, 1.f, 0xFFFFFFFF,
		0.5f, -0.5f, 0.0f, 1.f, 1.f, 0xFFFFFFFF,
		-0.5f, 0.5f, 0.0f, .0f, .0f, 0xFFFFFFFF
	);
	quad->AddVertex(
		0.5f, -0.5f, 0.0f, 1.f, 1.f, 0xFFFFFFFF,
		0.5f, 0.5f, 0.0f, 1.f, .0f, 0xFFFFFFFF,
		-0.5f, 0.5f, 0.0f, .0f, .0f, 0xFFFFFFFF
	);

	quad->FinishMesh();

	return 0;
}

double Acrylicor::FrameStart()
{
	frameRateCtrl.FrameStart();
	double dt = frameRateCtrl.GetFrameTime();

	windowMngr.FrameStart();
	renderMngr.FrameStart();

	inputMngr.Update();
	return dt;
}

void Acrylicor::FrameEnd()
{
	renderMngr.FrameEnd();
	windowMngr.FrameEnd();
	frameRateCtrl.FrameEnd();
}

void Acrylicor::RenderObject(GameObject & gameObject)
{
	renderMngr.RenderGameObject(gameObject);
}

Mesh * Acrylicor::CreateMesh(String meshName)
{
	return resourceMngr.LoadMesh(meshName);
}

SurfaceTextureBuffer * Acrylicor::LoadTexture(String fileName, String textureName)
{
	return nullptr;
	//return resourceMngr.LoadTexture(textureName, fileName, true);
}

void Acrylicor::LoadTexturesFromFile(String fileName)
{
	resourceMngr.LoadTexturesFromFile(fileName);
}

void Acrylicor::UnloadResources()
{
	resourceMngr.UnloadAll();
}

GameObject * Acrylicor::LoadGameObject(String fileName)
{
	return gameObjectFactory.LoadGameObjectFromFile(fileName);
}

void Acrylicor::LoadGameObjects(String fileName)
{
	gameObjectFactory.LoadGameObjectsFromFile(fileName);
}

void Acrylicor::LoadLevel(String fileName)
{
	try {
		json j = AcryJson::OpenJsonFile(fileName);

		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				if (it.key() == "objects") {
					int numObjs = j[it.key()].size();
					for (int i = 0; i < numObjs; ++i) {
						gameObjectMngr.SpawnGameObjectFromFile(j[it.key()][i]);
					}
				}
			}
		}
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}

void Acrylicor::LoadShaderProgram(String fileName)
{
	renderMngr.LoadShaderProgram(fileName);
}

void Acrylicor::SelectShaderProgram(String programName)
{
	renderMngr.SelectShaderProgram(programName);
}

void Acrylicor::UpdateGameObjects(double deltaTime)
{
	gameObjectMngr.UpdateGameObjects(deltaTime);
}

void Acrylicor::RenderGameObjects()
{
	gameObjectMngr.RenderGameObjects();
}
