/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Purpose: Base GameObject class
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/13/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "PhysicsBodyComponent.h"
#include "PhysicsMovementComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

#define FLAG_ACTIVE	0x00000001

class GameObject
{
private:
	unsigned long m_active;

	PhysicsBodyComponent* m_compPhysicsBody;
	PhysicsMovementComponent* m_compPhysicsMovement;
	SpriteComponent* m_compSprite;
	TransformComponent* m_compTransform;

public:
	GameObject();
	GameObject(GameObject const& rhs);
	GameObject& operator= (GameObject rhs);
	~GameObject();

	void Activate() { m_active = FLAG_ACTIVE; }
	void Deactivate() { m_active = 0; }
	unsigned long GetActive() { return m_active; }

	void AddPhysicsBodyComponent();
	void AddPhysicsMovementComponent();
	void AddSpriteComponent(char * spriteName);
	void AddTransformComponent(Vector2D position, float angle, float scaleX, float scaleY);

	// Const Forms
	const PhysicsBodyComponent* GetPhysicsBodyComponent() const { return m_compPhysicsBody; }
	const PhysicsMovementComponent* GetPhysicsMovementComponent() const { return m_compPhysicsMovement; }
	const SpriteComponent* GetSpriteComponent() const { return m_compSprite; }
	const TransformComponent* GetTransformComponent() const { return m_compTransform; }

	// Non-Const Forms
	PhysicsBodyComponent* GetPhysicsBodyComponent() { return m_compPhysicsBody; }
	PhysicsMovementComponent* GetPhysicsMovementComponent() { return m_compPhysicsMovement; }
	SpriteComponent* GetSpriteComponent() { return m_compSprite; }
	TransformComponent* GetTransformComponent() { return m_compTransform; }
};

#endif