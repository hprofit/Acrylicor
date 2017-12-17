#include "MainMenuControllerComponent.h"
//#include "JsonReader.h"

#include "KeyPressEvent.h"

#include "GameObject.h"
#include "UI_MainMenuComponent.h"
#include "InputManager.h"
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
		m_mmComp->PrevOption();
	if (inputMgr.IsKeyTriggered(ACR_S))
		m_mmComp->NextOption();
	if (inputMgr.IsKeyTriggered(ACR_SPACE))
		m_mmComp->Select();
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

void MainMenuControllerComponent::LateInitialize()
{
	m_mmComp = static_cast<UI_MainMenuComponent*>(m_parent.Get(COMPONENT_TYPE::UI_MAIN_MENU));
	if (!m_mmComp)
		std::cout << "MainMenuController components require UI_MainMenu components." << std::endl;
}
