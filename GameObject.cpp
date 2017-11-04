#include "GameObject.h"

GameObject::GameObject() : 
	m_parent(nullptr),
	m_objectFlags(0)
{}

GameObject::GameObject(const GameObject& rhs) :
	m_parent(nullptr),
	m_objectFlags(0) 
{
	Activate();

	for (auto comp : rhs.m_components) {
		if (comp.second) {
			m_components[comp.first] = comp.second->Clone(*this);
		}
	}
}

GameObject & GameObject::operator=(const GameObject & rhs)
{
	ClearComponents();
	Activate();
	for (auto comp : rhs.m_components) {
		if (comp.second) {
			m_components[comp.first] = comp.second->Clone(*this);
		}
	}

	return *this;
}

GameObject::~GameObject()
{
	ClearComponents();

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
	return (m_objectFlags & FLAG_ACTIVE) == 1;
}

bool GameObject::Has(COMPONENT_TYPE type)
{
	return m_components[type] != NULL;
}

Component * GameObject::Get(COMPONENT_TYPE type)
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

void GameObject::Update(double deltaTime)
{
	for (auto comp : m_components) {
		if (comp.second && !comp.second->IsPriorityComp())
			comp.second->Update(deltaTime);
	}
}
