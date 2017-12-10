#include "GameOverControllerComponent.h"
//#include "JsonReader.h"

#include "KeyPressEvent.h"

#include "GameObject.h"
#include "InputManager.h"
#include "EventManager.h"
#include <iostream>

GameOverControllerComponent::GameOverControllerComponent(GameObject& parent) :
	Component(parent, COMPONENT_TYPE::GAME_OVER_CONTROLLER)
{
}

GameOverControllerComponent::GameOverControllerComponent(const GameOverControllerComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::GAME_OVER_CONTROLLER)
{}

GameOverControllerComponent::~GameOverControllerComponent(){}

void GameOverControllerComponent::Update(double deltaTime)
{
	InputManager& inputMgr = InputManager::GetInstance();

	if (inputMgr.IsKeyTriggered(ACR_R))
		EventManager::GetInstance().AddDelayedEvent(new AcryEvent(EventType::RESTART_LEVEL, 0.0));
}

GameOverControllerComponent * GameOverControllerComponent::Clone(GameObject & parent)
{
	GameOverControllerComponent* comp = new GameOverControllerComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * GameOverControllerComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new GameOverControllerComponent(gObject);
}

void GameOverControllerComponent::Override(nlohmann::json j)
{
}

void GameOverControllerComponent::HandleEvent(AcryEvent * aEvent)
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