#include "SwapChain.h"
#include <iostream>
bool SwapChain::Initialize
(
	ID3D11Device* device,
	IDXGIFactory* factory,
	HWND hwnd, UINT width, UINT height)
{


	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = factory->CreateSwapChain(device, &desc, &swap_chain);

	if (FAILED(hr)) 
	{
		return false;
	}

	ID3D11Texture2D* buffer = NULL;
	hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	
	if (FAILED(hr)) 
	{
		return false;
	}

	device->CreateRenderTargetView(buffer, NULL, &rtv);
	buffer->Release();
	
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texDesc.MipLevels = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.CPUAccessFlags = 0;
	
	hr = device->CreateTexture2D(&texDesc, NULL, &buffer);

	if (FAILED(hr)) {
		std::cout << "CreateTexture2D failed! HRESULT = 0x"
			<< std::hex << hr << std::endl;
		return false;
	}

	HRESULT depthStencilResult = device->CreateDepthStencilView(buffer, NULL, &dsv);
	buffer->Release();

	return true;
}

void SwapChain::Release()
{
	this->swap_chain->Release();
	this->dsv->Release();
	this->rtv->Release();
}

void SwapChain::Present(bool vsync)
{
	this->swap_chain->Present(vsync, NULL);
}
