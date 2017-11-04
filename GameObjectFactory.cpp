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
#include "CameraComponent.h"

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
	GameObject * gObject = new GameObject(*GetObjectArchetype(objectType));
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		if (AcryJson::KeyIs(it, "transform"))
			gObject->Get(CT_TRANSFORM)->Override(j);
		else if (AcryJson::KeyIs(it, "sprite"))
			gObject->Get(CT_SPRITE)->Override(j);
		else if (AcryJson::KeyIs(it, "scrollingSprite"))
			gObject->Get(CT_SCROLLING_SPRITE)->Override(j);
		else if (AcryJson::KeyIs(it, "controller"))
			gObject->Get(CT_CONTROLLER)->Override(j);
		else if (AcryJson::KeyIs(it, "physics"))
			gObject->Get(CT_PHYSICS)->Override(j);
		else if (AcryJson::KeyIs(it, "aiSway"))
			gObject->Get(CT_AI_SWAY)->Override(j);
		else if (AcryJson::KeyIs(it, "aiRush"))
			gObject->Get(CT_AI_RUSH)->Override(j);
		else if (AcryJson::KeyIs(it, "camera"))
			gObject->Get(CT_CAMERA)->Override(j);
	}
	return gObject;
}

GameObject * GameObjectFactory::GetObjectArchetype(String objectType)
{
	if (m_gameObjectTypes.find(objectType) != m_gameObjectTypes.end())
		return m_gameObjectTypes[objectType];
	else {
		std::cerr << "Game object of type: " << objectType << " does not exist." << std::endl;
		return nullptr;
	}
}

GameObject * GameObjectFactory::LoadGameObjectFromFile(String fileName)
{
	try {
		json j = AcryJson::OpenJsonFile(fileName);
		GameObject * gObject = new GameObject();
		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				if(AcryJson::KeyIs(it, "transform"))
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
				else if (AcryJson::KeyIs(it, "camera"))
					gObject->AddComponent(CameraComponent::Serialize(*gObject, j));
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

		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				m_gameObjectTypes[it.key()] = LoadGameObjectFromFile(j[it.key()]);
			}
		}
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}
