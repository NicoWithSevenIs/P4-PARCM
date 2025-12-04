#include "BaseRunner.h"
#include <cmath>
BaseRunner::BaseRunner(): Window()
{
}
Scene* scene1;
Scene* scene2;

void BaseRunner::OnCreate()
{
	GraphicsEngine::Initialize(this);
	ImguiHandler::Initialize(hwnd,GraphicsEngine::GetD3DDevice(), GraphicsEngine::GetDeviceContext(), GraphicsEngine::get().texture->m_shader_res_view);
	
	NetworkHandler::Initialize();
	
	auto size = GetWindowSize();
	auto camera_transform = Engine::Transform (Math::Vector3f(0, 0, -2), Math::Vector3f(1, 1, 1), Math::Vector3f(0, 0, 0));
	auto camera_object = new Camera(GameObjectData("0", "Camera", camera_transform, "nil"), size.x, size.y);
	CameraManager::SetCurrentCamera(camera_object);
	GameObjectManager::get().main += camera_object;

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

void BaseRunner::OnKeyboardInput(char key, bool up_or_down) 
{
	auto camera = (Camera*)GameObjectManager::get().main["0"];
	if (up_or_down) {
		switch (key) {
			case 'W':
			case 'S': camera->forward = 0.f;  break;
			case 'A':
			case 'D': camera->right = 0.f;  break;
			case 'Q':
			case 'E': camera->up = 0.f;  break;
		}
	}
	else {
		switch (key) {
			case 'W': camera->forward = 1.f; break;
			case 'S': camera->forward = -1.f;  break;

			case 'A': camera->right = -1.f; break;
			case 'D': camera->right = 1.f;  break;

			case 'Q': camera->up = -1.f; break;
			case 'E': camera->up = 1.f;  break;
		}
	}
}

Math::Vector2i prev;
bool first = true;

void BaseRunner::OnMouseMove(Math::Vector2i point)
{
	if (first) {
		prev = point;
		first = false;
	}

	Math::Vector2i delta = point - prev;

	prev = point;

	auto camera = (Camera*)GameObjectManager::get().main["0"];
	
	const float sensitivity = 0.1f; // tweak this
	const float degToRad = 3.14159265f / 180.0f;

	float dx = -delta.y * sensitivity * Time::deltaTime();
	float dy = -delta.x * sensitivity * Time::deltaTime();
	dx = std::clamp(dx, -89.0f * degToRad, 89.0f * degToRad);

	camera->x_rot = dx;
	camera->y_rot = dy;
}

void BaseRunner::OnMouseInput(int button, bool up_or_down) 
{

}