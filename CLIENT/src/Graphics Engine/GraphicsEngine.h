#pragma once

#include "../../../SHARED/Singleton.h"
#include "../../../SHARED/Time/Time.h"

#include "Swap Chain/SwapChain.h"
#include "Device Context/DeviceContext.h"
#include "DrawArgs.h"
#include "../Window/Window.h"
#include "Shader.h"

#include <d3d11.h>
#include <memory>
#include <iostream>

#include "Buffers/Vertex Buffer/VertexBuffer.h"
#include "Buffers/Index Buffer/IndexBuffer.h"
#include "Buffers/Constant Buffer/ConstantBuffer.h"

using namespace Engine;

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
		DeviceContext device_context;

	public:
		static bool Initialize(Window* window);
		static void Present(bool vsync);
		static void Clear(Math::Color color = Math::Color::WHITE);
		static void Release();
		static void Draw(DrawArgs draw_args);

	public:
		inline static ID3D11Device* GetD3DDevice() {return get().d3d_device; }
		inline static ID3D11DeviceContext* GetDeviceContext() {return get().device_context.GetDeviceContext();}

	public:
		static Shader<ID3D11VertexShader>* CompileVertexShader(std::string filename);
		static Shader<ID3D11PixelShader>* CompilePixelShader(std::string filename);
		static VertexBuffer* CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, ID3DBlob* blob);
		static IndexBuffer* CreateIndexBuffer(void* list_incides, UINT size_list);
		static ConstantBuffer* CreateConstantBuffer(void* buffer, UINT size_buffer);

	public:
		inline static void DebugDrawTriangle() {
			struct V { float x, y, z; float u, v; float nx, ny, nz; };
			V tri[3] = {
				{ -0.5f, -0.5f, 0.5f, 0,0, 0,0,1 },
				{  0.0f,  0.5f, 0.5f, 0,0, 0,0,1 },
				{  0.5f, -0.5f, 0.5f, 0,0, 0,0,1 },
			};

			// create and bind a dynamic vertex buffer, very small
			D3D11_BUFFER_DESC bd{};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(tri);
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			D3D11_SUBRESOURCE_DATA sd{ tri, 0, 0 };
			ID3D11Buffer* vb = nullptr;
			get().d3d_device->CreateBuffer(&bd, &sd, &vb);

			UINT stride = sizeof(V), offset = 0;
			get().device_context.GetDeviceContext()->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
			get().device_context.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// use the same input layout & shaders you use for mesh (or use test shaders)
			get().device_context.GetDeviceContext()->Draw(3, 0);

			if (vb) { vb->Release(); }

			std::cout << "Draw" <<std::endl;
		}
};
