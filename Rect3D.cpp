#include "Rect3D.h"



Rect3D::Rect3D(Vector3D center, float halfWidth, float halfHeight) :
	m_center(center),
	m_halfWidth(halfWidth), m_halfHeight(halfHeight),
	m_left(LineSegment3D(center.getX() + halfWidth, center.getY() + halfHeight, center.getZ(),
						 center.getX() + halfWidth, center.getY() - halfHeight, center.getZ())),
	m_right(LineSegment3D(center.getX() - halfWidth, center.getY() + halfHeight, center.getZ(),
						  center.getX() - halfWidth, center.getY() - halfHeight, center.getZ())),
	m_top(LineSegment3D(center.getX() - halfWidth, center.getY() + halfHeight, center.getZ(),
						center.getX() + halfWidth, center.getY() + halfHeight, center.getZ())),
	m_bottom(LineSegment3D(center.getX() - halfWidth, center.getY() - halfHeight, center.getZ(),
						   center.getX() + halfWidth, center.getY() - halfHeight, center.getZ()))
{}

Rect3D::Rect3D(const Rect3D & rhs) :
	m_center(rhs.m_center),
	m_halfWidth(rhs.m_halfWidth), m_halfHeight(rhs.m_halfHeight),
	m_left(rhs.m_left),
	m_right(rhs.m_right),
	m_top(rhs.m_top),
	m_bottom(rhs.m_bottom)
{}

Rect3D & Rect3D::operator=(const Rect3D & rhs)
{
	m_center = rhs.m_center;
	m_halfWidth = rhs.m_halfWidth;
	m_halfHeight = rhs.m_halfHeight;
	m_left = rhs.m_left;
	m_right = rhs.m_right;
	m_top = rhs.m_top;
	m_bottom = rhs.m_bottom;
	return *this;
}

Rect3D::~Rect3D()
{}

Rect3D Rect3D::operator+(const Vector3D & rhs) const
{
	Rect3D result = Rect3D(*this);
	result.m_left += rhs;
	result.m_right += rhs;
	result.m_top += rhs;
	result.m_bottom += rhs;
	result.m_center += rhs;

	return result;
}

Rect3D Rect3D::operator-(const Vector3D & rhs) const
{
	Rect3D result = Rect3D(*this);
	result.m_left -= rhs;
	result.m_right -= rhs;
	result.m_top -= rhs;
	result.m_bottom -= rhs;
	result.m_center -= rhs;

	return result;
}

float Rect3D::Width() const
{
	return m_halfWidth * 2.f;
}

float Rect3D::Height() const
{
	return m_halfHeight * 2.f;
}

Vector3D Rect3D::Center() const
{
	return m_center;
}

LineSegment3D Rect3D::Left() const
{
	return m_left;
}

LineSegment3D Rect3D::Right() const
{
	return m_right;
}

LineSegment3D Rect3D::Top() const
{
	return m_top;
}

LineSegment3D Rect3D::Bottom() const
{
	return m_bottom;
}

Rect3D Rect3D::StretchHeight(float amount) const
{
	Rect3D result = Rect3D(*this);
	result.m_top.shiftAlongNormal(amount);
	result.m_bottom.shiftAlongNormal(-amount);
	return result;
}

Rect3D Rect3D::StretchWidth(float amount) const
{
	Rect3D result = Rect3D(*this);
	result.m_left.shiftAlongNormal(amount);
	result.m_right.shiftAlongNormal(-amount);
	return result;
}
