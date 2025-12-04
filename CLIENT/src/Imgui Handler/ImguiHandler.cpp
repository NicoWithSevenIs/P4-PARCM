#include "ImguiHandler.h"
#include "../SHARED/Time/Time.h"

std::vector<ImguiComponent*> ImguiHandler::imgui_components;

void ImguiHandler::Initialize(HWND hwnd, ID3D11Device* d3d_device, ID3D11DeviceContext* device_context)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(d3d_device, device_context);
	
	UI_FPSDisplay* fpsDisplay = new UI_FPSDisplay();
	fpsDisplay->width = 150.0f; 
	fpsDisplay->height = 50.0f;
	imgui_components.push_back(fpsDisplay);
}

void ImguiHandler::Update()
{	

	//ImGui::ShowDemoWindow(); // Show demo window! :)
	for (int i = 0; i < imgui_components.size(); i++) {
		imgui_components[i]->Update(Time::deltaTime());
	}
}

void ImguiHandler::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	for (int i = 0; i < imgui_components.size(); i++) {
		imgui_components[i]->Render();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImguiHandler::Release()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}