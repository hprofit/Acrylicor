#ifndef MATH2D_H
#define MATH2D_H

#include "Vector2D.h"

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
bool StaticPointToStaticCircle(const Vector2D &pos, const Vector2D &center, float radius);


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
bool StaticPointToStaticRect(const Vector2D &pos, const Vector2D &rect, const float width, const float height);

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
bool StaticCircleToStaticCircle(const Vector2D &center0, const float radius0, const Vector2D &center1, const float radius1);

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
bool StaticRectToStaticRect(const Vector2D &rect0, const float width0, const float height0, const Vector2D &rect1, const float width1, const float height1);


#endif