#include "LevelManager.h"
#include "JsonReader.h"

#include <iostream>

LevelManager::LevelManager() :
	_EventManager(EventManager::GetInstance()),
	_GameObjectManager(GameObjectManager::GetInstance())
{}

LevelManager::~LevelManager(){}

void LevelManager::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::NEXT_LEVEL:
	{

	}
	break;
	}
}

void LevelManager::LoadLevelConfig(String fileName)
{
	try {
		json jsonObj = AcryJson::OpenJsonFile(fileName);
		json j = jsonObj["levels"];

		if (j.is_array()) {
			int numObjs = j.size();
			for (int i = 0; i < numObjs; ++i)
				m_levels.push_back(j[i]);
		}

		m_currentLevel = AcryJson::ParseInt(jsonObj, "baseLevel");
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}

void LevelManager::LoadLevel(String fileName)
{
	try {
		json j = AcryJson::OpenJsonFile(fileName)["objects"];

		if (j.is_array()) {
			int numObjs = j.size();
			for (int i = 0; i < numObjs; ++i)
				_GameObjectManager.SpawnGameObjectFromFile(j[i]);
		}

		_GameObjectManager.LateInitializeGameObjects();
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}

void LevelManager::LoadCurrentLevel()
{
	LoadLevel(m_levels[m_currentLevel]);
}

void LevelManager::LoadNextLevel()
{
	LoadLevel(m_levels[++m_currentLevel]);
}
