#include "UI_MainMenuComponent.h"
#include "JsonReader.h"

#include "LevelManager.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <string>
#include <vector>
#include <iostream>


UI_MainMenuComponent::UI_MainMenuComponent(GameObject & parent) :
	Component(parent, COMPONENT_TYPE::UI_MAIN_MENU),
	m_currOption(0)
{}

UI_MainMenuComponent::UI_MainMenuComponent(const UI_MainMenuComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::UI_MAIN_MENU),
	m_currOption(rhs.m_currOption)
{}

UI_MainMenuComponent::~UI_MainMenuComponent() {}

void UI_MainMenuComponent::Update(double deltaTime) 
{
	unsigned int index = 0;
	std::for_each(m_textComponents.begin(), m_textComponents.end(), [this, &index](TextComponent* tComp) {
		String text = tComp->Text();
		if (index == m_currOption)
			text[0] = '>';
		else
			text[0] = ' ';
		tComp->SetText(text);
		++index;
	});
}

UI_MainMenuComponent * UI_MainMenuComponent::Clone(GameObject & parent)
{
	UI_MainMenuComponent* comp = new UI_MainMenuComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * UI_MainMenuComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	UI_MainMenuComponent* comp = new UI_MainMenuComponent(gObject);
	comp->_ParseEvents(j, "uiMainMenu");

	return comp;
}

void UI_MainMenuComponent::Override(nlohmann::json j){}

void UI_MainMenuComponent::HandleEvent(AcryEvent * aEvent){}

void UI_MainMenuComponent::LateInitialize()
{
	std::vector<GameObject*> children = m_parent.GetChildren();

	std::for_each(children.begin(), children.end(), [this](GameObject* go) {
		m_textComponents.push_back(static_cast<TextComponent*>(go->Get(COMPONENT_TYPE::TEXT)));
	});
}

void UI_MainMenuComponent::NextOption()
{
	if (++m_currOption >= m_textComponents.size())
		m_currOption = 0;
}

void UI_MainMenuComponent::PrevOption()
{
	if (--m_currOption >= m_textComponents.size())
		m_currOption = m_textComponents.size() - 1;
}

void UI_MainMenuComponent::Select()
{
	switch (m_currOption) {
	case MENU_OPTION::START:
		LevelManager::GetInstance().LoadNextLevel();
		break;
	case MENU_OPTION::EXIT:
		break;
	}
}
