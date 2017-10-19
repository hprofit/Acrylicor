#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject& parent, Vector2D position) :
	Component(parent),
	m_position(position),
	m_angle(0.0f), m_scaleX(1.0f), m_scaleY(1.0f)
{}

TransformComponent::TransformComponent(GameObject& parent, Vector2D position, float angle, float scaleX, float scaleY) :
	Component(parent),
	m_position(position),
	m_angle(angle), m_scaleX(scaleX), m_scaleY(scaleY)
{}

TransformComponent::~TransformComponent()
{
}

Vector2D TransformComponent::GetPosition() const
{ 
	return m_position; 
}

void TransformComponent::SetPosition(Vector2D pos)
{
	m_position = pos; 
}

void TransformComponent::UpdatePosition(Vector2D amount)
{
	m_position += amount;
}

float TransformComponent::GetAngle() const
{
	return m_angle;
}

void TransformComponent::SetAngle(float angle) 
{
	m_angle = angle;
}

float TransformComponent::GetScaleX() const
{
	return m_scaleX;
}

void TransformComponent::SetScaleX(float scaleX) 
{
	m_scaleX = scaleX; 
}


float TransformComponent::GetScaleY() const 
{
	return m_scaleY;
}

void TransformComponent::SetScaleY(float scaleY) 
{
	m_scaleY = scaleY; 
}

Matrix4x4 TransformComponent::GetModelTransform() const {
	return m_transform;
}

void TransformComponent::BuildModelTransform()
{
	Matrix4x4 trans = Matrix4x4::Translate(Vector3D(m_position)),
		rot = Matrix4x4::Rotate(m_angle, Vector3D(0,0,1,0)),
		scale = Matrix4x4::Scale(m_scaleX, m_scaleY, 0.0f);

	m_transform = trans * rot * scale;
}