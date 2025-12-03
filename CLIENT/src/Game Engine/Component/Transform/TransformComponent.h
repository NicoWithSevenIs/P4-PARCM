#pragma once

#include "../Component.h"
#include "../../../../../SHARED/Transform.h"
#include "../../../../../SHARED/Math.h"

class TransformComponent : public Engine::Component, public Engine::Transform {
	
	public:
		Math::Matrix transform_matrix;

	public:
		TransformComponent();
		TransformComponent(Engine::Transform data);
		void Update() override;
		void BuildTransform();
};