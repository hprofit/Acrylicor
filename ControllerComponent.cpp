#include "ControllerComponent.h"
//#include "JsonReader.h"

#include "KeyPressEvent.h"

// Don't like TODO: Fix
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "WeaponComponent.h"
#include "MissileLauncherComponent.h"
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
	MissileLauncherComponent* mlComp = static_cast<MissileLauncherComponent*>(m_parent.GetChildOfType("missileLauncher")->Get(COMPONENT_TYPE::MISSILE_LAUNCHER));

	if (!pComp || !sComp || !wComp)
		return;

	// TODO: HOOK THESE UP TO EVENTS
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
	if (inputMgr.IsKeyTriggered(ACR_F))
		mlComp->Fire();
	if (inputMgr.IsKeyTriggered(ACR_LSHIFT))
		m_parent.HandleEvent(new AcryEvent(EventType::DASH));

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
	ControllerComponent* comp = new ControllerComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
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
