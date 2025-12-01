#include "BaseRunner.h"

BaseRunner::BaseRunner(): Window()
{
}

void BaseRunner::OnCreate()
{
	GraphicsEngine::Initialize(this);
	ImguiHandler::Initialize(hwnd,GraphicsEngine::GetD3DDevice(), GraphicsEngine::GetDeviceContext());
	NetworkHandler::Initialize();
	NetworkHandler::MessageServer();
}

void BaseRunner::OnUpdate()
{
	GraphicsEngine::Clear(Math::Color::NICO_BLUE);
	ImguiHandler::Update();
	Engine::GameObjectManager::Update();
	Engine::GameObjectManager::Draw();
	ImguiHandler::Render();
	GraphicsEngine::Present(true);
}

void BaseRunner::OnDestroy()
{
	Engine::GameObjectManager::Release();
	ImguiHandler::Release();
	GraphicsEngine::Release();
}

void BaseRunner::OnFocus()
{
}

void BaseRunner::OnUnfocus()
{
}
