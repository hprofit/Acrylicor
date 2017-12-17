#include "LevelManager.h"
#include "JsonReader.h"

#include "AcryEvent.h"
#include "LoadLevelEvent.h"
#include <iostream>

LevelManager::LevelManager() :
	_EventManager(EventManager::GetInstance()),
	_GameObjectManager(GameObjectManager::GetInstance())
{
	_AddSubscriberToTracker();
	SubscribeToEvent(EventType::LOAD_LEVEL);
	SubscribeToEvent(EventType::NEXT_LEVEL);
	SubscribeToEvent(EventType::RESTART_LEVEL);
}

LevelManager::~LevelManager(){}

void LevelManager::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::NEXT_LEVEL:
	{
		_EventManager.BroadcastEventToSubscribers(new AcryEvent(EventType::UNLOAD_LEVEL));
		LoadNextLevel();
	}
	break;
	case EventType::RESTART_LEVEL:
	{
		_EventManager.BroadcastEventToSubscribers(new AcryEvent(EventType::UNLOAD_LEVEL));
		LoadCurrentLevel();
	}
	break;
	case EventType::LOAD_LEVEL:
	{
		LoadLevelEvent * llEvent = static_cast<LoadLevelEvent*>(aEvent);
		if (llEvent->level <= m_lastLevel) {
			m_currentLevel = llEvent->level;
			_EventManager.BroadcastEventToSubscribers(new AcryEvent(EventType::UNLOAD_LEVEL));
			LoadCurrentLevel();
		}
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
		m_lastLevel = AcryJson::ParseInt(jsonObj, "lastLevel");
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
	if (++m_currentLevel <= m_lastLevel)
		LoadLevel(m_levels[m_currentLevel]);
	else
		LoadLevel(m_levels[0]);
}
