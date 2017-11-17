#include "CameraComponent.h"
#include "JsonReader.h"
#include "WindowManager.h"
#include "TransformComponent.h"

#include "GameObjectManager.h"
#include "GameObject.h"

CameraComponent::CameraComponent(GameObject & parent) :
	Component(parent, COMPONENT_TYPE::CAMERA, true)
{}

CameraComponent::CameraComponent(GameObject & parent, float fov, unsigned short camType) :
	Component(parent, COMPONENT_TYPE::CAMERA, true),
	m_fov(fov), m_cameraType(camType)
{}

CameraComponent::CameraComponent(const CameraComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::CAMERA, true),
	m_fov(rhs.m_fov), m_cameraType(rhs.m_cameraType)
{}

CameraComponent::~CameraComponent()
{
	GameObjectManager::GetInstance().RemoveCamera(this);
}

Matrix4x4 CameraComponent::MatrixFromCameraVectors(const Vector3D & right, const Vector3D & up, const Vector3D & forward)
{
	return Matrix4x4(
		right.getX(), right.getY(), right.getZ(), 0.0f,
		up.getX(), up.getY(), up.getZ(), 0.0f,
		-forward.getX(), -forward.getY(), -forward.getZ(), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void CameraComponent::CalcViewMatrix()
{
	TransformComponent* tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));

	Matrix4x4 rotationM = MatrixFromCameraVectors(tComp->Right(), tComp->Up(), tComp->Forward());

	m_viewMatrix = rotationM * Matrix4x4::Translate(-1 * tComp->GetPosition());
}

void CameraComponent::CalcPerspectiveMatrix()
{
	m_perspectiveMatrix = Matrix4x4::Perspective(m_fov, m_aspectRatio, 1.f);
}

void CameraComponent::CalcOrthographicMatrix()
{
	m_orthographicMatrix = Matrix4x4::Orthographic(m_screenWidth, m_screenHeight, 0.1f);
}

void CameraComponent::Update(double deltaTime)
{
	WindowManager& winMngr = WindowManager::GetInstance();
	m_aspectRatio = winMngr.GetAspectRatio();
	m_screenWidth = winMngr.WindowWidth();
	m_screenHeight = winMngr.WindowHeight();
	CalcViewMatrix();
	switch (m_cameraType) {
	case CAM_BOTH:
		CalcPerspectiveMatrix();
		CalcOrthographicMatrix();
		break;
	case CAM_PERSP:
		CalcPerspectiveMatrix();
		break;
	case CAM_ORTHO:
		CalcOrthographicMatrix();
		break;
	}
}

CameraComponent * CameraComponent::Clone(GameObject & parent)
{
	CameraComponent* cComp = new CameraComponent(*this, parent);
	cComp->RegisterWithManager();
	cComp->SubscribeToEvents(this->m_eventsToSubscribeTo);
	return cComp;
}

Component * CameraComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	float fov = AcryJson::ValueExists(j, "camera", "fov") ? AcryJson::ParseFloat(j, "camera", "fov") : 80.f;
	unsigned short type = CAM_PERSP;
	if (AcryJson::ValueExists(j, "camera", "type")) {
		String typeString = AcryJson::ParseString(j, "camera", "type");
		if (typeString.compare("persp") == 0)
			type = CAM_PERSP;
		else if (typeString.compare("ortho") == 0)
			type = CAM_ORTHO;
		else if (typeString.compare("both") == 0)
			type = CAM_BOTH;
	}
	return new CameraComponent(gObject, fov, type);
}

void CameraComponent::Override(nlohmann::json j)
{
	m_fov = AcryJson::ValueExists(j, "camera", "fov") ? AcryJson::ParseFloat(j, "camera", "fov") : m_fov;
	if (AcryJson::ValueExists(j, "camera", "type")) {
		String typeString = AcryJson::ParseString(j, "camera", "type");
		if (typeString.compare("persp"))
			m_cameraType = CAM_PERSP;
		else if (typeString.compare("ortho"))
			m_cameraType = CAM_ORTHO;
		else if (typeString.compare("both"))
			m_cameraType = CAM_BOTH;
	}
}

void CameraComponent::RegisterWithManager()
{
	GameObjectManager::GetInstance().RegisterCamera(this);
}

float CameraComponent::GetFOV() const
{
	return m_fov;
}

float CameraComponent::GetAspect() const
{
	return m_aspectRatio;
}

Matrix4x4 CameraComponent::GetViewMatrix() const
{
	return m_viewMatrix;
}

Matrix4x4 CameraComponent::GetPerspectiveMatrix() const
{
	return m_perspectiveMatrix;
}

Matrix4x4 CameraComponent::GetOrthographicMatrix() const
{
	return m_orthographicMatrix;
}
