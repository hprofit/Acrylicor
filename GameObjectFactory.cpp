#include "GameObjectFactory.h"
#include <iostream>
#include "JsonReader.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ScrollingSpriteComponent.h"
#include "TextComponent.h"
#include "PhysicsComponent.h"
#include "ControllerComponent.h"
#include "GameOverControllerComponent.h"
#include "MainMenuControllerComponent.h"
#include "AIManagerComponent.h"
#include "AISwayComponent.h"
#include "AIRushComponent.h"
#include "AISeekComponent.h"
#include "AIAreaOfSightComponent.h"
#include "AISquareSwayComponent.h"
#include "AIFireGunComponent.h"
#include "AISwarmComponent.h"
#include "AISpawnOnDeathComponent.h"
#include "WeaponComponent.h"
#include "MissileLauncherComponent.h"
#include "CameraComponent.h"
#include "SpawnerComponent.h"
#include "HealthComponent.h"
#include "EnergyComponent.h"
#include "DamageComponent.h"
#include "UI_LivesComponent.h"
#include "UI_MissilesComponent.h"
#include "UI_ScoreComponent.h"
#include "UI_EnergyComponent.h"
#include "UI_MainMenuComponent.h"
#include "KillZoneComponent.h"
#include "DashComponent.h"
#include "GoalComponent.h"
#include "PickupComponent.h"
#include "TimeToLiveComponent.h"
#include "ShakeComponent.h"
#include "ScoreComponent.h"

GameObjectFactory::GameObjectFactory() {}

GameObjectFactory::~GameObjectFactory()
{
	for (auto comp : m_gameObjectTypes) {
		if (comp.second)
			delete comp.second;
	}
	m_gameObjectTypes.clear();
}

GameObject * GameObjectFactory::_SpawnObjectWithOverrides(String objectType, json j)
{
	GameObject * gObject = NewObjectFromArchetype(objectType);
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		if (AcryJson::KeyIs(it, "transform"))				gObject->Get(COMPONENT_TYPE::TRANSFORM)->Override(j);
		else if (AcryJson::KeyIs(it, "sprite"))				gObject->Get(COMPONENT_TYPE::SPRITE)->Override(j);
		else if (AcryJson::KeyIs(it, "scrollingSprite"))	gObject->Get(COMPONENT_TYPE::SCROLLING_SPRITE)->Override(j);
		else if (AcryJson::KeyIs(it, "text"))				gObject->Get(COMPONENT_TYPE::TEXT)->Override(j);
		else if (AcryJson::KeyIs(it, "controller"))			gObject->Get(COMPONENT_TYPE::CONTROLLER)->Override(j);
		else if (AcryJson::KeyIs(it, "gameOverController"))	gObject->Get(COMPONENT_TYPE::GAME_OVER_CONTROLLER)->Override(j);
		else if (AcryJson::KeyIs(it, "mainMenuController"))	gObject->Get(COMPONENT_TYPE::MAIN_MENU_CONTROLLER)->Override(j);
		else if (AcryJson::KeyIs(it, "physics"))			gObject->Get(COMPONENT_TYPE::PHYSICS)->Override(j);
		else if (AcryJson::KeyIs(it, "aiManager"))			gObject->Get(COMPONENT_TYPE::AI_MANAGER)->Override(j);
		else if (AcryJson::KeyIs(it, "aiSway"))				gObject->Get(COMPONENT_TYPE::AI_SWAY)->Override(j);
		else if (AcryJson::KeyIs(it, "aiRush"))				gObject->Get(COMPONENT_TYPE::AI_RUSH)->Override(j);
		else if (AcryJson::KeyIs(it, "aiSeek"))				gObject->Get(COMPONENT_TYPE::AI_SEEK)->Override(j);
		else if (AcryJson::KeyIs(it, "aiAreaOfSight"))		gObject->Get(COMPONENT_TYPE::AI_AREA_OF_SIGHT)->Override(j);
		else if (AcryJson::KeyIs(it, "aiSquareSway"))		gObject->Get(COMPONENT_TYPE::AI_SQUARE_SWAY)->Override(j);
		else if (AcryJson::KeyIs(it, "aiFireGun"))			gObject->Get(COMPONENT_TYPE::AI_FIRE_GUN)->Override(j);
		else if (AcryJson::KeyIs(it, "aiSwarm"))			gObject->Get(COMPONENT_TYPE::AI_SWARM)->Override(j);
		else if (AcryJson::KeyIs(it, "aiSpawnOnDeath"))		gObject->Get(COMPONENT_TYPE::AI_SPAWN_ON_DEATH)->Override(j);
		else if (AcryJson::KeyIs(it, "spawner"))			gObject->Get(COMPONENT_TYPE::SPAWNER)->Override(j);
		else if (AcryJson::KeyIs(it, "weapon"))				gObject->Get(COMPONENT_TYPE::WEAPON)->Override(j);
		else if (AcryJson::KeyIs(it, "missileLauncher"))	gObject->Get(COMPONENT_TYPE::MISSILE_LAUNCHER)->Override(j);
		else if (AcryJson::KeyIs(it, "camera"))				gObject->Get(COMPONENT_TYPE::CAMERA)->Override(j);
		else if (AcryJson::KeyIs(it, "health"))				gObject->Get(COMPONENT_TYPE::HEALTH)->Override(j);
		else if (AcryJson::KeyIs(it, "energy"))				gObject->Get(COMPONENT_TYPE::ENERGY)->Override(j);
		else if (AcryJson::KeyIs(it, "damage"))				gObject->Get(COMPONENT_TYPE::DAMAGE)->Override(j);
		else if (AcryJson::KeyIs(it, "uiLives"))			gObject->Get(COMPONENT_TYPE::UI_LIVES)->Override(j);
		else if (AcryJson::KeyIs(it, "uiMissiles"))			gObject->Get(COMPONENT_TYPE::UI_MISSILES)->Override(j);
		else if (AcryJson::KeyIs(it, "uiScore"))			gObject->Get(COMPONENT_TYPE::UI_SCORE)->Override(j);
		else if (AcryJson::KeyIs(it, "uiEnergy"))			gObject->Get(COMPONENT_TYPE::UI_ENERGY)->Override(j);
		else if (AcryJson::KeyIs(it, "uiMainMenu"))			gObject->Get(COMPONENT_TYPE::UI_MAIN_MENU)->Override(j);
		else if (AcryJson::KeyIs(it, "killZone"))			gObject->Get(COMPONENT_TYPE::KILL_ZONE)->Override(j);
		else if (AcryJson::KeyIs(it, "dash"))				gObject->Get(COMPONENT_TYPE::DASH)->Override(j);
		else if (AcryJson::KeyIs(it, "goal"))				gObject->Get(COMPONENT_TYPE::GOAL)->Override(j);
		else if (AcryJson::KeyIs(it, "pickup"))				gObject->Get(COMPONENT_TYPE::PICKUP)->Override(j);
		else if (AcryJson::KeyIs(it, "ttl"))				gObject->Get(COMPONENT_TYPE::TIME_TO_LIVE)->Override(j);
		else if (AcryJson::KeyIs(it, "shake"))				gObject->Get(COMPONENT_TYPE::SHAKE)->Override(j);
		else if (AcryJson::KeyIs(it, "score"))				gObject->Get(COMPONENT_TYPE::SCORE)->Override(j);
	}
	return gObject;
}

