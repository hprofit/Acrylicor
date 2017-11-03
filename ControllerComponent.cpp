#include "ControllerComponent.h"
//#include "JsonReader.h"

// Don't like TODO: Fix
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "InputManager.h"
#include "ComponentTypes.h"
#include "Vector2D.h"

ControllerComponent::ControllerComponent(GameObject& parent) :
	Component(parent, CT_CONTROLLER)
{
}

ControllerComponent::ControllerComponent(const ControllerComponent & rhs, GameObject & parent) :
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
	SpriteComponent* sComp = static_cast<SpriteComponent*>(m_parent.Get(CT_SPRITE));

	// TODO: Don't like
	sComp->SetFrame(2, 2);
	if (inputMgr.IsKeyPressed(ACR_W)) {
		tComp->Move(Vector2D(0.0f, 10.0f) * deltaTime);
		sComp->SetFrame(2, 1);
	}
	if (inputMgr.IsKeyPressed(ACR_S)) {
		tComp->Move(Vector2D(0.0f, -10.0f) * deltaTime);
		sComp->SetFrame(2, 3);
	}

	if (inputMgr.IsKeyPressed(ACR_A)) {
		tComp->Move(Vector2D(-10.0f, 0.0f) * deltaTime);
		sComp->PrevFrame();
	}
	if (inputMgr.IsKeyPressed(ACR_D)) {
		tComp->Move(Vector2D(10.0f, 0.0f) * deltaTime);
		sComp->NextFrame();
	}

	if (inputMgr.IsKeyPressed(ACR_Q)) {
		tComp->RotateZ(100.0f * deltaTime);
	}
	if (inputMgr.IsKeyPressed(ACR_E)) {
		tComp->RotateZ(-100.0f * deltaTime);
	}

	if (inputMgr.IsKeyPressed(ACR_R)) {
		tComp->ScaleUniform(5.0f * deltaTime);
	}
	if (inputMgr.IsKeyPressed(ACR_F)) {
		tComp->ScaleUniform(-5.0f * deltaTime);
	}
}

ControllerComponent * ControllerComponent::Clone(GameObject & parent)
{
	return new ControllerComponent(*this, parent);
}

Component * ControllerComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new ControllerComponent(gObject);
}

void ControllerComponent::Override(nlohmann::json j)
{
}
