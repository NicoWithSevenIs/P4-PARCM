#pragma once
#include "Shader.h"
#include "Buffers/Vertex Buffer/VertexBuffer.h"
#include "Buffers/Index Buffer/IndexBuffer.h"
#include "Buffers/Constant Buffer/ConstantBuffer.h"

namespace Engine {
	class DrawArgs {
		public:
			Shader<ID3D11VertexShader>*	vertex_shader;
			Shader<ID3D11PixelShader>*	pixel_shader;
			VertexBuffer*				vertex_buffer;
			ConstantBuffer*				constant_buffer;
	};
}