/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Math3D.h
Purpose: Provides 3D math functionality such as collision
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/03/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef MATH3D_H
#define MATH3D_H

#include "Vector3D.h"
#include "LineSegment3D.h"
#include "Rect3D.h"

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
bool StaticPointToStaticCircle(const Vector3D &pos, const Vector3D &center, float radius);

/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect
*/
bool StaticPointToStaticRect(const Vector3D &pos, const Vector3D &rect, const float halfWidth, const float halfHeight);

/*
This function determines the distance separating a point from a line

- Parameters
- P:		The point whose location should be determined
- LS:		The line segment

- Returned value: The distance. Note that the returned value should be:
- Negative if the point is in the line's inside half plane
- Positive if the point is in the line's outside half plane
- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(const Vector3D& P, const LineSegment3D& LS);


/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
bool StaticCircleToStaticCircle(const Vector3D &center0, const float radius0, const Vector3D &center1, const float radius1);


/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, halfWidth is "halfWidth0" and halfHeight is "halfHeight0"
Rectangle1: Center is pRect1, halfHeight is "halfHeight1" and halfHeight is "halfHeight1"
*/
bool StaticRectToStaticRect(const Vector3D &rect0, const float halfWidth0, const float halfHeight0, const Vector3D &rect1, const float halfWidth1, const float halfHeight1);

bool StaticRectToStaticCircle(const Vector3D &rect, const float halfWidth, const float halfHeight, const Vector3D center, const float radius);


/*
This function checks whether an animated point is colliding with a line segment

- Parameters
- Ps:		The point's starting location
- Pe:		The point's ending location
- LS:		The line segment
- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

- Returned value: Intersection time t
- -1.0f:				If there's no intersection
- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(const Vector3D& Ps, const Vector3D& Pe, const LineSegment3D& LS, Vector3D& Pi);

/*
This function checks whether an animated circle is colliding with a line segment

- Parameters
- Ps:		The center's starting location
- Pe:		The center's ending location
- Radius:	The circle's radius
- LS:		The line segment
- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

- Returned value: Intersection time t
- -1.0f:				If there's no intersection
- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticLineSegment(const Vector3D& Ps, const Vector3D& Pe, const float Radius, const LineSegment3D& LS, Vector3D& Pi);

/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line

- Parameters
- Ps:		The point's starting location
- Pe:		The point's ending location
- LS:		The line segment
- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
- R:		Reflected vector R

- Returned value: Intersection time t
- -1.0f:				If there's no intersection
- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(const Vector3D& Ps, const Vector3D& Pe, const LineSegment3D& LS, Vector3D& Pi, Vector3D& R);

/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line

- Parameters
- Ps:		The center's starting location
- Pe:		The center's ending location
- Radius:	The circle's radius
- LS:		The line segment
- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
- R:		Reflected vector R

- Returned value: Intersection time t
- -1.0f:				If there's no intersection
- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(const Vector3D& Ps, const Vector3D& Pe, const float Radius, const LineSegment3D& LS, Vector3D& Pi, Vector3D& R);

/*
This function checks whether an animated point is colliding with a static circle

- Parameters
- Ps:		The point's starting location
- Pe:		The point's ending location
- Center:	The circle's center
- Radius:	The circle's radius
- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

- Returned value: Intersection time t
- -1.0f:		If there's no intersection
- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticCircle(const Vector3D& Ps, const Vector3D& Pe, const Vector3D& Center, const float Radius, Vector3D& Pi);

/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle

- Parameters
- Ps:		The point's starting location
- Pe:		The point's ending location
- Center:	The circle's center
- Radius:	The circle's radius
- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
- R:		Reflected vector R

- Returned value: Intersection time t
- -1.0f:		If there's no intersection
- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(const Vector3D& Ps, const Vector3D& Pe, const Vector3D& Center, const float Radius, Vector3D& Pi, Vector3D& R);

/*
This function reflects an animated point on a static circle.

- Parameters
- Ps:		The point's starting location
- Pe:		The point's ending location
- Center:	The circle's center
- Pi:		Point of intersection
- timeOfInteresection	Float value of 0.f to 1.f representing when this point hit the circle this frame

- Returned value: Reflected vector
*/
Vector3D ReflectAnimatedPointOnStaticCircle(const Vector3D& Ps, const Vector3D& Pe, const Vector3D& Center, const Vector3D& Pi, const float timeOfIntersection);





/*
This function checks whether an animated circle is colliding with a static circle

- Parameters
- Center0s:		The starting position of the animated circle's center
- Center0e:		The ending position of the animated circle's center
- Radius0:		The animated circle's radius
- Center1:		The static circle's center
- Radius1:		The static circle's radius
- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

- Returned value: Intersection time t
- -1.0f:		If there's no intersection
- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(const Vector3D& ACenterS, const Vector3D& ACenterE, const float ARadius, const Vector3D& SCenter, const float SRadius, Vector3D& Pi);

/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one

- Parameters
- Center0s:		The starting position of the animated circle's center
- Center0e:		The ending position of the animated circle's center
- Radius0:		The animated circle's radius
- Center1:		The static circle's center
- Radius1:		The static circle's radius
- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
- R:			Reflected vector R

- Returned value: Intersection time t
- -1.0f:		If there's no intersection
- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticCircle(const Vector3D& ACenterS, const Vector3D& ACenterE, const float ARadius, const Vector3D& SCenter, const float SRadius, Vector3D& Pi, Vector3D& R);

/*
This function reflects an animated circle on a static circle.

- Parameters
- Center0s:		The starting position of the animated circle's center
- Center0e:		The ending position of the animated circle's center
- Radius0:		The animated circle's radius
- Center1:		The static circle's center
- Radius1:		The static circle's radius
- Pi:		Point of intersection

- Returned value: Reflected vector
*/
Vector3D ReflectAnimatedCircleOnStaticCircle(const Vector3D& ACenterS, const Vector3D& ACenterE, const float ARadius, const Vector3D& SCenter, const Vector3D& Pi, const float timeOfIntersection);



bool AnimatedCircletoAnimatedCircleWillCollideThisFrame(const Vector3D& CenterS0, const Vector3D& CenterE0, const float Radius0, const Vector3D& CenterS1, const Vector3D& CenterE1, const float Radius1);

float AnimatedCircleToAnimatedCircle(const Vector3D& Start0, const Vector3D& End0, const float Radius0, const Vector3D& Start1, const Vector3D& End1, const float Radius1, Vector3D& Pi);

Vector3D SnapPointStaticCircleToStaticRect(const Vector3D& Circle, const Vector3D& Rect, const float halfWidth, const float halfHeight);

bool StaticCircleToStaticRect(const Vector3D& Circle, const float Radius, const Vector3D& RectCenter, const float halfWidth, const float halfHeight, const Rect3D& rect);

bool AnimatedCircleToStaticRectWillCollideThisFrame(const Vector3D& CStart, const Vector3D& CEnd, const float Radius, const Vector3D& RectCenter, const float halfWidth, const float halfHeight, const Rect3D& rect);

bool AnimatedCircleToAnimatedRectWillCollideThisFrame(const Vector3D& CStart, const Vector3D& CEnd, const float Radius, const Vector3D& RectCenterStart, const Vector3D& RectCenterEnd, const float halfWidth, const float halfHeight);

float AnimatedCircleToAnimatedRect(const Vector3D& Start0, const Vector3D& End0, const float Radius, const Vector3D& Start1, const Vector3D& End1, const float halfWidth, const float halfHeight, Vector3D& Pi);


#endif