#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(Component(ComponentType::Camera))
{
	_width = static_cast<float>(g_gameDesc.width);
	_height = static_cast<float>(g_gameDesc.height);
}

Camera::~Camera()
{
}

void Camera::UpdateMatrix()
{
	Vec3 eye = GetTransform()->GetPosition();
	Vec3 look = eye + GetTransform()->GetLookVector();
	Vec3 up = GetTransform()->GetUpVector();

	S_MatView = ::XMMatrixLookAtLH(eye, look, up);

	switch (_type)
	{
	case ProjectionType::Perspective:
	{
		S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, (_width / _height), _near, _far);
	}break;
	case ProjectionType::Orthographic:
	{
		S_MatProjection = ::XMMatrixOrthographicLH(8, 6, 0.f, 1.f);
	}break;
	}
}

void Camera::Update()
{
	UpdateMatrix();
}
