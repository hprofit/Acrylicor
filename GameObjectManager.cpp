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

GameObject * GameObjectManager::SpawnGameObject(String objectType)
{
	return SpawnGameObject(objectType, nullptr);
}

GameObject * GameObjectManager::SpawnGameObject(String objectType, GameObject * parent)
{
	GameObject * gameObjArchetype = _GetObjectArchetype(objectType);

	GameObject * newGameObject = new GameObject(*gameObjArchetype, parent);
	newGameObject->_CloneChildren(*gameObjArchetype);
	newGameObject->_SpawnChildrenAndAttach(*gameObjArchetype);

	return _AddGameObjectToList(newGameObject);
}

void GameObjectManager::SpawnGameObjectFromFile(nlohmann::json j)
{
	String objectType = j.begin().key();
	GameObject * newGameObject = GameObjectFactory::GetInstance()._SpawnObjectWithOverrides(objectType, j[objectType]);

	GameObject * gameObjArchetype = _GetObjectArchetype(objectType);
	newGameObject->_CloneChildren(*gameObjArchetype);
	newGameObject->_SpawnChildrenAndAttach(*gameObjArchetype);

	_AddGameObjectToList(newGameObject);
}

void GameObjectManager::DestroyGameObject(GameObject * gObject)
{
	if (m_debugMode) std::cout << "Destroying object <" << gObject->m_type << ">" << std::endl;
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
		if (m_gameObjects[i] && m_gameObjects[i]->IsDead()) {
			if (m_debugMode) std::cout << "Destroying object <" << m_gameObjects[i]->m_type << ">" << std::endl;
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
