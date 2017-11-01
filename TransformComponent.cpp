#include "TransformComponent.h"
#include "GameObjectFactory.h"
#include "JsonReader.h"
#include <cmath>

TransformComponent::TransformComponent(GameObject & parent) :
	Component(parent, CT_TRANSFORM),
	m_position(Vector3D(0.f, 0.f, 0.f)),
	m_angleX(0.f), m_angleY(0.f), m_angleZ(0.f),
	m_scaleX(0.f), m_scaleY(0.f), m_scaleZ(0.f)
{}

TransformComponent::TransformComponent(GameObject& parent, Vector3D position) :
	Component(parent, CT_TRANSFORM),
	m_position(position),
	m_angleX(0.f), m_angleY(0.f), m_angleZ(0.f),
	m_scaleX(1.f), m_scaleY(1.f), m_scaleZ(0.f)
{}

/*!
Default interpretation of the TransformComponent is a 2D component, only the Z rotation and X-Y scales are taken into account.
*/
TransformComponent::TransformComponent(GameObject& parent, Vector3D position, float angleZ, float scaleX, float scaleY) :
	Component(parent, CT_TRANSFORM),
	m_position(position),
	m_angleX(0.f), m_angleY(0.f), m_angleZ(angleZ),
	m_scaleX(scaleX), m_scaleY(scaleY), m_scaleZ(0.f)
{}

TransformComponent::TransformComponent(GameObject & parent, Vector3D position, float angleX, float angleY, float angleZ, float scaleX, float scaleY, float scaleZ) :
	Component(parent, CT_TRANSFORM),
	m_position(position),
	m_angleX(angleX), m_angleY(angleY), m_angleZ(angleZ),
	m_scaleX(scaleX), m_scaleY(scaleY), m_scaleZ(scaleZ)
{}

TransformComponent::TransformComponent(const TransformComponent & rhs, GameObject& parent) :
	Component(m_parent, CT_TRANSFORM),
	m_position(rhs.m_position),
	m_angleX(rhs.m_angleX), m_angleY(rhs.m_angleY), m_angleZ(rhs.m_angleZ),
	m_scaleX(rhs.m_scaleX), m_scaleY(rhs.m_scaleY), m_scaleZ(rhs.m_scaleZ)
{}

TransformComponent & TransformComponent::operator=(const TransformComponent& rhs)
{
	m_position = rhs.m_position;
	m_angleX = rhs.m_angleX;
	m_angleY = rhs.m_angleY;
	m_angleZ = rhs.m_angleZ;
	m_scaleX = rhs.m_scaleX;
	m_scaleY = rhs.m_scaleY;
	m_scaleZ = rhs.m_scaleZ;
	return *this;
}

TransformComponent::~TransformComponent(){}

void TransformComponent::Update(double deltaTime)
{
	BuildModelTransform();
}

TransformComponent * TransformComponent::Clone(GameObject & parent)
{
	return new TransformComponent(*this, parent);
}

Component * TransformComponent::Serialize(GameObject& gObject, nlohmann::json j)
{
	TransformComponent * tComp = new TransformComponent(gObject);
	float x = AcryJson::ParseFloat(j, "transform", "position", "x");
	float y = AcryJson::ParseFloat(j, "transform", "position", "y");
	float z = AcryJson::ParseFloat(j, "transform", "position", "y");
	tComp->SetPosition(Vector3D(x, y, z));

	float rX = AcryJson::ParseFloat(j, "transform", "angle", "xRot");
	float rY = AcryJson::ParseFloat(j, "transform", "angle", "yRot");
	float rZ = AcryJson::ParseFloat(j, "transform", "angle", "zRot");
	tComp->SetAngles(rX, rY, rZ);

	float sX = AcryJson::ParseFloat(j, "transform", "scale", "x");
	float sY = AcryJson::ParseFloat(j, "transform", "scale", "y");
	float sZ = AcryJson::ParseFloat(j, "transform", "scale", "z");
	tComp->SetScale(sX, sY);

	return tComp;
}

