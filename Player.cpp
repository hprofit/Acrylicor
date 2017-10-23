#include "Player.h"
#include "TransformComponent.h"
#include "ControllerComponent.h"
#include "SpriteComponent.h"

Player::Player()
{
	m_components[CT_CONTROLLER] = new ControllerComponent(*this);
	m_components[CT_TRANSFORM] = new TransformComponent(*this, Vector2D(0,0,0));
	m_components[CT_SPRITE] = new SpriteComponent(*this, "player");
}

Player::Player(Player const & rhs)
{}

Player::~Player() {}

void Player::Update()
{
}

void Player::Update(double deltaTime)
{
	static_cast<ControllerComponent*>(m_components[CT_CONTROLLER])->Update(deltaTime);
	static_cast<TransformComponent*>(m_components[CT_TRANSFORM])->BuildModelTransform();
}
