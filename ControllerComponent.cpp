#include "ControllerComponent.h"
#include "GameObject.h"

// Don't like TODO: Fix
#include "TransformComponent.h"
#include "InputManager.h"
#include "ComponentTypes.h"
#include "Vector2D.h"

ControllerComponent::ControllerComponent(GameObject& parent) :
	Component(parent, CT_CONTROLLER)
{
}

ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Update(double deltaTime)
{
	InputManager& inputMgr = InputManager::GetInstance();
	TransformComponent* tComp = static_cast<TransformComponent*>(m_parent.Get(CT_TRANSFORM));

	// TODO: Don't like
	if (inputMgr.IsKeyPressed(ACR_W)) {
		tComp->Move(Vector2D(0.0f, 1.0f) * deltaTime);
	}
	if (inputMgr.IsKeyPressed(ACR_S)) {
		tComp->Move(Vector2D(0.0f, -1.0f) * deltaTime);
	}
	if (inputMgr.IsKeyPressed(ACR_A)) {
		tComp->Move(Vector2D(-1.0f, 0.0f) * deltaTime);
	}
	if (inputMgr.IsKeyPressed(ACR_D)) {
		tComp->Move(Vector2D(1.0f, 0.0f) * deltaTime);
	}

	if (inputMgr.IsKeyPressed(ACR_Q)) {
		tComp->Rotate(100.0f * deltaTime);
	}
	if (inputMgr.IsKeyPressed(ACR_E)) {
		tComp->Rotate(-100.0f * deltaTime);
	}

	if (inputMgr.IsKeyPressed(ACR_R)) {
		tComp->ScaleUniform(5.0f * deltaTime);
	}
	if (inputMgr.IsKeyPressed(ACR_F)) {
		tComp->ScaleUniform(-5.0f * deltaTime);
	}
}
