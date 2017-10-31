/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Purpose: Provides a camera that can be used for viewing the game scene.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/16/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3D.h"
#include "Matrix4x4.h"

#define CAM_BOTH	0
#define CAM_PERSP	1
#define CAM_ORTHO	2

class Camera
{
private:
	Vector3D m_position;
	Vector3D m_lookat;
	float m_xRot, m_yRot, m_fov, m_aspectRatio;
	Matrix4x4 m_viewMatrix, m_perspectiveMatrix, m_orthographicMatrix;
	unsigned short m_cameraType;

	Matrix4x4 MatrixFromCameraVectors(const Vector3D& right, const Vector3D& up, const Vector3D& forward);
	Vector3D GetCameraRight();
	Vector3D GetCameraUp(const Vector3D& forward, const Vector3D& right);
	void CalcViewMatrix();
	void CalcPerspectiveMatrix();
	void CalcOrthographicMatrix();
public:
	Camera();
	Camera(Vector3D pos, Vector3D lookat, unsigned short camType = CAM_BOTH);
	Camera(Vector3D pos, Vector3D lookat, float xRot, float yRot, unsigned short camType = CAM_BOTH);
	Camera(Vector3D pos, Vector3D lookat, float xRot, float yRot, float fov, unsigned short camType = CAM_BOTH);
	Camera(Camera const& rhs);
	Camera& operator= (Camera rhs);
	~Camera();

	void Update();
	void RotateCamera(float x, float y);

	Vector3D GetPosition() const;
	Vector3D GetLookAt() const;
	float GetXRot() const;
	float GetYRot() const;
	float GetFOV() const;
	float GetAspect() const;
	Matrix4x4 GetViewMatrix() const;
	Matrix4x4 GetPerspectiveMatrix() const;
	Matrix4x4 GetOrthographicMatrix() const;

};

#endif