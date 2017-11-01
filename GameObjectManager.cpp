#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include <iostream>

GameObjectManager::GameObjectManager(int maxObjects) :
	m_maxObjects(maxObjects)
{}

GameObjectManager::~GameObjectManager()
{
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i])
			delete m_gameObjects[i];
	}
}

void GameObjectManager::SpawnGameObject(String objectType)
{
	int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (!m_gameObjects[i] || (m_gameObjects[i] && !m_gameObjects[i]->IsActive())) {
			m_gameObjects[i] = GameObjectFactory::GetInstance().GetObjectArchetype(objectType);
			return;
		}
	}
	if (i < m_maxObjects)
		m_gameObjects.push_back(GameObjectFactory::GetInstance().GetObjectArchetype(objectType));
	else
		std::cerr << "Out of memory for GameObjects!" << std::endl;
}

void GameObjectManager::SpawnGameObjectFromFile(nlohmann::json j)
{
	GameObject * newGameObject = GameObjectFactory::GetInstance().SpawnObjectWithOverrides(j.begin().key(), j[j.begin().key()]);
	int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (!m_gameObjects[i] || (m_gameObjects[i] && !m_gameObjects[i]->IsActive())) {
			m_gameObjects[i] = newGameObject;
			return;
		}
	}
	if (i < m_maxObjects)
		m_gameObjects.push_back(newGameObject);
	else
		std::cerr << "Out of memory for GameObjects!" << std::endl;
}

void GameObjectManager::DestroyGameObject(GameObject * gObject)
{
	if (gObject->IsActive())
		gObject->Deactivate();
}
