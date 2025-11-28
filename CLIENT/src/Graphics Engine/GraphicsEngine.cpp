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