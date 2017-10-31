#include "SpriteComponent.h"
#include "ResourceManager.h"

SpriteComponent::SpriteComponent(GameObject & parent, String spriteName) :
	Component(parent, CT_SPRITE),
	m_spriteName(spriteName),
	m_texture(ResourceManager::GetInstance().GetTexture(spriteName)),
	//m_textureBuffer(ResourceManager::GetInstance().GetTexture(spriteName)),
	m_mesh(*ResourceManager::GetInstance().LoadMesh("quad"))
{}

SpriteComponent::SpriteComponent(const SpriteComponent& rhs, GameObject& parent) :
	Component(parent, CT_SPRITE),
	m_spriteName(rhs.m_spriteName),
	m_texture(rhs.m_texture),
	//m_textureBuffer(rhs.m_textureBuffer),
	m_mesh(rhs.m_mesh)
{}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Update(double deltaTime)
{
}

SpriteComponent * SpriteComponent::Clone(GameObject& parent)
{
	return new SpriteComponent(*this, parent);
}

const Mesh & SpriteComponent::GetMesh() const {
	return m_mesh;
}

void SpriteComponent::SetMesh(Mesh & mesh) {
	m_mesh = mesh;
}

String SpriteComponent::GetSpriteName() const
{
	return m_spriteName;
}

void SpriteComponent::SetSprite(String spriteName)
{
	m_texture = ResourceManager::GetInstance().GetTexture(spriteName);
}

GLuint SpriteComponent::GetTextureBuffer() const
{
	return m_texture->bufferId;
}

bool SpriteComponent::TextureHasAlpha() const
{
	return m_texture->surface->hasAlpha;
}
