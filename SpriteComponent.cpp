#include "SpriteComponent.h"
#include "ResourceManager.h"

SpriteComponent::SpriteComponent(GameObject & parent, std::string spriteName) :
	Component(parent, CT_SPRITE),
	m_spriteName(spriteName),
	m_textureBuffer(ResourceManager::GetInstance().GetTexture(spriteName)),
	m_mesh(*ResourceManager::GetInstance().LoadMesh("quad"))
{}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Update(double deltaTime)
{
}

const Mesh & SpriteComponent::GetMesh() const {
	return m_mesh;
}

void SpriteComponent::SetMesh(Mesh & mesh) {
	m_mesh = mesh;
}

std::string SpriteComponent::GetSprite() const
{
	return m_spriteName;
}

void SpriteComponent::SetSprite(std::string spriteName)
{

}

GLuint SpriteComponent::GetTextureBuffer() const
{
	return m_textureBuffer;
}
