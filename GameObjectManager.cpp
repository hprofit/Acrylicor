#include "GameObjectManager.h"

GameObjectManager::~GameObjectManager()
{
	for (int i = 0; i < m_numObjects; i++)
		delete m_gameObjects;
}
