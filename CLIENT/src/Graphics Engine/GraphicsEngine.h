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

#include "Texture/Texture.h"

using namespace Engine;

class GraphicsEngine final: public Singleton<GraphicsEngine> 
{
	private:
		Math::Vector2u window_size;

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
		Texture* texture;

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
        static void DebugDrawTriangle();
        
};
