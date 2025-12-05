#pragma once
#include "vector"
#include "../../../SHARED/Singleton.h"
#include "../../../SHARED/IMediator.h"

#include <Windows.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "Imgui Component/FPSDisplay.h"
#include "Imgui Component/SceneMiniWindow.h"

class ImguiHandler : public Singleton<ImguiHandler>, IMediator<ImguiComponent> 
{
	public:
		static std::vector<ImguiComponent*> imgui_components;

	public:
		static void Initialize(HWND hwnd, ID3D11Device* d3d_device, ID3D11DeviceContext* device_context, ID3D11ShaderResourceView* textureRef);
		static void Release();
		static void Update();
		static void Render();

		virtual void Notify(ImguiComponent* notifier, std::string notification) override;
		virtual ImguiComponent* Get(std::string name) override;
};