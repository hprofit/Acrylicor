#include "GameObject.h"

GameObject::GameObject() : m_active(0) {}

GameObject::GameObject(GameObject const& rhs) : m_active(0) {
	Activate();

	for (auto comp : rhs.m_components) {
		if (comp.second) {
			m_components[comp.first] = comp.second->Clone(*this);
		}
	}
}

GameObject::~GameObject()
{
	for (auto comp : m_components) {
		if (comp.second)
			delete comp.second;
	}
	m_components.clear();
}

void GameObject::Activate()
{
	m_active |= FLAG_ACTIVE;
}

void GameObject::Deactivate()
{
	m_active &= ~(FLAG_ACTIVE);
}

unsigned long GameObject::GetActive()
{
	return m_active;
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

void GameObject::Update(double deltaTime)
{
	for (auto comp : m_components) {
		if (comp.second)
			comp.second->Update(deltaTime);
	}
}
