#include "LineSegment3D.h"

LineSegment3D::LineSegment3D(float x0, float y0, float z0, float x1, float y1, float z1) :
	m_p0(Vector3D(x0, y0, z0)),
	m_p1(Vector3D(x1, y1, z1)),
	m_norm(Vector3D()),
	m_nDotP0(Vector3D::Dot(m_p0, m_norm))
{ 
	// This will NOT work if both points are going in the same direction
	float proj = Vector3D::Dot(m_p1, Vector3D::Normalize(m_p0));
	float scalar = proj / m_p0.Length();
	m_norm = m_p1 - (scalar * m_p0); 
}

LineSegment3D::LineSegment3D(Vector3D Point0, Vector3D Point1) :
	m_p0(Point0),
	m_p1(Point1),
	m_norm(Vector3D::Normalize(m_p0 - m_p1)),
	m_nDotP0(Vector3D::Dot(m_p0, m_norm))
{ }

LineSegment3D::~LineSegment3D() {}

void LineSegment3D::setP0(Vector3D p0)
{
	m_p0 = p0;
	m_norm = Vector3D::Normalize(m_p0 - m_p1);
	m_nDotP0 = Vector3D::Dot(m_p0, m_norm);
}

void LineSegment3D::setP1(Vector3D p1)
{
	m_p1 = p1;
	m_norm = Vector3D::Normalize(m_p0 - m_p1);
	m_nDotP0 = Vector3D::Dot(m_p0, m_norm);
}