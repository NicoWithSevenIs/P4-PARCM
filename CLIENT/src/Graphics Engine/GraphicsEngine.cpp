#include "GraphicsEngine.h"

bool GraphicsEngine::Initialize(Window* window)
{

	D3D_DRIVER_TYPE driver_types[] = {
	D3D_DRIVER_TYPE_HARDWARE,
	D3D_DRIVER_TYPE_WARP,
	D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);
	ID3D11DeviceContext* imm_context;

	HRESULT res = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;) {
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &get().d3d_device, &get().feature_level, &imm_context);

		if (SUCCEEDED(res))
			break;

		++driver_type_index;
	}

	if (FAILED(res)) {
		return false;
	}

	get().device_context.Initialize(imm_context);

	get().d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&get().dxgi_device);
	get().dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&get().dxgi_adapter);
	get().dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&get().dxgi_factory);


	Math::Vector2u dim = window->GetWindowSize();
	get().swap_chain.Initialize(get().d3d_device, get().dxgi_factory, window->GetHWND(), dim.x, dim.y);

	return true;
}

void GraphicsEngine::Present(bool vsync) {
	get().swap_chain.Present(vsync);
}

void GraphicsEngine::Clear(Math::Color color) {
	get().device_context.clearRenderTargetColor(
		get().swap_chain.GetRenderTargetView(), 
		get().swap_chain.GetDepthTargetView(),
		color
	);
}

void GraphicsEngine::Release() {
	get().swap_chain.Release();
	get().device_context.Release();
	get().dxgi_device->Release();
	get().dxgi_adapter->Release();
	get().dxgi_factory->Release();
	get().d3d_device->Release();
}

void GraphicsEngine::Draw(DrawArgs args)
{
	UINT stride = args.vertex_buffer->GetVertexSize();
	UINT offset = 0;
	ID3D11DeviceContext* context = get().device_context.GetDeviceContext();

	ID3D11Buffer* c_buff = args.constant_buffer->GetBuffer();
	context->VSSetConstantBuffers(0, 1, &c_buff);
	context->PSSetConstantBuffers(0, 1, &c_buff);

	context->VSSetShader(args.vertex_shader->GetShader(), nullptr, 0);
	context->PSSetShader(args.pixel_shader->GetShader(), nullptr, 0);

	ID3D11Buffer* v_buff = args.vertex_buffer->GetBuffer();
	context->IASetVertexBuffers(0, 1, &v_buff, &stride, &offset);
	context->IASetInputLayout(args.vertex_buffer->GetLayout());

	context->IASetIndexBuffer(args.index_buffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);

	
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->DrawIndexed(args.index_buffer->GetIndexListSize(), 0, 0);

	
}


Shader<ID3D11VertexShader>* GraphicsEngine::CompileVertexShader(std::string filename) 
{
	auto shader = new Shader<ID3D11VertexShader>();
	shader->Initialize(filename, get().d3d_device);
	return shader;
}

Shader<ID3D11PixelShader>* GraphicsEngine::CompilePixelShader(std::string filename)
{
	auto shader = new Shader<ID3D11PixelShader>();
	shader->Initialize(filename, get().d3d_device);
	return shader;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, ID3DBlob* blob)
{
	auto v_buffer = new VertexBuffer();
	v_buffer->Load(list_vertices, size_vertex, size_list, blob, get().d3d_device);
	return v_buffer;
}

IndexBuffer* GraphicsEngine::CreateIndexBuffer(void* list_incides, UINT size_list)
{
	auto i_buffer = new IndexBuffer();
	i_buffer->Load(list_incides, size_list, get().d3d_device);
	return i_buffer;
}

ConstantBuffer* GraphicsEngine::CreateConstantBuffer(void* buffer, UINT size_buffer)
{
	auto c_buffer = new ConstantBuffer();
	c_buffer->Load(buffer, size_buffer, get().d3d_device);
	return c_buffer;
}
