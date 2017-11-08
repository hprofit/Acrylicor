#include "ControllerComponent.h"
//#include "JsonReader.h"

// Don't like TODO: Fix
#include "GameObject.h"
#include "PhysicsComponent.h"
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
	PhysicsComponent* pComp = static_cast<PhysicsComponent*>(m_parent.Get(CT_PHYSICS));
	SpriteComponent* sComp = static_cast<SpriteComponent*>(m_parent.Get(CT_SPRITE));

	if (!pComp || !sComp)
		return;

	// TODO: Don't like
	sComp->SetFrame(2, 2);
	float force = 10.0f;
	if (inputMgr.IsKeyPressed(ACR_W)) {
		pComp->AddForce(Vector3D(0.f, force, 0.f));
		//sComp->SetFrame(2, 1);
	}
	if (inputMgr.IsKeyPressed(ACR_S)) {
		pComp->AddForce(Vector3D(0.f, -force, 0.f));
		//sComp->SetFrame(2, 3);
	}

	if (inputMgr.IsKeyPressed(ACR_A)) {
		pComp->AddForce(Vector3D(-force, 0.f, 0.f));
		//sComp->PrevFrame();
	}
	if (inputMgr.IsKeyPressed(ACR_D)) {
		pComp->AddForce(Vector3D(force, 0.f, 0.f));
		//sComp->NextFrame();
	}

	//if (inputMgr.IsKeyPressed(ACR_Q)) {
	//	tComp->RotateZ(100.0f * deltaTime);
	//}
	//if (inputMgr.IsKeyPressed(ACR_E)) {
	//	tComp->RotateZ(-100.0f * deltaTime);
	//}

	//if (inputMgr.IsKeyPressed(ACR_R)) {
	//	tComp->ScaleUniform(5.0f * deltaTime);
	//}
	//if (inputMgr.IsKeyPressed(ACR_F)) {
	//	tComp->ScaleUniform(-5.0f * deltaTime);
	//}
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
