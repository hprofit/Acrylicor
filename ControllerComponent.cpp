#include "ControllerComponent.h"
//#include "JsonReader.h"

#include "KeyPressEvent.h"

// Don't like TODO: Fix
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "WeaponComponent.h"
#include "InputManager.h"
#include "ComponentTypes.h"
#include "Vector2D.h"

ControllerComponent::ControllerComponent(GameObject& parent) :
	Component(parent, COMPONENT_TYPE::CONTROLLER)
{
}

ControllerComponent::ControllerComponent(const ControllerComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::CONTROLLER)
{
}

ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Update(double deltaTime)
{
	InputManager& inputMgr = InputManager::GetInstance();
	PhysicsComponent* pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	SpriteComponent* sComp = static_cast<SpriteComponent*>(m_parent.Get(COMPONENT_TYPE::SPRITE));
	WeaponComponent* wComp = static_cast<WeaponComponent*>(m_parent.GetChildOfType("gun")->Get(COMPONENT_TYPE::WEAPON));

	if (!pComp || !sComp || !wComp)
		return;

	// TODO: Don't like
	sComp->SetFrame(2, 2);
	float force = 10000.0f;
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

	if (inputMgr.IsKeyPressed(ACR_SPACE))
		wComp->Fire();

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

void ControllerComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
		case EventType::KEY_PRESS:
		{
			KeyPressEvent * kpEvent = static_cast<KeyPressEvent*>(aEvent);
		}
			break;
	}
}
