#include "GameObjectFactory.h"
#include <iostream>
#include "JsonReader.h"

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
}

TransformComponent * GameObjectFactory::LoadTransformComponent(GameObject* gObject, const json j)
{
	TransformComponent * tComp = new TransformComponent(*gObject);
	float x = AcryJson::ParseFloat(j, "transform", "position2D", "x");
	float y = AcryJson::ParseFloat(j, "transform", "position2D", "y");
	tComp->SetPosition(Vector2D(x, y));

	float angle = AcryJson::ParseFloat(j, "transform", "angle2D");
	tComp->SetAngle(angle);

	float sX = AcryJson::ParseFloat(j, "transform", "scale2D", "x");
	float sY = AcryJson::ParseFloat(j, "transform", "scale2D", "y");
	tComp->SetScale(sX, sY);

	return tComp;
}

SpriteComponent * GameObjectFactory::LoadSpriteComponent(GameObject * gObject, const json j)
{
	String spriteName = j["sprite"]["name"].is_string() ? j["sprite"]["name"] : "";
	return new SpriteComponent(*gObject, spriteName);
}

ControllerComponent * GameObjectFactory::LoadControllerComponent(GameObject * gObject, const json j)
{
	return new ControllerComponent(*gObject);
}

PhysicsBodyComponent * GameObjectFactory::LoadPhysicsBodyComponent(GameObject * gObject, const json j)
{
	return new PhysicsBodyComponent(*gObject);
}

PhysicsMovementComponent * GameObjectFactory::LoadPhysicsMovementComponent(GameObject * gObject, const json j)
{
	return new PhysicsMovementComponent(*gObject);
}

void GameObjectFactory::AddComponentType(String componentType, Component * component)
{
	m_components[componentType] = component;
}

GameObject * GameObjectFactory::SpawnObject(String objectType)
{
	if (m_gameObjectTypes.find(objectType) != m_gameObjectTypes.end())
		return new GameObject(m_gameObjectTypes[objectType]);
	std::cerr << "Game object of type: " << objectType << " does not exist." << std::endl;
	return nullptr;
}

GameObject * GameObjectFactory::LoadGameObjectFromFile(String fileName)
{
	try {
		json j = AcryJson::OpenJsonFile(fileName);
		GameObject * gObject = new GameObject();
		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				if(AcryJson::KeyIs(it, "transform")) {
					gObject->AddComponent(LoadTransformComponent(gObject, j));
				}
				else if (AcryJson::KeyIs(it, "sprite")) {
					gObject->AddComponent(LoadSpriteComponent(gObject, j));
				}
				else if (AcryJson::KeyIs(it, "controller")) {
					gObject->AddComponent(LoadControllerComponent(gObject, j));
				}
				else if (AcryJson::KeyIs(it, "physicsBody")) {
					gObject->AddComponent(LoadPhysicsBodyComponent(gObject, j));
				}
				else if (AcryJson::KeyIs(it, "physicsMovement")) {
					gObject->AddComponent(LoadPhysicsMovementComponent(gObject, j));
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

		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				m_gameObjectTypes[it.key()] = *LoadGameObjectFromFile(j[it.key()]);
			}
		}
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}

void GameObjectFactory::LoadLevelFile(String fileName)
{
	try {
		json j = AcryJson::OpenJsonFile(fileName);

		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				// TODO: Load entities into GameObjectManager
			}
		}
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}
