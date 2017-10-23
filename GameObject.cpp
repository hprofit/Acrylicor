#include "GameObject.h"

GameObject::GameObject(){}

GameObject::GameObject(GameObject const & rhs){}

GameObject::~GameObject()
{
	for (auto comp : m_components)
		delete comp.second;
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

void GameObject::Update()
{
}
