/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Rect3D.h
Purpose: Rect3D class that contains LineSegment3D objects able to represent the edges
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/19/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef RECT3D_H
#define RECT3D_H

#include "LineSegment3D.h"

class Rect3D
{
protected:
	Vector3D& m_center;
	float m_halfWidth;
	float m_halfHeight;
	LineSegment3D& m_left;
	LineSegment3D& m_right;
	LineSegment3D& m_top;
	LineSegment3D& m_bottom;
	Vector3D& m_upVec;
	Vector3D& m_rightVec;

public:
	Rect3D(Vector3D center, float halfWidth, float halfHeight);
	Rect3D(const Rect3D& rhs);
	Rect3D& operator=(const Rect3D& rhs);
	~Rect3D();

	Rect3D operator+(const Vector3D& rhs) const;
	Rect3D operator-(const Vector3D& rhs) const;

	float Width() const;
	float Height() const;

	Vector3D Center() const;
	LineSegment3D Left() const;
	LineSegment3D Right() const;
	LineSegment3D Top() const;
	LineSegment3D Bottom() const;

	Vector3D UpVec() const;
	Vector3D RightVec() const;

	Rect3D StretchHeight(float amount) const;
	Rect3D StretchWidth(float amount) const;
};

#endif