#include "SpriteComponent.h"
#include "ResourceManager.h"

SpriteComponent::SpriteComponent(GameObject& parent, const char * meshName) : 
	Component(parent, CT_SPRITE),
	m_mesh(*ResourceManager::GetInstance().LoadMesh(meshName))
{ }

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Update()
{
}
