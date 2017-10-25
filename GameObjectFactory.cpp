#include "GameObjectFactory.h"
#include <fstream>

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
}

TransformComponent * GameObjectFactory::LoadTransformComponent(GameObject* gObject, const json j)
{
	TransformComponent * tComp = new TransformComponent(*gObject);

	float x = j["transform"]["position2D"]["x"].is_number() ? j["transform"]["position2D"]["x"] : 0.0f;
	float y = j["transform"]["position2D"]["y"].is_number() ? j["transform"]["position2D"]["y"] : 0.0f;
	tComp->SetPosition(Vector2D(x, y));

	float angle = j["transform"]["angle2D"].is_number() ? j["transform"]["angle2D"] : 0.0f;
	tComp->SetAngle(angle);

	float sX = j["transform"]["scale2D"]["x"].is_number() ? j["transform"]["scale2D"]["x"] : 0.0f;
	float sY = j["transform"]["scale2D"]["y"].is_number() ? j["transform"]["scale2D"]["y"] : 0.0f;
	tComp->SetScale(sX, sY);

	return tComp;
}

SpriteComponent * GameObjectFactory::LoadSpriteComponent(GameObject * gObject, const json j)
{
	std::string spriteName = j["sprite"]["name"].is_string() ? j["sprite"]["name"] : "";
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

GameObject * GameObjectFactory::LoadGameObjectFromFile(const char * fileName)
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
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
}
