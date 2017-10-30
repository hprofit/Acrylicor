#include "TransformComponent.h"
#include <cmath>

TransformComponent::TransformComponent(GameObject & parent) :
	Component(parent, CT_TRANSFORM),
	m_position(Vector2D(0.f, 0.f)),
	m_angle(0.0f),
	m_scaleX(1.0f), m_scaleY(1.0f), m_scaleZ(1.0f)
{
}

TransformComponent::TransformComponent(GameObject& parent, Vector2D position) :
	Component(parent, CT_TRANSFORM),
	m_position(position),
	m_angle(0.0f), 
	m_scaleX(1.0f), m_scaleY(1.0f), m_scaleZ(1.0f)
{}

TransformComponent::TransformComponent(GameObject& parent, Vector2D position, float angle, float scaleX, float scaleY) :
	Component(parent, CT_TRANSFORM),
	m_position(position),
	m_angle(angle),
	m_scaleX(scaleX), m_scaleY(scaleY), m_scaleZ(1.0f)
{}

TransformComponent::TransformComponent(GameObject & parent, Vector2D position, float angle, float scaleX, float scaleY, float scaleZ) :
	Component(parent, CT_TRANSFORM),
	m_position(position),
	m_angle(angle), 
	m_scaleX(scaleX), m_scaleY(scaleY), m_scaleZ(scaleZ)
{
}

TransformComponent::TransformComponent(const TransformComponent & rhs, GameObject& parent) :
	Component(m_parent, CT_TRANSFORM),
	m_position(rhs.m_position),
	m_angle(rhs.m_angle),
	m_scaleX(rhs.m_scaleX), m_scaleY(rhs.m_scaleY), m_scaleZ(rhs.m_scaleZ)
{
}

TransformComponent & TransformComponent::operator=(const TransformComponent& rhs)
{

	m_position = rhs.m_position;
	m_angle = rhs.m_angle;
	m_scaleX = rhs.m_scaleX;
	m_scaleY = rhs.m_scaleY;
	m_scaleZ = rhs.m_scaleZ;
	return *this;
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Update(double deltaTime)
{
	BuildModelTransform();
}

TransformComponent * TransformComponent::Clone(GameObject & parent)
{
	return new TransformComponent(*this, parent);
}

#pragma region Translation
Vector2D TransformComponent::GetPosition() const
{ 
	return m_position; 
}

void TransformComponent::SetPosition(Vector2D pos)
{
	m_position = pos; 
}

void TransformComponent::Move(Vector2D amount)
{
	m_position += amount;
}
#pragma endregion

#pragma region Rotate
void TransformComponent::WrapAngle()
{
	if (m_angle > 180.0f) {
		float over = fmod(m_angle + 180.0f, 360.0f);
		m_angle = over - 180.0f;
	}
	else if (m_angle < -180.0f) {
		float over = fmod(fabs(m_angle) + 180.0f, 360.0f);
		m_angle = 180.0f - over;
	}
}

float TransformComponent::GetAngle() const
{
	return m_angle;
}

void TransformComponent::SetAngle(float angle) 
{
	m_angle = angle;
	WrapAngle();
}

void TransformComponent::Rotate(float amount)
{
	m_angle += amount;
	WrapAngle();
}
#pragma endregion

#pragma region Scale
float TransformComponent::GetScaleX() const
{
	return m_scaleX;
}

void TransformComponent::SetScaleX(float scaleX) 
{
	m_scaleX = scaleX; 
}

void TransformComponent::ScaleX(float amount)
{
	m_scaleX += amount;
}

float TransformComponent::GetScaleY() const 
{
	return m_scaleY;
}

void TransformComponent::SetScaleY(float scaleY) 
{
	m_scaleY = scaleY; 
}

void TransformComponent::ScaleY(float amount)
{
	m_scaleY += amount;
}

float TransformComponent::GetScaleZ() const
{
	return m_scaleZ;
}

void TransformComponent::SetScaleZ(float scaleZ)
{
	m_scaleZ = scaleZ;
}

void TransformComponent::ScaleZ(float amount)
{
	m_scaleZ += amount;
}

void TransformComponent::SetScaleUniform(float amount)
{
	m_scaleX = m_scaleY = m_scaleZ = amount;
}

void TransformComponent::SetScale(float scaleX, float scaleY)
{
	m_scaleX = scaleX;
	m_scaleY = scaleY;
}

void TransformComponent::SetScale(float scaleX, float scaleY, float scaleZ)
{
	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_scaleZ = scaleZ;
}

void TransformComponent::ScaleUniform(float amount)
{
	m_scaleX += amount;
	m_scaleY += amount;
	m_scaleZ += amount;
}
#pragma endregion

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