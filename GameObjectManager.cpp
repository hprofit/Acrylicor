#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "RenderManager.h"
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

void GameObjectManager::SetActiveCamera(GameObject * gObject)
{
	if (gObject->Has(CT_CAMERA))
		m_activeCamera = gObject;
}

void GameObjectManager::SpawnGameObject(String objectType)
{
	GameObject * newGameObject = GameObjectFactory::GetInstance().GetObjectArchetype(objectType);
	SetActiveCamera(newGameObject);
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

void GameObjectManager::SpawnGameObjectFromFile(nlohmann::json j)
{
	GameObject * newGameObject = GameObjectFactory::GetInstance().SpawnObjectWithOverrides(j.begin().key(), j[j.begin().key()]);
	SetActiveCamera(newGameObject);
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

void GameObjectManager::UpdateGameObjects(double deltaTime)
{
	int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i] && m_gameObjects[i]->IsActive())
			m_gameObjects[i]->Update(deltaTime);
	}
}

void GameObjectManager::RenderGameObjects()
{
	RenderManager& renderMngr = RenderManager::GetInstance();
	int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i] && m_gameObjects[i]->IsActive())
			renderMngr.RenderGameObject(*m_activeCamera, *m_gameObjects[i]);
	}
}

void GameObjectManager::RegisterCamera(Component * cameraComp)
{
	m_cameras.push_back(cameraComp);
}

void GameObjectManager::UpdateCameraObjects(double deltaTime)
{
	int i = 0;
	for (i = 0; i < m_cameras.size(); ++i) {
		if (m_cameras[i] && m_cameras[i]->m_parent.IsActive())
			m_cameras[i]->Update(deltaTime);
	}
}
