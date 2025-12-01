#pragma once
#include "Shader.h"
namespace Engine {
	struct DrawArgs {
		Shader<ID3D11VertexShader> vertex_shader;
		Shader<ID3D11PixelShader> pixel_shader;
	};
}