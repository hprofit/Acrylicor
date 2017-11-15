#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "RenderManager.h"
#include <iostream>

GameObjectManager::GameObjectManager(int maxObjects) :
	m_maxObjects(maxObjects)
{}

GameObjectManager::~GameObjectManager()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i])
			delete m_gameObjects[i];
	}
}

void GameObjectManager::SetActiveCamera(GameObject * gObject)
{
	if (gObject->Has(COMPONENT_TYPE::CAMERA))
		m_activeCamera = gObject;
}

GameObject * GameObjectManager::SpawnGameObject(String objectType)
{
	GameObject * newGameObject = GameObjectFactory::GetInstance().NewObjectFromArchetype(objectType);
	SetActiveCamera(newGameObject);
	unsigned int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (!m_gameObjects[i] || (m_gameObjects[i] && !m_gameObjects[i]->IsActive())) {
			m_gameObjects[i] = newGameObject;
			return newGameObject;
		}
	}
	if (i < m_maxObjects) {
		m_gameObjects.push_back(newGameObject);
		return newGameObject;
	}
	else {
		std::cerr << "Out of memory for GameObjects!" << std::endl;
		return nullptr;
	}
}

void GameObjectManager::SpawnGameObjectFromFile(nlohmann::json j)
{
	GameObject * newGameObject = GameObjectFactory::GetInstance().SpawnObjectWithOverrides(j.begin().key(), j[j.begin().key()]);
	SetActiveCamera(newGameObject);
	unsigned int i = 0;
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
	if (gObject->IsActive()) {
		gObject->ResetFlags();
	}
}

void GameObjectManager::UpdateGameObjects(double deltaTime)
{
	unsigned int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i] && m_gameObjects[i]->IsActive())
			m_gameObjects[i]->Update(deltaTime);
	}
}

void GameObjectManager::RenderGameObjects()
{
	RenderManager& renderMngr = RenderManager::GetInstance();
	unsigned int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i] && m_gameObjects[i]->IsActive())
			renderMngr.RenderGameObject(*m_activeCamera, *m_gameObjects[i]);
	}
}

void GameObjectManager::CleanUpGameObjects()
{
	unsigned int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i] && m_gameObjects[i]->IsDead())
			DestroyGameObject(m_gameObjects[i]);
	}
}

void GameObjectManager::RegisterCamera(Component * cameraComp)
{
	m_cameras.push_back(cameraComp);
}

void GameObjectManager::UpdateCameraObjects(double deltaTime)
{
	unsigned int i = 0;
	for (i = 0; i < m_cameras.size(); ++i) {
		if (m_cameras[i] && m_cameras[i]->m_parent.IsActive())
			m_cameras[i]->Update(deltaTime);
	}
}
