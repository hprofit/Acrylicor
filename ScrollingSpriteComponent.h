/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScrollingSpriteComponent.h
Purpose: Scrolling Sprite Component class - renders a sprite to scrolling across the mesh continuously.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SCROLLING_SPRITE_COMPONENT_H
#define SCROLLING_SPRITE_COMPONENT_H

#include "SpriteComponent.h"
class ScrollingSpriteComponent :
	public SpriteComponent
{
protected:
	float m_speedX, m_speedY;
	float m_offsetU, m_offsetV;
public:
	ScrollingSpriteComponent() = delete;
	ScrollingSpriteComponent(GameObject& parent, String spriteName, int frameX, int frameY, String shader, float tileX = 1.f, float tileY = 1.f, float speedX = 1.f, float speedY = 1.f);
	ScrollingSpriteComponent(const ScrollingSpriteComponent& rhs) = delete;
	ScrollingSpriteComponent(const ScrollingSpriteComponent& rhs, GameObject& parent);
	ScrollingSpriteComponent& operator= (ScrollingSpriteComponent rhs) = delete;
	~ScrollingSpriteComponent();

	virtual void Update(double deltaTime);
	virtual ScrollingSpriteComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);

	float SpeedX() const { return m_speedX; }
	float SpeedY() const { return m_speedY; }
	void SetSpeed(float speedX, float speedY);
	void SetSpeedX(float speedX);
	void SetSpeedY(float speedY);
	float U() const { return m_offsetU; }
	float V() const { return m_offsetV; }
};

#endif