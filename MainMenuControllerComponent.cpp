#include "MainMenuControllerComponent.h"
//#include "JsonReader.h"

#include "KeyPressEvent.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "WeaponComponent.h"
#include "MissileLauncherComponent.h"
#include "InputManager.h"
#include "EventManager.h"
#include "ShakeEvent.h"
#include <iostream>

MainMenuControllerComponent::MainMenuControllerComponent(GameObject& parent) :
	Component(parent, COMPONENT_TYPE::MAIN_MENU_CONTROLLER)
{
}

MainMenuControllerComponent::MainMenuControllerComponent(const MainMenuControllerComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::MAIN_MENU_CONTROLLER)
{}

MainMenuControllerComponent::~MainMenuControllerComponent(){}

void MainMenuControllerComponent::Update(double deltaTime)
{
	InputManager& inputMgr = InputManager::GetInstance();

	if (inputMgr.IsKeyTriggered(ACR_W))
		EventManager::GetInstance().BroadcastEventToSubscribers(new ShakeEvent(4.0));
	if (inputMgr.IsKeyTriggered(ACR_D))
		EventManager::GetInstance().AddDelayedEvent(new AcryEvent(EventType::RESTART_LEVEL, 0.0));
	if (inputMgr.IsKeyTriggered(ACR_SPACE))
		EventManager::GetInstance().BroadcastEventToSubscribers(new AcryEvent(EventType::SPAWN));
}

MainMenuControllerComponent * MainMenuControllerComponent::Clone(GameObject & parent)
{
	MainMenuControllerComponent* comp = new MainMenuControllerComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * MainMenuControllerComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new MainMenuControllerComponent(gObject);
}

void MainMenuControllerComponent::Override(nlohmann::json j)
{
}

void MainMenuControllerComponent::HandleEvent(AcryEvent * aEvent)
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