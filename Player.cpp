#include "Player.h"

Player::Player()
{
}

Player::Player(Player const & rhs)
{}

Player::~Player() {}

void Player::Update()
{
}

void Player::Update(double deltaTime)
{
	for (auto comp : m_components) {
		if (comp.second)
			comp.second->Update(deltaTime);
	}
}
