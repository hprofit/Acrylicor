#include "Player.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

Player::Player()
{
	m_components[CT_TRANSFORM] = new TransformComponent(*this, Vector2D(0,0,0));
	m_components[CT_SPRITE] = new SpriteComponent(*this, "player");
}

Player::Player(Player const & rhs)
{}

Player::~Player() {}

void Player::Update()
{
	static_cast<TransformComponent*>(m_components[CT_TRANSFORM])->BuildModelTransform();
}
