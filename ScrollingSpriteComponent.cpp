#include "ScrollingSpriteComponent.h"
#include "JsonReader.h"

ScrollingSpriteComponent::ScrollingSpriteComponent(GameObject & parent, String spriteName, int frameX, int frameY, 
	String shader, float tileX, float tileY, float speedX, float speedY) :
	SpriteComponent(CT_SCROLLING_SPRITE, parent, spriteName, frameX, frameY, shader, tileX, tileY),
	m_speedX(speedX), m_speedY(speedY)
{}

ScrollingSpriteComponent::ScrollingSpriteComponent(const ScrollingSpriteComponent & rhs, GameObject & parent) :
	SpriteComponent(CT_SCROLLING_SPRITE, rhs, parent),
	m_speedX(rhs.m_speedX), m_speedY(rhs.m_speedY)
{}

ScrollingSpriteComponent::~ScrollingSpriteComponent()
{}

void ScrollingSpriteComponent::Update(double deltaTime)
{}

ScrollingSpriteComponent * ScrollingSpriteComponent::Clone(GameObject & parent)
{
	return new ScrollingSpriteComponent(*this, parent);
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
	return new ScrollingSpriteComponent(gObject, spriteName, frameX, frameY, shader, tileX, tileY, speedX, speedY);
}

void ScrollingSpriteComponent::Override(nlohmann::json j)
{
	SetSprite(AcryJson::ValueExists(j, "sprite", "name") ? j["sprite"]["name"] : GetSpriteName());
	SetFrame(
		AcryJson::ValueExists(j, "sprite", "frameX") ? AcryJson::ParseInt(j, "sprite", "frameX") : m_frameX,
		AcryJson::ValueExists(j, "sprite", "frameY") ? AcryJson::ParseInt(j, "sprite", "frameY") : m_frameY
	);
	SetSpeed(
		AcryJson::ValueExists(j, "sprite", "scrollSpeedX") ? AcryJson::ParseInt(j, "sprite", "scrollSpeedX") : m_speedX,
		AcryJson::ValueExists(j, "sprite", "scrollSpeedY") ? AcryJson::ParseInt(j, "sprite", "scrollSpeedY") : m_speedY
	);
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
