#include "AIBaseComponent.h"



AIBaseComponent::AIBaseComponent(COMPONENT_TYPE type, GameObject & parent) :
	Component(parent, type), m_active(true)
{}

AIBaseComponent::AIBaseComponent(COMPONENT_TYPE type, const AIBaseComponent & rhs, GameObject & parent) :
	Component(parent, type), m_active(rhs.m_active)
{}

AIBaseComponent::~AIBaseComponent(){}

void AIBaseComponent::Activate()
{
	m_active = true;
}

void AIBaseComponent::Deactivate()
{
	m_active = false;
}
