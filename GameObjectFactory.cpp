#include "GameObjectFactory.h"
#include <fstream>
#include <iostream>

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
}

float GameObjectFactory::ParseFloat(const json j, String comp, String prop)
{
	if (j[comp].find(prop) != j[comp].end())
		return j[comp][prop];
	return 0.0f;
}

float GameObjectFactory::ParseFloat(const json j, String comp, String prop, String coord)
{
	if (j[comp].find(prop) != j[comp].end()) {
		if (j[comp][prop].find(coord) != j[comp][prop].end())
			return j[comp][prop][coord];
	}
	return 0.0f;
}

TransformComponent * GameObjectFactory::LoadTransformComponent(GameObject* gObject, const json j)
{
	TransformComponent * tComp = new TransformComponent(*gObject);
	float x = ParseFloat(j, "transform", "position2D", "x");
	float y = ParseFloat(j, "transform", "position2D", "y");
	tComp->SetPosition(Vector2D(x, y));

	float angle = ParseFloat(j, "transform", "angle2D");
	tComp->SetAngle(angle);

	float sX = ParseFloat(j, "transform", "scale2D", "x");
	float sY = ParseFloat(j, "transform", "scale2D", "y");
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

GameObject * GameObjectFactory::LoadGameObjectFromFile(String fileName)
{
	try {
		std::ifstream i(fileName);
		json j;
		i >> j;

		GameObject * gObject = new GameObject();
		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				if (it.key().compare("transform") == 0) {
					gObject->AddComponent(LoadTransformComponent(gObject, j));
				}
				else if (it.key().compare("sprite") == 0) {
					gObject->AddComponent(LoadSpriteComponent(gObject, j));
				}
				else if (it.key().compare("controller") == 0) {
					gObject->AddComponent(LoadControllerComponent(gObject, j));
				}
				else if (it.key().compare("physicsBody") == 0) {
					gObject->AddComponent(LoadPhysicsBodyComponent(gObject, j));
				}
				else if (it.key().compare("physicsMovement") == 0) {
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

void GameObjectFactory::LoadLevelFile(String fileName)
{
}
