#include "ConstantBuffer.h"

void ConstantBuffer::Load(void* c_buffer, UINT size_buffer, ID3D11Device* d3d_device)
{
	if (buffer) buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = c_buffer;

	HRESULT hr = d3d_device->CreateBuffer(&buff_desc, &init_data, &buffer);
	
	if (FAILED(hr)) 
	{
		std::cout << "[ERROR] Failed to create Constant Buffer." << std::endl;
	}
}

void ConstantBuffer::Update(ID3D11DeviceContext* device_context, void* buffer)
{
	device_context->UpdateSubresource(this->buffer, NULL, NULL, buffer, NULL, NULL);
}
