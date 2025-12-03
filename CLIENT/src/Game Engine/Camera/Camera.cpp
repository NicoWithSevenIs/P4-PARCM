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
	return Matrix::PerspectiveProjection(1.57f, viewport_width / viewport_height, 0.1f, 100.f);
}
