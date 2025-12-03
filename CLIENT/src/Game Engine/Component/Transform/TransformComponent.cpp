#include "TransformComponent.h"

TransformComponent::TransformComponent(): 
	Component("TRANSFORM", Engine::ComponentType::SCRIPT), 
	Transform()
{}

TransformComponent::TransformComponent(Engine::Transform data):
	Component("TRANSFORM", Engine::ComponentType::SCRIPT),
	Transform(data)
{}

void TransformComponent::BuildTransform()
{
	this->transform_matrix = 
		Math::Matrix::Scale(scale) *
		Math::Matrix::Rotation(rotation)* 
		Math::Matrix::Translation(position);
}

void TransformComponent::Update()
{
	TransformComponent::BuildTransform();
}