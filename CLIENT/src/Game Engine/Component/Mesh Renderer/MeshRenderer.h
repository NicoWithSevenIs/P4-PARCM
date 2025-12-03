#pragma once

#include "../Component.h"


#include "../../../tiny_obj_loader.h"

#include "../../../Graphics Engine/DrawArgs.h"
#include "../../../Graphics Engine/GraphicsEngine.h"
#include "../../Camera/Camera.h"
#include "../../../../../SHARED/Time/Time.h"

#include "../Transform/TransformComponent.h"

#include <string>

using namespace Engine;

class MeshRenderer final: public Component {

	private:
		DrawArgs draw_args;
		Constant constant;

	private:
		std::vector<Vertex> list_vertices;
		std::vector<unsigned int> list_indices;

	public:
		MeshRenderer();
		
	public:
		void Initialize(std::string obj_path, std::string vs_path = "", std::string ps_path = "");
		void Update() override;
};	