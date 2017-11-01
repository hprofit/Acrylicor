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
#include "Vector3D.h"
#include "Matrix4x4.h"

#define X_AXIS	0
#define Y_AXIS	1
#define Z_AXIS	2

class TransformComponent :
	public Component
{
protected:
	Vector3D m_position;
	float m_angleX, m_angleY, m_angleZ;
	float m_scaleX, m_scaleY, m_scaleZ;
	Matrix4x4 m_transform;

	void WrapAngle(float & angle);

public:
	TransformComponent() = delete;
	TransformComponent(GameObject& parent);
	TransformComponent(GameObject& parent, Vector3D position);
	TransformComponent(GameObject& parent, Vector3D position, float angleZ, float scaleX, float scaleY);
	TransformComponent(GameObject& parent, Vector3D position, float angleX, float angleY, float angleZ, float scaleX, float scaleY, float scaleZ);
	TransformComponent(const TransformComponent& rhs, GameObject& parent);
	TransformComponent& operator=(const TransformComponent& rhs);
	~TransformComponent();

	virtual void Update(double deltaTime);
	virtual TransformComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);

	Vector3D GetPosition() const;
	void SetPosition(Vector3D pos);
	void Move(Vector3D amount);

	void SetAngles(float angleX, float angleY, float angleZ);
	float GetAngleX() const { return m_angleX; }
	void SetAngleX(float angle);
	float GetAngleY() const { return m_angleY; }
	void SetAngleY(float angle);
	float GetAngleZ() const { return m_angleZ; }
	void SetAngleZ(float angle);

	void RotateX(float amount);
	void RotateY(float amount);
	void RotateZ(float amount);

	float GetScaleX() const;
	void SetScaleX(float scaleX);
	void ScaleX(float amount);

	float GetScaleY() const;
	void SetScaleY(float scaleY);
	void ScaleY(float amount);

	float GetScaleZ() const;
	void SetScaleZ(float scaleZ);
	void ScaleZ(float amount);

	void SetScaleUniform(float amount);
	void SetScale(float scaleX, float scaleY);
	void SetScale(float scaleX, float scaleY, float scaleZ);
	void ScaleUniform(float amount);

	Matrix4x4 GetModelTransform() const;
	void BuildModelTransform();
};

#endif