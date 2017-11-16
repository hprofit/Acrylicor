#include "GameObjectFactory.h"
#include <iostream>
#include "JsonReader.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ScrollingSpriteComponent.h"
#include "PhysicsComponent.h"
#include "ControllerComponent.h"
#include "AISwayComponent.h"
#include "AIRushComponent.h"
#include "WeaponComponent.h"
#include "CameraComponent.h"
#include "HealthComponent.h"
#include "DamageComponent.h"

GameObjectFactory::GameObjectFactory()
{}

GameObjectFactory::~GameObjectFactory()
{
	for (auto comp : m_gameObjectTypes) {
		if (comp.second)
			delete comp.second;
	}
	m_gameObjectTypes.clear();
}

GameObject * GameObjectFactory::SpawnObjectWithOverrides(String objectType, json j)
{
	GameObject * gObject = NewObjectFromArchetype(objectType);
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		if (AcryJson::KeyIs(it, "transform"))
			gObject->Get(COMPONENT_TYPE::TRANSFORM)->Override(j);
		else if (AcryJson::KeyIs(it, "sprite"))
			gObject->Get(COMPONENT_TYPE::SPRITE)->Override(j);
		else if (AcryJson::KeyIs(it, "scrollingSprite"))
			gObject->Get(COMPONENT_TYPE::SCROLLING_SPRITE)->Override(j);
		else if (AcryJson::KeyIs(it, "controller"))
			gObject->Get(COMPONENT_TYPE::CONTROLLER)->Override(j);
		else if (AcryJson::KeyIs(it, "physics"))
			gObject->Get(COMPONENT_TYPE::PHYSICS)->Override(j);
		else if (AcryJson::KeyIs(it, "aiSway"))
			gObject->Get(COMPONENT_TYPE::AI_SWAY)->Override(j);
		else if (AcryJson::KeyIs(it, "aiRush"))
			gObject->Get(COMPONENT_TYPE::AI_RUSH)->Override(j);
		else if (AcryJson::KeyIs(it, "weapon"))
			gObject->Get(COMPONENT_TYPE::WEAPON)->Override(j);
		else if (AcryJson::KeyIs(it, "camera"))
			gObject->Get(COMPONENT_TYPE::CAMERA)->Override(j);
		else if (AcryJson::KeyIs(it, "health"))
			gObject->Get(COMPONENT_TYPE::HEALTH)->Override(j);
		else if (AcryJson::KeyIs(it, "damage"))
			gObject->Get(COMPONENT_TYPE::DAMAGE)->Override(j);
	}
	return gObject;
}

GameObject * GameObjectFactory::GetObjectArchetype(String objectType)
{
	if (m_gameObjectTypes.find(objectType) != m_gameObjectTypes.end())
		return m_gameObjectTypes[objectType];
	else {
		std::cerr << "Game object of type <" << objectType << "> does not exist." << std::endl;
		return nullptr;
	}
}

void GameObjectFactory::AttachGameObjectToParentGameObjectArchetype(String parentName, GameObject * child)
{
	GameObject * parent = GetObjectArchetype(parentName);
	if (!parent) {
		std::cout << "No such parent object <" << parentName << "> exists!" << std::endl;
		return;
	}
	child->SetParent(parent);
	parent->AddChild(child);
}

GameObject * GameObjectFactory::NewObjectFromArchetype(String objectType)
{
	if (m_gameObjectTypes.find(objectType) != m_gameObjectTypes.end())
		return new GameObject(*m_gameObjectTypes[objectType]);
	else {
		std::cerr << "Game object of type <" << objectType << "> does not exist." << std::endl;
		return nullptr;
	}
}

GameObject * GameObjectFactory::LoadGameObjectFromFile(String fileName, String objectName)
{
	try {
		json j = AcryJson::OpenJsonFile(fileName);
		GameObject * gObject = new GameObject(objectName);
		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				if (AcryJson::KeyIs(it, "transform"))
					gObject->AddComponent(TransformComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "sprite"))
					gObject->AddComponent(SpriteComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "scrollingSprite"))
					gObject->AddComponent(ScrollingSpriteComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "controller"))
					gObject->AddComponent(ControllerComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "physics"))
					gObject->AddComponent(PhysicsComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiSway"))
					gObject->AddComponent(AISwayComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiRush"))
					gObject->AddComponent(AIRushComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "weapon"))
					gObject->AddComponent(WeaponComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "camera"))
					gObject->AddComponent(CameraComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "health"))
					gObject->AddComponent(HealthComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "damage"))
					gObject->AddComponent(DamageComponent::Serialize(*gObject, j));

				// Special case, hook up to parent from here
				else if (AcryJson::KeyIs(it, "parent")) {
					AttachGameObjectToParentGameObjectArchetype(j["parent"], gObject);
				}
			}
		}
		return gObject;
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
		return nullptr;
	}
}

void GameObjectFactory::LoadGameObjectsFromFile(String fileName)
{
	try {
		json j = AcryJson::OpenJsonFile(fileName);

		if (j.is_array()) {
			int numObjs = j.size();
			for (int i = 0; i < numObjs; ++i) {
				json::iterator it = j[i].begin();
				String objectName = it.key();
				m_gameObjectTypes[objectName] = LoadGameObjectFromFile(j[i][objectName], objectName);
			}
		}
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}
