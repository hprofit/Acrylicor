#include "Camera.h"
#include "WindowManager.h"

Camera::Camera() : 
	m_position(Vector3D(0, 0, 0, 1)), 
	m_lookat(Vector3D(0, 0, -1, 0)),
	m_xRot(0.0f), m_yRot(0.0f), m_fov(80.0f),
	m_cameraType(CAM_BOTH) { }

Camera::Camera(Vector3D pos, Vector3D lookat, unsigned short camType) :
	m_position(pos),
	m_lookat(lookat),
	m_xRot(0.0f), m_yRot(0.0f), m_fov(80.0f),
	m_cameraType(camType) { }

Camera::Camera(Vector3D pos, Vector3D lookat, float xRot, float yRot, unsigned short camType) :
	m_position(pos),
	m_lookat(lookat),
	m_xRot(xRot), m_yRot(yRot), m_fov(80.0f),
	m_cameraType(camType) { }

Camera::Camera(Vector3D pos, Vector3D lookat, float xRot, float yRot, float fov, unsigned short camType) :
	m_position(pos),
	m_lookat(lookat),
	m_xRot(xRot), m_yRot(yRot), m_fov(fov),
	m_cameraType(camType) { }

Camera::Camera(Camera const & rhs) :
	m_position(rhs.m_position),
	m_lookat(rhs.m_lookat),
	m_xRot(rhs.m_xRot), m_yRot(rhs.m_yRot), m_fov(rhs.m_fov) { }

Camera & Camera::operator=(Camera rhs)
{
	m_position = rhs.m_position;
	m_lookat = rhs.m_lookat;
	m_xRot = rhs.m_xRot;
	m_yRot = rhs.m_yRot;
	m_fov = rhs.m_fov;
	return *this;
}

Camera::~Camera()
{
}

Matrix4x4 Camera::MatrixFromCameraVectors(const Vector3D & right, const Vector3D & up, const Vector3D & forward)
{
	return Matrix4x4(
		right.getX(), right.getY(), right.getZ(), 0.0f,
		up.getX(), up.getY(), up.getZ(), 0.0f,
		-forward.getX(), -forward.getY(), -forward.getZ(), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Vector3D Camera::GetCameraRight()
{
	Vector3D lCrossR = Vector3D::Cross(m_lookat, Vector3D(0, 1, 0, 0));
	float lenLCrossR = lCrossR.Length();
	return lenLCrossR != 0.0f ? lCrossR * (1.0f / lenLCrossR) : Vector3D(0, 0, 1, 0);
}

Vector3D Camera::GetCameraUp(const Vector3D & forward, const Vector3D & right)
{
	return Vector3D::Cross(forward * -1, right);
}

void Camera::CalcViewMatrix()
{
	Vector3D forward = Vector3D::Normalize(m_lookat);
	Vector3D right = GetCameraRight();
	Vector3D up = GetCameraUp(forward, right);

	Matrix4x4 rotationM = MatrixFromCameraVectors(right, up, forward);

	m_viewMatrix = rotationM * Matrix4x4::Translate(-1 * m_position);
}

void Camera::CalcPerspectiveMatrix()
{
	m_perspectiveMatrix = Matrix4x4::Perspective(m_fov, m_aspectRatio, 0.1f);
}

void Camera::CalcOrthographicMatrix()
{
	m_orthographicMatrix = Matrix4x4::Orthographic(m_fov, m_aspectRatio, 0.1f);
}

void Camera::Update()
{
	m_aspectRatio = WindowManager::GetInstance().GetAspectRatio();
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

void Camera::RotateCamera(float x, float y)
{
	Vector3D defaultLookat(0.0f, 0.0f, -1.0f, 0.0f);
	Vector3D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
	Vector3D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
	m_xRot -= x;
	m_yRot -= y;
	m_lookat = Matrix4x4::Rotate(m_xRot, yAxis) *  Matrix4x4::Rotate(m_yRot, xAxis) * defaultLookat;
}

Vector3D Camera::GetPosition() const 
{ 
	return m_position; 
}

Vector3D Camera::GetLookAt() const
{ 
	return m_lookat; 
}

float Camera::GetXRot() const
{ 
	return m_xRot; 
}

float Camera::GetYRot() const 
{ 
	return m_yRot; 
}

float Camera::GetFOV() const 
{ 
	return m_fov; 
}

float Camera::GetAspect() const
{ 
	return m_aspectRatio; 
}

Matrix4x4 Camera::GetViewMatrix() const
{ 
	return m_viewMatrix; 
}

Matrix4x4 Camera::GetPerspectiveMatrix() const
{
	return m_perspectiveMatrix;
}

Matrix4x4 Camera::GetOrthographicMatrix() const
{
	return m_orthographicMatrix;
}
