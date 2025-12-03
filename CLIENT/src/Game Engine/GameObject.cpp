#include "GameObject.h"

using namespace Engine;


GameObject::GameObject(GameObjectData data) : data(data) 
{
	auto transform = new TransformComponent(data.GetTransform());
	AddComponent(transform);
}

void GameObject::Notify(Component* notifier, std::string notification)
{

}

void GameObject::Update()
{
	for (auto& component : this->components) {
		if (component->GetType() == ComponentType::SCRIPT) {
			component->Update();
		}
	}
}

void GameObject::Draw()
{
	for (auto& component : this->components) {
		if (component->GetType() == ComponentType::RENDERER) {
			component->Update();
		}	
	}
}

void GameObject::AddComponent(Component* component)
{
	if (!Get(component->GetName())) {
		component->SetOwner(this);
		this->components.push_back(component);	
	}
}

Component* Engine::GameObject::Get(std::string name)
{
	for (auto& component : this->components) {
		if(component->GetName() == name)
			return component;
	}
	return nullptr;
}
void GameObject::Release()
{
	for (auto& component : this->components) {
		component->Release();
		delete component;
	}
}