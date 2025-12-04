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


	get().window_size = window->GetWindowSize();
	get().swap_chain.Initialize(get().d3d_device, get().dxgi_factory, window->GetHWND(), get().window_size.x, get().window_size.y);

	return true;
}

void GraphicsEngine::Present(bool vsync) 
{
	get().swap_chain.Present(vsync);
}

void GraphicsEngine::Clear(Math::Color color) 
{
	get().device_context.clearRenderTargetColor(
		get().swap_chain.GetRenderTargetView(), 
		get().swap_chain.GetDepthTargetView(),
		color
	);

	D3D11_VIEWPORT vp = {};
	vp.Width = get().window_size.x;
	vp.Height = get().window_size.y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	get().device_context.GetDeviceContext()->RSSetViewports(1, &vp);
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

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->Draw(args.vertex_buffer->GetListSize(), 0);

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

void GraphicsEngine::DebugDrawTriangle()
{
	
	struct Vertex { float x, y, z; };
	Vertex tri[3] = {
		{-0.5f, -0.5f, 0.0f},
		{ 0.0f,  0.5f, 0.0f},
		{ 0.5f, -0.5f, 0.0f},
	};

	// --- Vertex Buffer ---
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(tri);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd{ tri, 0, 0 };
	ID3D11Buffer* vb = nullptr;
	get().d3d_device->CreateBuffer(&bd, &sd, &vb);

	// --- Simple HLSL Shaders (compiled elsewhere or embedded) ---
	Shader<ID3D11VertexShader>* v =	 CompileVertexShader("SAMPLE_VERTEX.hlsl");
	Shader<ID3D11PixelShader>* p =	 CompilePixelShader("SAMPLE_PIXEL.hlsl");
	ID3D11VertexShader* vs = v->GetShader();
	ID3D11PixelShader* ps = p->GetShader();

	// --- Input Layout ---
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	ID3D11InputLayout* inputLayout = nullptr;
	get().d3d_device->CreateInputLayout(layout, 1, v->GetBlob()->GetBufferPointer(), v->GetBlob()->GetBufferSize(), &inputLayout);

	// --- Bind pipeline ---
	UINT stride = sizeof(Vertex), offset = 0;
	auto ctx = get().device_context.GetDeviceContext();
	ctx->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
	ctx->IASetInputLayout(inputLayout);
	ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ctx->VSSetShader(vs, nullptr, 0);
	ctx->PSSetShader(ps, nullptr, 0);

	// --- Draw ---
	ctx->Draw(3, 0);

	// --- Cleanup ---
	if (vb) vb->Release();
	if (inputLayout) inputLayout->Release();
	if (vs) vs->Release();
	if (ps) ps->Release();
	
}
