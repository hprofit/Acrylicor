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
	quad->AddTriangle(
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	);
	quad->AddTriangle(
		-0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
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

Mesh * Acrylicor::CreateMesh(const char * meshName)
{
	return resourceMngr.LoadMesh(meshName);
}
