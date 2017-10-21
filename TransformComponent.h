/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformComponent.h
Purpose: Transform Component class - contains position, scale, rotation, transformation matrix
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/17/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include "Vector2D.h"
#include "Matrix4x4.h"

class TransformComponent :
	public Component
{
protected:
	Vector2D m_position;
	float m_angle, m_scaleX, m_scaleY;
	Matrix4x4 m_transform;

public:
	TransformComponent() = delete;
	TransformComponent(GameObject& parent, Vector2D position);
	TransformComponent(GameObject& parent, Vector2D position, float angle, float scaleX, float scaleY);
	TransformComponent(TransformComponent const& rhs) = delete;
	~TransformComponent();

	virtual void Update();

	Vector2D GetPosition() const;
	void SetPosition(Vector2D pos);
	void Move(Vector2D amount);

	float GetAngle() const;
	void SetAngle(float angle);

	float GetScaleX() const;
	void SetScaleX(float scaleX);

	float GetScaleY() const;
	void SetScaleY(float scaleY);

	void SetScale(float scale);

	Matrix4x4 GetModelTransform() const;
	void BuildModelTransform();
};

#endif