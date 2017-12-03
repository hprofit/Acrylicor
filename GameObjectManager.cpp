#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "RenderManager.h"
#include "EventManager.h"
#include "GODestroyedEvent.h"
#include <iostream>

GameObjectManager::GameObjectManager(unsigned int maxObjects) :
	m_currentId(0), m_maxObjects(maxObjects)
{
	SubscribeToEvent(EventType::UNLOAD_LEVEL);
}

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

GameObject * GameObjectManager::_AddGameObjectToList(GameObject * gameObject)
{
	_SetActiveCamera(gameObject);
	unsigned int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i] && !m_gameObjects[i]->IsActive()) {
			delete m_gameObjects[i];
			m_gameObjects[i] = gameObject;
			return gameObject;
		}
		else if (!m_gameObjects[i]) {
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

GameObject * GameObjectManager::_GetObjectArchetype(String objectType)
{
	if (m_debugMode) std::cout << "Spawning object <" << objectType << ">" << std::endl;
	return GameObjectFactory::GetInstance()._GetObjectArchetype(objectType);
}

unsigned int GameObjectManager::_GetNextId()
{
	return ++m_currentId;
}

void GameObjectManager::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::UNLOAD_LEVEL:
	{
		DestroyAllGameObjects();
	}
	break;
	}
}

GameObject * GameObjectManager::SpawnGameObject(String objectType)
{
	return SpawnGameObject(objectType, nullptr);
}

GameObject * GameObjectManager::SpawnGameObject(String objectType, GameObject * parent)
{
	GameObject * gameObjArchetype = _GetObjectArchetype(objectType);

	GameObject * newGameObject = new GameObject(*gameObjArchetype, parent);
	newGameObject->_SetId(_GetNextId());
	newGameObject->_CloneChildrenGameObjects(*gameObjArchetype);
	newGameObject->_SpawnChildrenAndAttachGameObjects(*gameObjArchetype);

	newGameObject->LateInitialize();
	return _AddGameObjectToList(newGameObject);
}

void GameObjectManager::SpawnGameObjectFromFile(nlohmann::json j)
{
	String objectType = j.begin().key();
	GameObject * newGameObject = GameObjectFactory::GetInstance()._SpawnObjectWithOverrides(objectType, j[objectType]);
	newGameObject->_SetId(_GetNextId());
	GameObject * gameObjArchetype = _GetObjectArchetype(objectType);
	newGameObject->_CloneChildrenGameObjects(*gameObjArchetype);
	newGameObject->_SpawnChildrenAndAttachGameObjects(*gameObjArchetype);

	_AddGameObjectToList(newGameObject);
}

void GameObjectManager::DestroyGameObject(GameObject * gObject)
{
	if (m_debugMode) std::cout << "Destroying object <" << gObject->m_type << ">" << std::endl;
	gObject->Kill();
	EventManager::GetInstance().BroadcastEventToSubscribers(new GODestroyedEvent(0.0, gObject));
	EventManager::GetInstance().UnsubscribeAll(gObject);
}

void GameObjectManager::DestroyAllGameObjects()
{
	unsigned int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i] && m_gameObjects[i]->IsActive()) {
			m_gameObjects[i]->Kill();
			EventManager::GetInstance().UnsubscribeAll(m_gameObjects[i]);
		}
	}
	CleanUpGameObjects();
	if (m_debugMode) std::cout << "All game objects destroyed and cleaned up" << std::endl;
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
		if (m_gameObjects[i] && m_gameObjects[i]->IsDead()) {
			if (m_debugMode) std::cout << "Cleaning up object <" << m_gameObjects[i]->m_type << ">" << std::endl;
			delete m_gameObjects[i];
			m_gameObjects[i] = nullptr;
		}
	}
	m_gameObjects.erase(
		std::remove(m_gameObjects.begin(), m_gameObjects.end(), nullptr),
		m_gameObjects.end()
	);
}

void GameObjectManager::RegisterCamera(Component * cameraComp)
{
	m_cameras.push_back(cameraComp);
}

void GameObjectManager::RemoveCamera(Component * cameraComp)
{
	std::vector<Component*>::iterator position = std::find(m_cameras.begin(), m_cameras.end(), cameraComp);
	if (position != m_cameras.end())
		m_cameras.erase(position);
}

void GameObjectManager::UpdateCameraObjects(double deltaTime)
{
	unsigned int i = 0;
	for (i = 0; i < m_cameras.size(); ++i) {
		if (m_cameras[i] && m_cameras[i]->m_parent.IsActive())
			m_cameras[i]->Update(deltaTime);
	}
}

void GameObjectManager::LateInitializeGameObjects()
{
	unsigned int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i] && m_gameObjects[i]->IsActive())
			m_gameObjects[i]->LateInitialize();
	}
}

std::vector<GameObject*> GameObjectManager::GetObjectsWithTag(String tag)
{
	std::vector<GameObject*> objects;

	unsigned int i = 0;
	for (i = 0; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i] && m_gameObjects[i]->IsActive() && m_gameObjects[i]->Tags().HasTag(tag))
			objects.push_back(m_gameObjects[i]);
	}

	return objects;
}
