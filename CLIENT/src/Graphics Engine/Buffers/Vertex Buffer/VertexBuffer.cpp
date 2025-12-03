#include "VertexBuffer.h"

void VertexBuffer::Load(void* list_vertices, UINT size_vertex, UINT size_list, ID3DBlob* blob, ID3D11Device* d3d_device) 
{
	if (buffer)
		buffer->Release();
	if (layout)
		layout->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->size_vertex = size_vertex;
	this->size_list = size_list;

	HRESULT hr = d3d_device->CreateBuffer(&buff_desc, &init_data, &buffer);

	if (FAILED(hr))
	{
		std::cout << "[ERROR] Failed to create Vertex Buffer." << std::endl;
		return;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT size_layout = ARRAYSIZE(layout);
	hr = d3d_device->CreateInputLayout(layout, size_layout, blob->GetBufferPointer(), blob->GetBufferSize(), &this->layout);

	if (FAILED(hr))
	{
		std::cout << "[ERROR] Failed to create Vertex Buffer Input Layout." << std::endl;
	}

}
