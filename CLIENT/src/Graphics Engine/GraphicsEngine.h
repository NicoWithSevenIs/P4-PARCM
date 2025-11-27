#pragma once

#include "../../../Library/Singleton.h"
#include "Swap Chain/SwapChain.h"

#include "../Window/Window.h"

#include <d3d11.h>
#include <memory>

class GraphicsEngine final: public Singleton<GraphicsEngine> 
{
	private:	
		ID3D11Device* d3d_device;
		D3D_FEATURE_LEVEL feature_level;

	private:
		IDXGIDevice* dxgi_device;
		IDXGIAdapter* dxgi_adapter;
		IDXGIFactory* dxgi_factory;

	private:
		SwapChain swap_chain;

	public:
		static bool Initialize(Window* window);
		static void Present(bool vsync);
};