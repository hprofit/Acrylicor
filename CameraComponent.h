/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CameraComponent.h
Purpose: Camera component containing several functions and objects relevant to rendering
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

#define CAM_BOTH	0
#define CAM_PERSP	1
#define CAM_ORTHO	2

class TransformComponent;

class CameraComponent :
	public Component
{
protected:
	float m_fov, m_aspectRatio;
	unsigned int m_screenWidth, m_screenHeight;
	Matrix4x4 m_viewMatrix, m_perspectiveMatrix, m_orthographicMatrix;
	unsigned short m_cameraType;

	TransformComponent* m_tComp;

	Matrix4x4 _MatrixFromCameraVectors(const Vector3D& right, const Vector3D& up, const Vector3D& forward);
	void _CalcViewMatrix();
	void _CalcPerspectiveMatrix();
	void _CalcOrthographicMatrix();
public:
	CameraComponent() = delete;
	CameraComponent(GameObject& parent, float fov, unsigned short camType = CAM_BOTH);
	CameraComponent(const CameraComponent& rhs) = delete;
	CameraComponent(const CameraComponent& rhs, GameObject& parent);
	CameraComponent& operator= (CameraComponent rhs) = delete;
	~CameraComponent();

	virtual void Update(double deltaTime);
	virtual CameraComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager();
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();

	float GetFOV() const;
	float GetAspect() const;
	Matrix4x4 GetViewMatrix() const;
	Matrix4x4 GetPerspectiveMatrix() const;
	Matrix4x4 GetOrthographicMatrix() const;
};

#endif