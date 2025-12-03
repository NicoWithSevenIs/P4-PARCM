#pragma once

#include "../../../SHARED/GameObjectData/GameObjectData.h"
#include "../../../SHARED/IMediator.h"
#include "Component/Component.h"
#include "Component/Transform/TransformComponent.h"

#include <vector>
#include <sstream>
namespace Engine {
	class GameObject: public IMediator<Component> {
		public:
			GameObjectData data;
		protected:
		
			std::vector<Component*> components;

		public:
			GameObject(GameObjectData data);
			
			virtual void Update();
			virtual void Draw();
			virtual void Release();
		public:
			void AddComponent(Component* component);

			virtual void Notify(Component* notifier, std::string notification) override;
			Component* Get(std::string name);
	};
}
