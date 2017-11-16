#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "RenderManager.h"
#include <iostream>

GameObjectManager::GameObjectManager(unsigned int maxObjects) :
	m_maxObjects(maxObjects)
{}

GameObjectManager::~GameObjectManager()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i])
			delete m_gameObjects[i];
	}
}

void GameObjectManager::_SetActiveCamera(GameObject * gObject)
{
	if (gObject->Has(COMPONENT_TYPE::CAMERA))
		m_activeCamera = gObject;
}

GameObject * GameObjectManager::_SpawnObject(GameObject * gameObject)
{
	_SetActiveCamera(gameObject);
	unsigned int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (!m_gameObjects[i] || (m_gameObjects[i] && !m_gameObjects[i]->IsActive())) {
			m_gameObjects[i] = gameObject;
			return gameObject;
		}
	}
	if (i < m_maxObjects) {
		m_gameObjects.push_back(gameObject);
		return gameObject;
	}
	else {
		std::cerr << "Out of memory for GameObjects!" << std::endl;
		return nullptr;
	}
}

GameObject * GameObjectManager::SpawnGameObject(String objectType)
{
	GameObjectFactory& gameObjFactory = GameObjectFactory::GetInstance();
	GameObject * gameObjArchetype = gameObjFactory.GetObjectArchetype(objectType);

	GameObject * newGameObject = new GameObject(*gameObjArchetype);
	newGameObject->CloneChildren(*gameObjArchetype);

	return _SpawnObject(newGameObject);
}

GameObject * GameObjectManager::SpawnGameObject(String objectType, GameObject * parent)
{
	GameObjectFactory& gameObjFactory = GameObjectFactory::GetInstance();
	GameObject * gameObjArchetype = gameObjFactory.GetObjectArchetype(objectType);

	GameObject * newGameObject = new GameObject(*gameObjArchetype, parent);
	newGameObject->CloneChildren(*gameObjArchetype);

	return _SpawnObject(newGameObject);
}

void GameObjectManager::SpawnGameObjectFromFile(nlohmann::json j)
{
	String objectType = j.begin().key();
	GameObjectFactory& gameObjFactory = GameObjectFactory::GetInstance();

	GameObject * gameObjArchetype = gameObjFactory.GetObjectArchetype(objectType);
	GameObject * newGameObject = gameObjFactory.SpawnObjectWithOverrides(objectType, j[objectType]);
	newGameObject->CloneChildren(*gameObjArchetype);

	_SpawnObject(newGameObject);
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
