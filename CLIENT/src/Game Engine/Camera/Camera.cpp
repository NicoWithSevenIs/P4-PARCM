#include "Camera.h"

Camera::Camera(Engine::GameObjectData data, float viewport_width, float viewport_height):
	viewport_width(viewport_width), viewport_height(viewport_height), Engine::GameObject(data)
{}

Matrix Camera::GetViewMatrix()
{
	auto transform = (TransformComponent*) Get("TRANSFORM");
	transform->BuildTransform();
	Matrix t = transform->transform_matrix;	
	t.Inverse();
	return t;
}

Matrix Camera::GetProjectionMatrix()
{
/*
	float left = -10.0f;
	float right = 10.0f;
	float top = 10.0f;
	float bottom = -10.0f;
	float nearZ = 0.1f;
	float farZ = 100.0f;

	Math::Matrix ortho = Math::Matrix::OrthographicProjection(right - left, top - bottom, nearZ, farZ);
	return ortho;
	*/
	return Matrix::PerspectiveProjection(1.57f, viewport_width / viewport_height, 0.1f, 100.f);
}
