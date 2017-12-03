/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CollisionResult.h
Purpose: Contains the resulting collision data between two objects - indicates if they collided, when, and where their surfaces touched
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/21/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef COLLISION_RESULT_H
#define COLLISION_RESULT_H

#include "Vector3D.h"


struct CollisionResult {
	bool collided;
	float timeOfImpact;
	Vector3D pointOfImpact;
	Vector3D lhs_poi;
	Vector3D rhs_poi;

	CollisionResult(bool _collided = false) :
		collided(_collided), timeOfImpact(-1.f), pointOfImpact(Vector3D()), lhs_poi(Vector3D()), rhs_poi(Vector3D()) {};

	CollisionResult(const CollisionResult& rhs) : 
		collided(rhs.collided), 
		timeOfImpact(rhs.timeOfImpact),
		pointOfImpact(rhs.pointOfImpact), 
		lhs_poi(rhs.lhs_poi),
		rhs_poi(rhs.rhs_poi) {}

	CollisionResult& operator=(const CollisionResult& rhs) {
		collided = rhs.collided;
		timeOfImpact = rhs.timeOfImpact;
		pointOfImpact = rhs.pointOfImpact;
		lhs_poi = rhs.lhs_poi;
		rhs_poi = rhs.rhs_poi;
		return *this;
	}

	void Set(float toi, Vector3D poi, Vector3D lhs, Vector3D rhs) {
		timeOfImpact = toi;
		pointOfImpact = poi;
		lhs_poi = lhs;
		rhs_poi = rhs;
		collided = true;
	}
};

#endif