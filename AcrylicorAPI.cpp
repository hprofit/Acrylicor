#include "AcrylicorAPI.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "FrameRateController.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "PhysicsManager.h"
#include "json.hpp"
#include <iostream>
#include "JsonReader.h"
#include "Mesh.h"

static FrameRateController& frameRateCtrl = FrameRateController::GetInstance();
static WindowManager& windowMngr = WindowManager::GetInstance();
static RenderManager& renderMngr = RenderManager::GetInstance();
static InputManager& inputMngr = InputManager::GetInstance();
static ResourceManager& resourceMngr = ResourceManager::GetInstance();
static GameObjectFactory& gameObjectFactory = GameObjectFactory::GetInstance();
static GameObjectManager& gameObjectMngr = GameObjectManager::GetInstance();
static PhysicsManager& physicsMngr = PhysicsManager::GetInstance();

int Acrylicor::Initialize(String configFileName)
{
	Acrylicor::AcryProps props;

	try {
		json j = AcryJson::OpenJsonFile(configFileName);

		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				if (AcryJson::KeyIs(it, "WINDOW_WIDTH"))
					props.windowWidth = AcryJson::ParseInt(j, "WINDOW_WIDTH");
				else if (AcryJson::KeyIs(it, "WINDOW_HEIGHT"))
					props.windowHeight = AcryJson::ParseInt(j, "WINDOW_HEIGHT");
				else if (AcryJson::KeyIs(it, "WINDOW_TITLE"))
					props.windowTitle = AcryJson::ParseString(j, "WINDOW_TITLE");
				else if (AcryJson::KeyIs(it, "DEBUG_MODE"))
					props.debugMode = AcryJson::ParseBool(j, "DEBUG_MODE");
				else if (AcryJson::KeyIs(it, "DEBUG_SHADER"))
					props.debugShader = AcryJson::ParseString(j, "DEBUG_SHADER");
			}
		}
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}

	return Initialize(props);
}

int Acrylicor::Initialize(AcryProps props)
{
	WindowManager::GetInstance().SetWindowSize(props.windowWidth, props.windowHeight);
	WindowManager::GetInstance().SetWindowTitle(props.windowTitle);

	RenderManager& renderManager = RenderManager::GetInstance();
	if (!renderManager.Init())
		return 1;

	if (props.debugMode) {
		renderManager.SetDebugShaderName(props.debugShader);
		renderManager.SetDebugMode(props.debugMode);
	}

	Mesh * quad = CreateMesh("quad");

	quad->AddTriangle(
		-0.5f, -0.5f, 0.0f, .0f, 1.f, 0xFFFFFFFF,
		0.5f, -0.5f, 0.0f, 1.f, 1.f, 0xFFFFFFFF,
		-0.5f, 0.5f, 0.0f, .0f, .0f, 0xFFFFFFFF
	);
	quad->AddTriangle(
		0.5f, -0.5f, 0.0f, 1.f, 1.f, 0xFFFFFFFF,
		0.5f, 0.5f, 0.0f, 1.f, .0f, 0xFFFFFFFF,
		-0.5f, 0.5f, 0.0f, .0f, .0f, 0xFFFFFFFF
	);

	quad->FinishMesh();

	if (props.debugMode)
		resourceMngr.CreateDebugLine();

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
	physicsMngr.UpdatePhysics(deltaTime);
	gameObjectMngr.UpdateCameraObjects(deltaTime);
}

void Acrylicor::RenderGameObjects()
{
	gameObjectMngr.RenderGameObjects();
}

void Acrylicor::CleanUpGameObjects()
{
	gameObjectMngr.CleanUpGameObjects();
}