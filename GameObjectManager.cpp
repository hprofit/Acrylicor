#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(int numObjects) : 
	m_numObjects(numObjects)
{
	m_gameObjects = new GameObject[numObjects];
}

GameObjectManager::~GameObjectManager()
{
	for (int i = 0; i < m_numObjects; i++)
		delete m_gameObjects;
}
