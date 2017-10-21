#include "ControllerComponent.h"
#include "InputManager.h"

ControllerComponent::ControllerComponent(GameObject& parent) :
	Component(parent, CT_CONTROLLER)
{
}

ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Update()
{
	InputManager& inputMgr = InputManager::GetInstance();
	if (inputMgr.IsKeyPressed(ACR_W)) {
		parent.Move(Vector2D(0.0f, 1.0f) * dt);
	}
	if (inputMgr.IsKeyPressed(ACR_S)) {
		player->GetTransformComponent()->Move(Vector2D(0.0f, -1.0f) * dt);
	}
	if (inputMgr.IsKeyPressed(ACR_A)) {
		player->GetTransformComponent()->Move(Vector2D(-1.0f, 0.0f) * dt);
	}
	if (inputMgr.IsKeyPressed(ACR_D)) {
		player->GetTransformComponent()->Move(Vector2D(1.0f, 0.0f) * dt);
	}
}
