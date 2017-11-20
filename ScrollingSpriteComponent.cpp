#include "ScrollingSpriteComponent.h"
#include "JsonReader.h"

ScrollingSpriteComponent::ScrollingSpriteComponent(GameObject & parent, String spriteName, int frameX, int frameY, 
	String shader, float tileX, float tileY, float speedX, float speedY, Vector3D color) :
	SpriteComponent(COMPONENT_TYPE::SCROLLING_SPRITE, parent, spriteName, frameX, frameY, shader, tileX, tileY, color),
	m_speedX(speedX), m_speedY(speedY), m_offsetU(0.f), m_offsetV(0.f)
{}

ScrollingSpriteComponent::ScrollingSpriteComponent(const ScrollingSpriteComponent & rhs, GameObject & parent) :
	SpriteComponent(COMPONENT_TYPE::SCROLLING_SPRITE, rhs, parent),
	m_speedX(rhs.m_speedX), m_speedY(rhs.m_speedY), m_offsetU(rhs.m_offsetU), m_offsetV(rhs.m_offsetV)
{}

ScrollingSpriteComponent::~ScrollingSpriteComponent()
{}

void ScrollingSpriteComponent::Update(double deltaTime)
{
	m_offsetU += m_speedX * (float)deltaTime;
	m_offsetV += m_speedY * (float)deltaTime;
}

ScrollingSpriteComponent * ScrollingSpriteComponent::Clone(GameObject & parent)
{
	ScrollingSpriteComponent* comp = new ScrollingSpriteComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * ScrollingSpriteComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	String spriteName = AcryJson::ParseString(j, "scrollingSprite", "name");
	int frameX = AcryJson::ParseInt(j, "scrollingSprite", "frameX");
	int frameY = AcryJson::ParseInt(j, "scrollingSprite", "frameY");
	float tileX = AcryJson::ValueExists(j, "scrollingSprite", "tileX") ? AcryJson::ParseFloat(j, "scrollingSprite", "tileX") : 1.f;
	float tileY = AcryJson::ValueExists(j, "scrollingSprite", "tileY") ? AcryJson::ParseFloat(j, "scrollingSprite", "tileY") : 1.f;
	float speedX = AcryJson::ParseFloat(j, "scrollingSprite", "scrollSpeedX");
	float speedY = AcryJson::ParseFloat(j, "scrollingSprite", "scrollSpeedY");
	String shader = AcryJson::ParseString(j, "scrollingSprite", "shader"); 
	Vector3D color = AcryJson::ParseColor(j, "scrollingSprite", "color");
	return new ScrollingSpriteComponent(gObject, spriteName, frameX, frameY, shader, tileX, tileY, speedX, speedY, color);
}

void ScrollingSpriteComponent::Override(nlohmann::json j)
{
	SetSprite(AcryJson::ValueExists(j, "scrollingSprite", "name") ? j["scrollingSprite"]["name"] : GetSpriteName());
	SetFrame(
		AcryJson::ValueExists(j, "scrollingSprite", "frameX") ? AcryJson::ParseInt(j, "scrollingSprite", "frameX") : m_frameX,
		AcryJson::ValueExists(j, "scrollingSprite", "frameY") ? AcryJson::ParseInt(j, "scrollingSprite", "frameY") : m_frameY
	);
	SetSpeed(
		AcryJson::ValueExists(j, "scrollingSprite", "scrollSpeedX") ? AcryJson::ParseFloat(j, "scrollingSprite", "scrollSpeedX") : m_speedX,
		AcryJson::ValueExists(j, "scrollingSprite", "scrollSpeedY") ? AcryJson::ParseFloat(j, "scrollingSprite", "scrollSpeedY") : m_speedY
	);
	m_tileX = AcryJson::ValueExists(j, "scrollingSprite", "tileX") ? AcryJson::ParseFloat(j, "scrollingSprite", "tileX") : m_tileX;
	m_tileY = AcryJson::ValueExists(j, "scrollingSprite", "tileY") ? AcryJson::ParseFloat(j, "scrollingSprite", "tileY") : m_tileY;
	m_shader = AcryJson::ValueExists(j, "scrollingSprite", "shader") ? AcryJson::ParseString(j, "scrollingSprite", "shader") : m_shader;
	m_color = AcryJson::ValueExists(j, "scrollingSprite", "color") ? AcryJson::ParseColor(j, "scrollingSprite", "color") : m_color;
}

void ScrollingSpriteComponent::SetSpeed(float speedX, float speedY)
{
	m_speedX = speedX;
	m_speedY = speedY;
}

void ScrollingSpriteComponent::SetSpeedX(float speedX)
{
	m_speedX = speedX;
}

void ScrollingSpriteComponent::SetSpeedY(float speedY)
{
	m_speedY = speedY;
}
