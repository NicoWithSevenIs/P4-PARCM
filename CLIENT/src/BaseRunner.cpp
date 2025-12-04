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
	ImguiHandler::Initialize(hwnd,GraphicsEngine::GetD3DDevice(), GraphicsEngine::GetDeviceContext());

	//NetworkHandler::Initialize();
	//NetworkHandler::MessageServer();

	auto size = GetWindowSize();
	auto camera_transform = Engine::Transform (Math::Vector3f(0, 0, -2), Math::Vector3f(1, 1, 1), Math::Vector3f(0, 0, 0));
	auto camera_object = new Camera(GameObjectData("0", "Camera", camera_transform, "nil"), size.x, size.y);
	CameraManager::SetCurrentCamera(camera_object);
	GameObjectManager::get().main += camera_object;

	//
	

	scene1 = new Scene();

	auto cow_transform = Engine::Transform(Math::Vector3f(0, 0, 5), Math::Vector3f(0.3, 0.3, 0.3), Math::Vector3f(0, 0, 0));
	auto cow_object = new Engine::GameObject( GameObjectData("1", "Cow (Your Mom)", cow_transform, "COW") );

	auto mesh_renderer = new MeshRenderer();
	mesh_renderer->Initialize("cow.obj", "mesh_vertex.hlsl", "mesh_pixel.hlsl");
	cow_object->AddComponent(mesh_renderer);

	*scene1 += cow_object;

	auto lucy_transform = Engine::Transform(Math::Vector3f(10, 0, 15), Math::Vector3f(0.01, 0.01, 0.01), Math::Vector3f(90 * 3.14159265358979323846 / 180.0, 0, 0));
	auto lucy_object = new Engine::GameObject(GameObjectData("2", "Lucy", lucy_transform, "LUCY"));

	auto mesh_renderer2 = new MeshRenderer();
	mesh_renderer2->Initialize("lucy.obj", "mesh_vertex.hlsl", "mesh_pixel.hlsl");
	lucy_object->AddComponent(mesh_renderer2);

	*scene1 += lucy_object;
	
	//
	
	scene2 = new Scene();

	auto cow_transform2 = Engine::Transform(Math::Vector3f(-3, 0, 5), Math::Vector3f(0.3, 0.3, 0.3), Math::Vector3f(0, 0, 0));
	auto cow_object2 = new Engine::GameObject(GameObjectData("3", "Cow (Your Mom)", cow_transform2, "COW"));

	auto mesh_renderer3 = new MeshRenderer();
	mesh_renderer3->Initialize("cow.obj", "mesh_vertex.hlsl", "mesh_pixel.hlsl");
	cow_object2->AddComponent(mesh_renderer3);

	*scene2 += cow_object2;

	auto cow_transform3 = Engine::Transform(Math::Vector3f(3, 0, 5), Math::Vector3f(0.3, 0.3, 0.3), Math::Vector3f(0, 90 * 3.14159265358979323846 / 180.0, 0));
	auto cow_object3 = new Engine::GameObject(GameObjectData("4", "Cow (Your Mom)", cow_transform3, "COW"));

	auto mesh_renderer4 = new MeshRenderer();
	mesh_renderer4->Initialize("cow.obj", "mesh_vertex.hlsl", "mesh_pixel.hlsl");
	cow_object3->AddComponent(mesh_renderer4);

	*scene2 += cow_object3;

	auto lucy_transform2 = Engine::Transform(Math::Vector3f(0, 0, 15), Math::Vector3f(0.01, 0.01, 0.01), Math::Vector3f(90 * 3.14159265358979323846 / 180.0, 0, 0));
	auto lucy_object2 = new Engine::GameObject(GameObjectData("5", "Lucy", lucy_transform2, "LUCY"));

	auto mesh_renderer5 = new MeshRenderer();
	mesh_renderer5->Initialize("lucy.obj", "mesh_vertex.hlsl", "mesh_pixel.hlsl");
	lucy_object2->AddComponent(mesh_renderer5);

	*scene2 += lucy_object2;

	GameObjectManager::LoadScene(scene1);
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