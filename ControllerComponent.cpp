#include "ControllerComponent.h"
//#include "JsonReader.h"

#include "KeyPressEvent.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "WeaponComponent.h"
#include "MissileLauncherComponent.h"
#include "InputManager.h"

#include <iostream>

ControllerComponent::ControllerComponent(GameObject& parent) :
	Component(parent, COMPONENT_TYPE::CONTROLLER)
{
}

ControllerComponent::ControllerComponent(const ControllerComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::CONTROLLER)
{}

ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Update(double deltaTime)
{
	InputManager& inputMgr = InputManager::GetInstance();
	//PhysicsComponent* pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	//WeaponComponent* wComp = static_cast<WeaponComponent*>(m_parent.GetChildOfType("gun")->Get(COMPONENT_TYPE::WEAPON));
	//MissileLauncherComponent* mlComp = static_cast<MissileLauncherComponent*>(m_parent.GetChildOfType("missileLauncher")->Get(COMPONENT_TYPE::MISSILE_LAUNCHER));

	// TODO: HOOK THESE UP TO EVENTS
	//sComp->SetFrame(2, 2);
	float force = 10000.0f;
	if (m_pComp) {
		if (inputMgr.IsKeyPressed(ACR_W)) {
			m_pComp->AddForce(Vector3D(0.f, force, 0.f));
		}
		if (inputMgr.IsKeyPressed(ACR_S)) {
			m_pComp->AddForce(Vector3D(0.f, -force, 0.f));
		}

		if (inputMgr.IsKeyPressed(ACR_A)) {
			m_pComp->AddForce(Vector3D(-force, 0.f, 0.f));
		}
		if (inputMgr.IsKeyPressed(ACR_D)) {
			m_pComp->AddForce(Vector3D(force, 0.f, 0.f));
		}
	}

	if (inputMgr.IsKeyPressed(ACR_SPACE) && m_wComp)
		m_wComp->Fire();
	if (inputMgr.IsKeyTriggered(ACR_F) && m_mlComp)
		m_mlComp->Fire();
	if (inputMgr.IsKeyTriggered(ACR_LSHIFT))
		m_parent.HandleEvent(new AcryEvent(EventType::DASH));
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
			std::cout << kpEvent->GetKey() << std::endl;
		}
			break;
	}
}

void ControllerComponent::LateInitialize()
{
	m_pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	if (!m_pComp)
		std::cout << "Controller components require Physics components." << std::endl;

	m_wComp = static_cast<WeaponComponent*>(m_parent.GetChildOfType("gun")->Get(COMPONENT_TYPE::WEAPON));
	if (!m_wComp)
		std::cout << "Controller components require Weapon components." << std::endl;
	m_mlComp = static_cast<MissileLauncherComponent*>(m_parent.GetChildOfType("missileLauncher")->Get(COMPONENT_TYPE::MISSILE_LAUNCHER));
	if (!m_pComp)
		std::cout << "Controller components require Missile Launcher components." << std::endl;
}
