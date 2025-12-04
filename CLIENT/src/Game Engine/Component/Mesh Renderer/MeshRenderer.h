#pragma once

#include "../Component.h"


#include "../../../tiny_obj_loader.h"

#include "../../../Graphics Engine/DrawArgs.h"
#include "../../../Graphics Engine/GraphicsEngine.h"
#include "../../Camera/Camera.h"
#include "../../../../../SHARED/Time/Time.h"

#include "../Transform/TransformComponent.h"

#include <string>
#include <sstream>

using namespace Engine;

class MeshRenderer final: public Component 
{
	private:
		tinyobj::attrib_t attribs;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

	private:
		DrawArgs draw_args;
		Constant constant;

	private:
		std::vector<Vector3f> list_vertices;

	public:
		MeshRenderer();
		
	private:
		void ConfigurePipeline();
		void ConfigureVertices();

	public:
		void InitializeFromFile(std::string obj_path);
		void InitializeFromString(std::stringstream obj_str);
		void Update() override;


};	