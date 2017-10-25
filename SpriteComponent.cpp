#include "SpriteComponent.h"
#include "ResourceManager.h"

SpriteComponent::SpriteComponent(GameObject & parent, std::string spriteName) :
	Component(parent, CT_SPRITE),
	m_spriteName(spriteName),
	m_mesh(*ResourceManager::GetInstance().LoadMesh("quad"))
{

}

SpriteComponent::SpriteComponent(GameObject& parent, const char * spriteName) :
	Component(parent, CT_SPRITE),
	m_spriteName(spriteName),
	m_mesh(*ResourceManager::GetInstance().LoadMesh("quad"))
{ }

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Update(double deltaTime)
{
}