GameObject * GameObjectFactory::_GetObjectArchetype(String objectType)
{
	if (m_gameObjectTypes.find(objectType) != m_gameObjectTypes.end())
		return m_gameObjectTypes[objectType];
	else {
		std::cerr << "Game object of type <" << objectType << "> does not exist." << std::endl;
		return nullptr;
	}
}

void GameObjectFactory::_AttachGameObjectToParentGameObjectArchetype(String parentName, GameObject * child)
{
	GameObject * parent = _GetObjectArchetype(parentName);
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
				if (AcryJson::KeyIs(it, "transform"))				gObject->AddComponent(TransformComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "sprite"))				gObject->AddComponent(SpriteComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "scrollingSprite"))	gObject->AddComponent(ScrollingSpriteComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "text"))				gObject->AddComponent(TextComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "controller"))			gObject->AddComponent(ControllerComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "gameOverController"))	gObject->AddComponent(GameOverControllerComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "mainMenuController"))	gObject->AddComponent(MainMenuControllerComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "physics"))			gObject->AddComponent(PhysicsComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiManager"))			gObject->AddComponent(AIManagerComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiSway"))				gObject->AddComponent(AISwayComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiRush"))				gObject->AddComponent(AIRushComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiSeek"))				gObject->AddComponent(AISeekComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiAreaOfSight"))		gObject->AddComponent(AIAreaOfSightComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiSquareSway"))		gObject->AddComponent(AISquareSwayComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiFireGun"))			gObject->AddComponent(AIFireGunComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiSwarm"))			gObject->AddComponent(AISwarmComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "aiSpawnOnDeath"))		gObject->AddComponent(AISpawnOnDeathComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "spawner"))			gObject->AddComponent(SpawnerComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "weapon"))				gObject->AddComponent(WeaponComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "missileLauncher"))	gObject->AddComponent(MissileLauncherComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "camera"))				gObject->AddComponent(CameraComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "health"))				gObject->AddComponent(HealthComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "energy"))				gObject->AddComponent(EnergyComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "damage"))				gObject->AddComponent(DamageComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "uiLives"))			gObject->AddComponent(UI_LivesComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "uiMissiles"))			gObject->AddComponent(UI_MissilesComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "uiScore"))			gObject->AddComponent(UI_ScoreComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "uiEnergy"))			gObject->AddComponent(UI_EnergyComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "uiMainMenu"))			gObject->AddComponent(UI_MainMenuComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "killZone"))			gObject->AddComponent(KillZoneComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "dash"))				gObject->AddComponent(DashComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "goal"))				gObject->AddComponent(GoalComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "pickup"))				gObject->AddComponent(PickupComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "ttl"))				gObject->AddComponent(TimeToLiveComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "shake"))				gObject->AddComponent(ShakeComponent::Serialize(*gObject, j));
				else if (AcryJson::KeyIs(it, "score"))				gObject->AddComponent(ScoreComponent::Serialize(*gObject, j));

				// Special case, hook up to parent from here
				else if (AcryJson::KeyIs(it, "parent"))				_AttachGameObjectToParentGameObjectArchetype(j["parent"], gObject);
				// Special case, hook up children from here
				else if (AcryJson::KeyIs(it, "children"))			gObject->SetChildTypes(j["children"]);
				// Special case, attach tags to this object
				else if (AcryJson::KeyIs(it, "tags"))				
					gObject->Tags().SetTags(j["tags"]);
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
