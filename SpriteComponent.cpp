#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "JsonReader.h"

SpriteComponent::SpriteComponent(COMPONENT_TYPE type, GameObject & parent, String spriteName, int frameX, int frameY, String shader, float tileX, float tileY, Vector3D color) :
	Component(parent, type),
	m_spriteName(spriteName),
	m_texture(ResourceManager::GetInstance().GetTexture(spriteName)),
	m_mesh(*ResourceManager::GetInstance().LoadMesh("quad")),
	m_frameX(frameX), m_frameY(frameY),
	m_tileX(tileX), m_tileY(tileY),
	m_shader(shader),
	m_color(color)
{}

SpriteComponent::SpriteComponent(COMPONENT_TYPE type, const SpriteComponent & rhs, GameObject & parent) :
	Component(parent, type),
	m_spriteName(rhs.m_spriteName),
	m_texture(rhs.m_texture),
	m_mesh(rhs.m_mesh),
	m_frameX(rhs.m_frameX), m_frameY(rhs.m_frameY),
	m_tileX(rhs.m_tileX), m_tileY(rhs.m_tileY),
	m_shader(rhs.m_shader),
	m_color(rhs.m_color)
{}

SpriteComponent::SpriteComponent(GameObject & parent, String spriteName) :
	Component(parent, CT_SPRITE),
	m_spriteName(spriteName),
	m_texture(ResourceManager::GetInstance().GetTexture(spriteName)),
	m_mesh(*ResourceManager::GetInstance().LoadMesh("quad")),
	m_frameX(0), m_frameY(0),
	m_tileX(1.f), m_tileY(1.f),
	m_shader(""),
	m_color(Vector3D(1, 1, 1, 1))
{}

SpriteComponent::SpriteComponent(GameObject & parent, String spriteName, int frameX, int frameY, String shader, float tileX, float tileY, Vector3D color) :
	Component(parent, CT_SPRITE),
	m_spriteName(spriteName),
	m_texture(ResourceManager::GetInstance().GetTexture(spriteName)),
	m_mesh(*ResourceManager::GetInstance().LoadMesh("quad")),
	m_frameX(frameX), m_frameY(frameY),
	m_tileX(tileX), m_tileY(tileY),
	m_shader(shader),
	m_color(color)
{}

SpriteComponent::SpriteComponent(const SpriteComponent& rhs, GameObject& parent) :
	Component(parent, CT_SPRITE),
	m_spriteName(rhs.m_spriteName),
	m_texture(rhs.m_texture),
	m_mesh(rhs.m_mesh),
	m_frameX(rhs.m_frameX), m_frameY(rhs.m_frameY),
	m_tileX(rhs.m_tileX), m_tileY(rhs.m_tileY),
	m_shader(rhs.m_shader),
	m_color(rhs.m_color)
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

Component * SpriteComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	String spriteName = AcryJson::ParseString(j, "sprite", "name");
	int frameX = AcryJson::ParseInt(j, "sprite", "frameX");
	int frameY = AcryJson::ParseInt(j, "sprite", "frameY");
	float tileX = AcryJson::ValueExists(j, "sprite", "tileX") ? AcryJson::ParseFloat(j, "sprite", "tileX") : 1.f;
	float tileY = AcryJson::ValueExists(j, "sprite", "tileY") ? AcryJson::ParseFloat(j, "sprite", "tileY") : 1.f;
	String shader = AcryJson::ParseString(j, "sprite", "shader");
	Vector3D color = AcryJson::ParseColor(j, "sprite", "color");
	return new SpriteComponent(gObject, spriteName, frameX, frameY, shader, tileX, tileY, color);
}

void SpriteComponent::Override(nlohmann::json j)
{
	SetSprite(AcryJson::ValueExists(j, "sprite", "name") ? j["sprite"]["name"] : GetSpriteName());
	SetFrame(
		AcryJson::ValueExists(j, "sprite", "frameX") ? AcryJson::ParseInt(j, "sprite", "frameX") : m_frameX,
		AcryJson::ValueExists(j, "sprite", "frameY") ? AcryJson::ParseInt(j, "sprite", "frameY") : m_frameY
	);
	m_color = AcryJson::ValueExists(j, "sprite", "color") ? AcryJson::ParseColor(j, "sprite", "color") : m_color;
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

void SpriteComponent::SetFrame(int frameNum)
{
	m_frameX = frameNum / m_texture->surface->rows;
	m_frameY = frameNum - (m_frameX * m_texture->surface->columns);
}

void SpriteComponent::SetFrame(int x, int y)
{
	m_frameX = x;
	m_frameY = y;
}

void SpriteComponent::NextFrame()
{
	if (++m_frameX >= m_texture->surface->columns) {
		m_frameX = 0;
		if (++m_frameY >= m_texture->surface->rows)
			m_frameY = 0;
	}
}

void SpriteComponent::PrevFrame()
{
	if (--m_frameX < 0) {
		m_frameX = m_texture->surface->columns - 1;
		if (--m_frameY < 0)
			m_frameY = m_texture->surface->rows - 1;
	}
}

int SpriteComponent::GetFrame() const
{
	return m_frameX + m_frameY;
}

void SpriteComponent::GetFrame(int & x, int & y) const
{
	x = m_frameX;
	y = m_frameY;
}

float SpriteComponent::GetFrameUOffset() const
{
	return m_frameY * m_texture->surface->frameHeight;
}

float SpriteComponent::GetFrameVOffset() const
{
	return m_frameX * m_texture->surface->frameWidth;
}

float SpriteComponent::FrameHeight() const
{
	return m_texture->surface->frameHeight;
}

float SpriteComponent::FrameWidth() const
{
	return m_texture->surface->frameWidth;
}

float SpriteComponent::TileX() const
{
	return m_tileX;
}

float SpriteComponent::TileY() const
{
	return m_tileY;
}

String SpriteComponent::Shader() const
{
	return m_shader;
}

SurfaceTextureBuffer * SpriteComponent::GetTexture() const
{
	return m_texture;
}
