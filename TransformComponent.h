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

class PhysicsComponent;

class TransformComponent :
	public Component
{
protected:
	Vector3D m_position;
	float m_angleX, m_angleY, m_angleZ;
	Vector3D m_lookAt;
	float m_scaleX, m_scaleY, m_scaleZ;
	Matrix4x4 m_transform;
	bool m_2d;

	void WrapAngle(float & angle);
	void UpdateLookAt();
	void Set2D(bool is2D);
public:
	friend PhysicsComponent;

	TransformComponent() = delete;
	TransformComponent(GameObject& parent, bool is2D = true);
	TransformComponent(GameObject& parent, Vector3D position, bool is2D = true);
	TransformComponent(GameObject& parent, Vector3D position, float angleZ, float scaleX, float scaleY, bool is2D = true);
	TransformComponent(GameObject& parent, Vector3D position, float angleX, float angleY, float angleZ, float scaleX, float scaleY, float scaleZ, bool is2D = true);
	TransformComponent(const TransformComponent& rhs, GameObject& parent);
	TransformComponent& operator=(const TransformComponent& rhs);
	virtual ~TransformComponent();

	virtual void Update(double deltaTime);
	virtual TransformComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager();

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

	Vector3D Forward() const;
	Vector3D Right() const;
	Vector3D Up() const;

	Vector3D LookAt() const;

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