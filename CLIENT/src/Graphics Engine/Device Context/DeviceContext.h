#pragma once
#include <d3d11.h>
#include "../../../../SHARED/Math.h"

class DeviceContext {
	private:
		ID3D11DeviceContext* device_context;
		

	public:
		void Initialize(ID3D11DeviceContext* device_context);
		void clearRenderTargetColor(ID3D11RenderTargetView** rtv, ID3D11DepthStencilView** dsv, Math::Color color);
		void Release();

	public:
		inline ID3D11DeviceContext* GetDeviceContext(){return this->device_context;}
};