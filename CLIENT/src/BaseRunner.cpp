#include "BaseRunner.h"

BaseRunner::BaseRunner(): Window()
{
}

void BaseRunner::OnCreate()
{
	GraphicsEngine::Initialize(this);
	ImguiHandler::Initialize(hwnd,GraphicsEngine::GetD3DDevice(), GraphicsEngine::GetDeviceContext());
	//NetworkHandler::Initialize();
	//NetworkHandler::MessageServer();

	
	Engine::Transform cow(Math::Vector3f(0, 0,5), Math::Vector3f(0.3, 0.3,0.3), Math::Vector3f(0, 0, 0));
	GameObjectData data("1", "Cow (your mom)", cow, "asdasd");

	auto go = GameObjectManager::AddGameObject(data);
	auto mesh_renderer = new MeshRenderer();
	mesh_renderer->Initialize("cow.obj", "mesh_vertex.hlsl", "mesh_pixel.hlsl");

	go->AddComponent(mesh_renderer);

	Engine::Transform t(Math::Vector3f(0, 0, -2), Math::Vector3f(1, 1, 1), Math::Vector3f(0, 0, 0));
	GameObjectData camera_data("0", "Camera", t, "nil");

	auto size = GetWindowSize();

	Camera* c = new Camera(camera_data, size.x, size.y);
	GameObjectManager::AddGameObject(c);
	CameraManager::SetCurrentCamera(c);
}

void BaseRunner::OnUpdate()
{
	GraphicsEngine::Clear(Math::Color::NICO_BLUE);


	ImguiHandler::Update();
	Engine::GameObjectManager::Update();

	auto go = GameObjectManager::GetGameObject("1");
	auto tc = (TransformComponent*)go->Get("TRANSFORM");
	tc->rotation.y += Time::deltaTime();


	Engine::GameObjectManager::Draw();
	ImguiHandler::Render();


	//GraphicsEngine::DebugDrawTriangle();

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
