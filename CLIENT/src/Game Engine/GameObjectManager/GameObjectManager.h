#pragma once


#include "../../../../SHARED/Singleton.h"
#include "../../../../SHARED/Time/Time.h"
#include "../GameObject.h"

#include <vector>
#include <unordered_map>

namespace Engine {
	class GameObjectManager: public Singleton<GameObjectManager> {
		private: 
			std::unordered_map<std::string, GameObject*> object_map;

		public:
			GameObjectManager();

		public:
			void AddGameObject(GameObjectData gameobject);
			void AddGameObjects(std::vector<GameObjectData> gameobjects);

		public:
			static void Update();
			static void Draw();
			static void Release();
	};
}
