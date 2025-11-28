#include "DeviceContext.h"
#include "DeviceContext.h"

void DeviceContext::Initialize(ID3D11DeviceContext* device_context)
{
	this->device_context = device_context;
}

void DeviceContext::clearRenderTargetColor(ID3D11RenderTargetView** rtv, ID3D11DepthStencilView** dsv, Math::Color color)
{
	device_context->ClearRenderTargetView(*rtv, color.Scalar().data());
	device_context->ClearDepthStencilView(*dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	device_context->OMSetRenderTargets(1, rtv, *dsv);
}

void DeviceContext::Release() {
	device_context->Release();
}