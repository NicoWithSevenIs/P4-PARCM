#pragma once

#include "../../../SHARED/Singleton.h"
#include <Windows.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


class ImguiHandler : public Singleton<ImguiHandler> {

	public:
		static void Initialize(HWND hwnd, ID3D11Device* d3d_device, ID3D11DeviceContext* device_context);
		static void Release();
		static void Update();
		static void Render();
};