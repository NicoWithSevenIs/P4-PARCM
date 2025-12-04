#include "Camera.h"
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

void Camera::Update()
{

	auto transform = (TransformComponent*)Get("TRANSFORM");

	auto cm = transform->transform_matrix;

	auto local_z_dir = Vector3f(cm[2][0], cm[2][1], cm[2][2]);
	auto local_x_dir = Vector3f(cm[0][0], cm[0][1], cm[0][2]);

	Vector3f forward = local_z_dir * Time::deltaTime() * this->forward;
	Vector3f right = local_x_dir * Time::deltaTime() * this->right;
	Vector3f up = Vector3f(0, Time::deltaTime() * this->up, 0);

	transform->position += forward + right + up;
	transform->rotation += Vector3f(x_rot, y_rot, 0);

	x_rot = 0;
	y_rot = 0;

}
