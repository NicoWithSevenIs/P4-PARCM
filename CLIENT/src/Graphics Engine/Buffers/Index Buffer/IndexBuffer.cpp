#include "IndexBuffer.h"

void IndexBuffer::Load(void* list_incides, UINT size_list, ID3D11Device* d3d_device) {
	if (buffer) buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * size_list;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_incides;

	this->size_list = size_list;

	HRESULT hr = d3d_device->CreateBuffer(&buff_desc, &init_data, &this->buffer);

	if (FAILED(hr)) 
	{
		std::cout << "[ERROR] Failed to create Index Buffer." << std::endl;
	}

}