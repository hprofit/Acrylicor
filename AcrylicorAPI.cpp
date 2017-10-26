#include "AcrylicorAPI.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "FrameRateController.h"
#include "RenderManager.h"
#include "ResourceManager.h"

static FrameRateController& frameRateCtrl = FrameRateController::GetInstance();
static WindowManager& windowMngr = WindowManager::GetInstance();
static RenderManager& renderMngr = RenderManager::GetInstance();
static InputManager& inputMngr = InputManager::GetInstance();
static ResourceManager& resourceMngr = ResourceManager::GetInstance();

int Acrylicor::Initialize(AcryProps props)
{
	WindowManager::GetInstance().SetWindowSize(props.windowWidth, props.windowHeight);
	WindowManager::GetInstance().SetWindowTitle(props.windowTitle);

	RenderManager& renderManager = RenderManager::GetInstance();
	if (!renderManager.Init())
		return 1;

	Mesh * quad = CreateMesh("quad");
	quad->AddVertex(
		-0.5f, -0.5f, 0.0f, .0f, .0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, .0f, 1.0f
	);
	quad->AddVertex(
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, .0f, 1.0f
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

void Acrylicor::RenderObject(Camera & camera, GameObject & gameObject)
{
	renderMngr.RenderGameObject(camera, gameObject);
}

Mesh * Acrylicor::CreateMesh(String meshName)
{
	return resourceMngr.LoadMesh(meshName);
}

GLuint Acrylicor::LoadTexture(String fileName, String textureName)
{
	return resourceMngr.LoadTexture(fileName, textureName);
}

void Acrylicor::LoadTexturesFromFile(String fileName)
{
	resourceMngr.LoadTexturesFromFile(fileName);
}

void Acrylicor::UnloadResources()
{
	resourceMngr.UnloadAll();
}

void Acrylicor::LoadShaderProgram(String fileName)
{
	renderMngr.LoadShaderProgram(fileName);
}

void Acrylicor::SelectShaderProgram(String programName)
{
	renderMngr.SelectShaderProgram(programName);
}
