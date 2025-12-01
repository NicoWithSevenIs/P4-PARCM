#pragma once

#include "../../../SHARED/GameObjectData/GameObjectData.h"
#include "../../../SHARED/IMediator.h"
#include "Component/Component.h"
#include <vector>
namespace Engine {
	class GameObject: public IMediator<Component> {
		public:
			GameObjectData data;
			std::vector<Component*> components;
		public:
			inline GameObject(GameObjectData data): data(data) {}
			virtual void Notify(Component* notifier, std::string notification) override;
			virtual void Update();
			virtual void Draw();
			virtual void Release();
		public:
			void AddComponent(Component* component);
	};
}
