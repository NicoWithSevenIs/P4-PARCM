#pragma once

#include "../../../SHARED/GameObject/GameObject.h"
#include "../../../SHARED/Singleton.h"
#include "../../../SHARED/Time/Time.h"
#include <vector>

namespace Engine {
	class GameObjectManager: public Singleton<GameObjectManager> {
		private: 
			std::vector<GameObject*> gameobjects;

		public:
			void AddGameObject(GameObject* gameobject);
			void AddGameObjects(std::vector<GameObject*> gameobjects);

		public:
			void Update();
			void Draw();
			void Release();
	};
}
