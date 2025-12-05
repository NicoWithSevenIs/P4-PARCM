#pragma once
#include "../Buffer.h""
#include "../../../../../SHARED/Math.h"

__declspec(align(16))
struct Constant
{
	public:
		Math::Matrix transform_matrix;
		Math::Matrix view_matrix;
		Math::Matrix projection_matrix;
		Math::Vector3f color;
		float deltaTime;
};


class ConstantBuffer : public Buffer {
	public:
		void Load(void* buffer, UINT size_buffer, ID3D11Device* d3d_device);
		void Update(ID3D11DeviceContext* device_context, void* buffer);
};
