#include "GameObjectFactory.h"
#include <iostream>
#include "JsonReader.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "PhysicsBodyComponent.h"
#include "PhysicsMovementComponent.h"
#include "ControllerComponent.h"

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

//TransformComponent * GameObjectFactory::LoadTransformComponent(GameObject* gObject, const json j)
//{
//	TransformComponent * tComp = new TransformComponent(*gObject);
//	float x = AcryJson::ParseFloat(j, "transform", "position", "x");
//	float y = AcryJson::ParseFloat(j, "transform", "position", "y");
//	float z = AcryJson::ParseFloat(j, "transform", "position", "y");
//	tComp->SetPosition(Vector3D(x, y, z));
//
//	float rX = AcryJson::ParseFloat(j, "transform", "angle", "xRot");
//	float rY = AcryJson::ParseFloat(j, "transform", "angle", "yRot");
//	float rZ = AcryJson::ParseFloat(j, "transform", "angle", "zRot");
//	tComp->SetAngles(rX, rY, rZ);
//
//	float sX = AcryJson::ParseFloat(j, "transform", "scale", "x");
//	float sY = AcryJson::ParseFloat(j, "transform", "scale", "y");
//	float sZ = AcryJson::ParseFloat(j, "transform", "scale", "z");
//	tComp->SetScale(sX, sY);
//
//	return tComp;
//}
//
//void GameObjectFactory::OverrideComponent(TransformComponent * tComp, const json j)
//{
//	Vector3D pos = tComp->GetPosition();
//	pos.Set(
//		AcryJson::ValueExists(j, "transform", "position", "x") ? AcryJson::ParseFloat(j, "transform", "position", "x") : pos.getX(),
//		AcryJson::ValueExists(j, "transform", "position", "y") ? AcryJson::ParseFloat(j, "transform", "position", "y") : pos.getY(),
//		AcryJson::ValueExists(j, "transform", "position", "z") ? AcryJson::ParseFloat(j, "transform", "position", "z") : pos.getZ()
//	);
//	tComp->SetPosition(pos);
//
//	float rX = tComp->GetAngleX();
//	float rY = tComp->GetAngleY();
//	float rZ = tComp->GetAngleZ();
//	tComp->SetAngles(
//		AcryJson::ValueExists(j, "transform", "angle", "xRot") ? AcryJson::ParseFloat(j, "transform", "angle", "xRot") : rX,
//		AcryJson::ValueExists(j, "transform", "angle", "yRot") ? AcryJson::ParseFloat(j, "transform", "angle", "yRot") : rY,
//		AcryJson::ValueExists(j, "transform", "angle", "zRot") ? AcryJson::ParseFloat(j, "transform", "angle", "zRot") : rZ
//	);
//
//	float sX = tComp->GetScaleX();
//	float sY = tComp->GetScaleY();
//	float sZ = tComp->GetScaleZ();
//	tComp->SetScale(
//		AcryJson::ValueExists(j, "transform", "scale", "x") ? AcryJson::ParseFloat(j, "transform", "scale", "x") : sX,
//		AcryJson::ValueExists(j, "transform", "scale", "y") ? AcryJson::ParseFloat(j, "transform", "scale", "y") : sY,
//		AcryJson::ValueExists(j, "transform", "scale", "z") ? AcryJson::ParseFloat(j, "transform", "scale", "z") : sZ
//	);
//
//}
//
//SpriteComponent * GameObjectFactory::LoadSpriteComponent(GameObject * gObject, const json j)
//{
//	String spriteName = j["sprite"]["name"].is_string() ? j["sprite"]["name"] : "";
//	return new SpriteComponent(*gObject, spriteName);
//}
//
//void GameObjectFactory::OverrideComponent(SpriteComponent * tComp, const json j)
//{
//	tComp->SetSprite(AcryJson::ValueExists(j, "sprite", "name") ? j["sprite"]["name"] : tComp->GetSpriteName());
//}
//
//ControllerComponent * GameObjectFactory::LoadControllerComponent(GameObject * gObject, const json j)
//{
//	return new ControllerComponent(*gObject);
//}
//
//void GameObjectFactory::OverrideComponent(ControllerComponent * tComp, const json j)
//{
//}
//
//PhysicsBodyComponent * GameObjectFactory::LoadPhysicsBodyComponent(GameObject * gObject, const json j)
//{
//	return new PhysicsBodyComponent(*gObject);
//}
//
//void GameObjectFactory::OverrideComponent(PhysicsBodyComponent * tComp, const json j)
//{
//}
//
//PhysicsMovementComponent * GameObjectFactory::LoadPhysicsMovementComponent(GameObject * gObject, const json j)
//{
//	return new PhysicsMovementComponent(*gObject);
//}
//
//void GameObjectFactory::OverrideComponent(PhysicsMovementComponent * tComp, const json j)
//{
//}

GameObject * GameObjectFactory::SpawnObjectWithOverrides(String objectType, json j)
{
	GameObject * gObject = new GameObject(*GetObjectArchetype(objectType));
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		if (AcryJson::KeyIs(it, "transform"))
			gObject->Get(CT_TRANSFORM)->Override(j);
		else if (AcryJson::KeyIs(it, "sprite"))
			gObject->Get(CT_SPRITE)->Override(j);
		else if (AcryJson::KeyIs(it, "controller"))
			gObject->Get(CT_CONTROLLER)->Override(j);
		else if (AcryJson::KeyIs(it, "physicsBody"))
			gObject->Get(CT_PHYSICS_BODY)->Override(j);
		else if (AcryJson::KeyIs(it, "physicsMovement"))
			gObject->Get(CT_PHYSICS_MOVEMENT)->Override(j);
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
				if(AcryJson::KeyIs(it, "transform")) {
					gObject->AddComponent(TransformComponent::Serialize(*gObject, j));
				}
				else if (AcryJson::KeyIs(it, "sprite")) {
					gObject->AddComponent(SpriteComponent::Serialize(*gObject, j));
				}
				else if (AcryJson::KeyIs(it, "controller")) {
					gObject->AddComponent(ControllerComponent::Serialize(*gObject, j));
				}
				else if (AcryJson::KeyIs(it, "physicsBody")) {
					gObject->AddComponent(PhysicsBodyComponent::Serialize(*gObject, j));
				}
				else if (AcryJson::KeyIs(it, "physicsMovement")) {
					gObject->AddComponent(PhysicsMovementComponent::Serialize(*gObject, j));
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
				m_gameObjectTypes[it.key()] = LoadGameObjectFromFile(j[it.key()]);
			}
		}
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}
