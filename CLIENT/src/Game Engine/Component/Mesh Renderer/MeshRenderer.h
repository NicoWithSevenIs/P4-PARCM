#pragma once

#include "../Component.h"
#include "../../../tiny_obj_loader.h"
#include "../../../Graphics Engine/DrawArgs.h"
#include "../../../Graphics Engine/GraphicsEngine.h"


#include <string>

using namespace Engine;

class MeshRenderer final: public Component {

	private:
		bool initialized;
		Shader<ID3D11VertexShader> vertex_shader;
		Shader<ID3D11PixelShader> pixel_shader;

	public:
		MeshRenderer();
		
	public:
		void Initialize(std::string obj_path, std::string vs_path = "", std::string ps_path = "");
		void Update() override;
};	