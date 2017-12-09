/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ShakeComponent.h
Purpose: Camera component containing several functions and objects relevant to rendering
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/08/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SHAKE_COMPONENT_H
#define SHAKE_COMPONENT_H

#include "Component.h"
#include "Vector3D.h"

class TransformComponent;

class ShakeComponent :
	public Component
{
protected:
	double m_shakeDuration;
	double m_currentShake;
	float m_shakeAmount;
	bool m_isShaking;
	Vector3D m_originalPosition;

	TransformComponent* m_tComp;
public:
	ShakeComponent() = delete;
	ShakeComponent(GameObject& parent, float shakeAmount);
	ShakeComponent(const ShakeComponent& rhs) = delete;
	ShakeComponent(const ShakeComponent& rhs, GameObject& parent);
	ShakeComponent& operator= (ShakeComponent rhs) = delete;
	~ShakeComponent();

	virtual void Update(double deltaTime);
	virtual ShakeComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();
};

#endif