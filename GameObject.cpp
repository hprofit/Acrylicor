#include "GameObject.h"
#include "GameObjectManager.h"
#include "EventManager.h"

void GameObject::_CloneChildrenGameObjects(const GameObject & rhs)
{
	GameObjectManager& gameObjMngr = GameObjectManager::GetInstance();
	for (GameObject * child : rhs.m_children) {
		GameObject * childClone = gameObjMngr.SpawnGameObject(child->m_type, this);
		AddChild(childClone);
	}
}

void GameObject::_CloneComponents(const GameObject & rhs)
{
	for (auto comp : rhs.m_components) {
		if (comp.second) {
			m_components[comp.first] = comp.second->Clone(*this);
		}
	}
}

void GameObject::_SpawnChildrenAndAttachGameObjects(const GameObject & rhs)
{
	GameObjectManager& gameObjMngr = GameObjectManager::GetInstance();
	for (String childType : rhs.m_childrenToSpawn) {
		GameObject * childClone = gameObjMngr.SpawnGameObject(childType, this);
		AddChild(childClone);
	}
}

void GameObject::_SetId(unsigned int id)
{
	m_id = id;
}

GameObject::GameObject(String type) :
	m_type(type),
	m_parent(nullptr),
	m_objectFlags(0)
{}

GameObject::GameObject(const GameObject& rhs) :
	m_type(rhs.m_type),
	m_parent(nullptr),
	m_objectFlags(0),
	m_tags(rhs.m_tags)
{
	Activate();
	_AddSubscriberToTracker();
	_CloneComponents(rhs);
}

GameObject::GameObject(const GameObject & rhs, GameObject * parent) :
	m_type(rhs.m_type),
	m_parent(parent),
	m_objectFlags(0),
	m_tags(rhs.m_tags)
{
	Activate();
	_AddSubscriberToTracker();
	_CloneComponents(rhs);
}

GameObject & GameObject::operator=(const GameObject & rhs)
{
	m_tags = rhs.m_tags;
	ClearComponents();
	Activate();
	_AddSubscriberToTracker();
	_CloneComponents(rhs);
	return *this;
}

GameObject::~GameObject()
{
	ClearComponents();
}

void GameObject::UnsubscribeChildrenFromAll()
{
	EventManager& eventMngr = EventManager::GetInstance();
	std::map<COMPONENT_TYPE, Component*>::iterator it;
	for (it = m_components.begin(); it != m_components.end(); ++it) {
		if (it->second)
			eventMngr.UnsubscribeAll(it->second);
	}
}

void GameObject::ResetFlags()
{
	m_objectFlags = 0;
}

void GameObject::Activate()
{
	m_objectFlags |= FLAG_ACTIVE;
}

void GameObject::Deactivate()
{
	m_objectFlags &= ~(FLAG_ACTIVE);
	ClearComponents();
}

bool GameObject::IsActive()
{
	return static_cast<bool>(m_objectFlags & FLAG_ACTIVE);
}

void GameObject::Kill()
{
	m_objectFlags |= FLAG_READY_TO_DIE;

	for (GameObject* child : m_children) {
		GameObjectManager::GetInstance().DestroyGameObject(child);
	}
}

bool GameObject::IsDead()
{
	return static_cast<bool>(m_objectFlags & FLAG_READY_TO_DIE);
}

void GameObject::AddChildType(String childObjectType)
{
	m_childrenToSpawn.push_back(childObjectType);
}

void GameObject::SetChildTypes(std::vector<String> childObjectTypes)
{
	m_childrenToSpawn = childObjectTypes;
}

void GameObject::SetParent(GameObject * parent)
{
	m_parent = parent;
}

void GameObject::AddChild(GameObject * child)
{
	m_children.push_back(child);
}

GameObject * GameObject::GetChildOfType(String type) const
{
	for (GameObject* child : m_children) {
		if (child->m_type.compare(type) == 0)
			return child;
	}
	return nullptr;
}

bool GameObject::Has(COMPONENT_TYPE type)
{
	return m_components[type] != NULL;
}

Component * GameObject::Get(COMPONENT_TYPE type)
{
	if (!m_components[type] && m_parent)
		return m_parent->Get(type);
	return m_components[type];
}

Component * GameObject::GetImmediate(COMPONENT_TYPE type)
{
	return m_components[type];
}

void GameObject::AddComponent(Component * component)
{
	m_components[component->m_type] = component;
}

void GameObject::ClearComponents()
{
	for (auto comp : m_components) {
		if (comp.second)
			delete comp.second;
	}
	m_components.clear();
}

std::map<COMPONENT_TYPE, Component*> GameObject::GetComponents()
{
	return m_components;
}

void GameObject::LateInitialize()
{
	for (auto comp : m_components) {
		if (comp.second)
			comp.second->LateInitialize();
	}
}

void GameObject::Update(double deltaTime)
{
	for (auto comp : m_components) {
		if (comp.second && !comp.second->IsPriorityComp())
			comp.second->Update(deltaTime);
	}
}

void GameObject::HandleEvent(AcryEvent * aEvent)
{
	for (auto comp : m_components) {
		if (comp.second)
			comp.second->HandleEvent(aEvent);
	}
	if (m_parent)
		m_parent->HandleEvent(aEvent);
}

Tags & GameObject::Tags()
{
	return m_tags;
}
