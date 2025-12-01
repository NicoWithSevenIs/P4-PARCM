#include "GameObject.h"

using namespace Engine;

void GameObject::Notify(Component* notifier, std::string notification)
{
}

void GameObject::Update()
{
	for (auto& component : this->components) {
		if(component->GetType() == ComponentType::SCRIPT)
			component->Update();
	}
}

void GameObject::Draw()
{
	for (auto& component : this->components) {
		if (component->GetType() == ComponentType::RENDERER)
			component->Update();
	}
}

void GameObject::AddComponent(Component* component)
{
	this->components.push_back(component);
	component->SetOwner(this);
}
void GameObject::Release()
{
	for (auto& component : this->components) {
		component->Release();
		delete component;
	}
}