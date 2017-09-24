#include "Math2D.h"
#include "stdio.h"

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "radius"
*/
bool StaticPointToStaticCircle(const Vector2D &pos, const Vector2D &center, float radius)
{
	float sqDistance = Vector2D::SquareDistance(pos, center);
	return sqDistance <= (radius * radius);
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "width" and height is height
*/
bool StaticPointToStaticRect(const Vector2D &pos, const Vector2D &rect, const float width, const float height)
{
	float halfwidth = width / 2.0f, halfheight = height / 2.0f;
	float left = rect.m_x - halfwidth,
		right = rect.m_x + halfwidth,
		top = rect.m_y + halfheight,
		bottom = rect.m_y - halfheight;
	return (pos.m_x >= left && pos.m_x <= right && pos.m_y <= top && pos.m_y >= bottom);
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "radius0"
Circle1: Center is Center1, radius is "radius1"
*/
bool StaticCircleToStaticCircle(const Vector2D &center0, const float radius0, const Vector2D &center1, const float radius1)
{
	float sqDistance = Vector2D::SquareDistance(center0, center1),
			radiusSum = radius0 + radius1;
	return sqDistance <= (radiusSum * radiusSum);
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is rect0, width is "width0" and height is "height0"
Rectangle1: Center is rect1, width is "width1" and height is "height1"
*/
bool StaticRectToStaticRect(const Vector2D &rect0, const float width0, const float height0, const Vector2D &rect1, const float width1, const float height1)
{
	float halfwidth0 = width0 / 2.0f, halfheight0 = height0 / 2.0,
		halfwidth1 = width1 / 2.0f, halfheight1 = height1 / 2.0;
	float left0 = rect0.m_x - halfwidth0,
		right0 = rect0.m_x + halfwidth0,
		top0 = rect0.m_y + halfheight0,
		bottom0 = rect0.m_y - halfheight0,
		left1 = rect1.m_x - halfwidth1,
		right1 = rect1.m_x + halfwidth1,
		top1 = rect1.m_y + halfheight1,
		bottom1 = rect1.m_y - halfheight1;

	return !(top1 < bottom0 || left1 > right0 || right1 < left0 || bottom1 > top0);
}