void TransformComponent::Override(nlohmann::json j)
{
	Vector3D pos = GetPosition();
	m_position.Set(
		AcryJson::ValueExists(j, "transform", "position", "x") ? AcryJson::ParseFloat(j, "transform", "position", "x") : pos.getX(),
		AcryJson::ValueExists(j, "transform", "position", "y") ? AcryJson::ParseFloat(j, "transform", "position", "y") : pos.getY(),
		AcryJson::ValueExists(j, "transform", "position", "z") ? AcryJson::ParseFloat(j, "transform", "position", "z") : pos.getZ()
	);

	SetAngles(
		AcryJson::ValueExists(j, "transform", "angle", "xRot") ? AcryJson::ParseFloat(j, "transform", "angle", "xRot") : m_angleX,
		AcryJson::ValueExists(j, "transform", "angle", "yRot") ? AcryJson::ParseFloat(j, "transform", "angle", "yRot") : m_angleY,
		AcryJson::ValueExists(j, "transform", "angle", "zRot") ? AcryJson::ParseFloat(j, "transform", "angle", "zRot") : m_angleZ
	);

	SetScale(
		AcryJson::ValueExists(j, "transform", "scale", "x") ? AcryJson::ParseFloat(j, "transform", "scale", "x") : m_scaleX,
		AcryJson::ValueExists(j, "transform", "scale", "y") ? AcryJson::ParseFloat(j, "transform", "scale", "y") : m_scaleY,
		AcryJson::ValueExists(j, "transform", "scale", "z") ? AcryJson::ParseFloat(j, "transform", "scale", "z") : m_scaleZ
	);
}

#pragma region Translation
Vector3D TransformComponent::GetPosition() const
{ 
	return m_position; 
}

void TransformComponent::SetPosition(Vector3D pos)
{
	m_position = pos; 
}

void TransformComponent::Move(Vector3D amount)
{
	m_position += amount;
}
#pragma endregion

#pragma region Rotate
void TransformComponent::WrapAngle(float & angle)
{
	if (angle > 180.0f) {
		float over = fmod(angle + 180.0f, 360.0f);
		angle = over - 180.0f;
	}
	else if (angle < -180.0f) {
		float over = fmod(fabs(angle) + 180.0f, 360.0f);
		angle = 180.0f - over;
	}
}

void TransformComponent::SetAngles(float angleX, float angleY, float angleZ)
{
	m_angleX = angleX;
	WrapAngle(m_angleX);

	m_angleY = angleY;
	WrapAngle(m_angleY);

	m_angleZ = angleZ;
	WrapAngle(m_angleZ);
}

void TransformComponent::SetAngleX(float angle)
{
	m_angleX = angle;
	WrapAngle(m_angleX);
}

void TransformComponent::SetAngleY(float angle)
{
	m_angleY = angle;
	WrapAngle(m_angleY);
}

void TransformComponent::SetAngleZ(float angle)
{
	m_angleZ = angle;
	WrapAngle(m_angleZ);
}

void TransformComponent::RotateX(float amount)
{
	m_angleX += amount;
	WrapAngle(m_angleX);
}

void TransformComponent::RotateY(float amount)
{
	m_angleY += amount;
	WrapAngle(m_angleY);
}

void TransformComponent::RotateZ(float amount)
{
	m_angleZ += amount;
	WrapAngle(m_angleZ);
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
		rot = Matrix4x4::Rotate(m_angleX, Vector3D(1,0,0,0)) * Matrix4x4::Rotate(m_angleY, Vector3D(0, 1, 0, 0)) * Matrix4x4::Rotate(m_angleZ, Vector3D(0, 0, 1, 0)),
		scale = Matrix4x4::Scale(m_scaleX, m_scaleY, m_scaleZ);

	m_transform = trans * rot * scale;
}

