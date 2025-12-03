#pragma once

#include <d3d11.h>
#include <memory>

class SwapChain {
	private:
		IDXGISwapChain* swap_chain;
		ID3D11RenderTargetView* rtv;
		ID3D11DepthStencilView* dsv;

	public:
		SwapChain() = default;
		~SwapChain() = default;

	public:
		bool Initialize(ID3D11Device* device, IDXGIFactory* factory, HWND hwnd, UINT width, UINT height);
		void Present(bool vsync);
		void Release();

	public:
		inline IDXGISwapChain* GetSwapChain()
		{
			return swap_chain;
		}
	public:
		inline ID3D11RenderTargetView* GetRenderTargetView() 
		{
			return rtv;
		}
		inline ID3D11DepthStencilView* GetDepthTargetView() 
		{
			return dsv;
		}
};