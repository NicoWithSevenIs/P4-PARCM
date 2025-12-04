#pragma once


#include "../../../../SHARED/Singleton.h"
#include "../../../../SHARED/Time/Time.h"
#include "../GameObject.h"

#include <vector>
#include <unordered_map>

#include "../Component/Mesh Renderer/MeshRenderer.h"
#include "../Camera/Camera.h"

namespace Engine {
	class GameObjectManager: public Singleton<GameObjectManager> {
		private: 
			std::unordered_map<std::string, GameObject*> object_map;

		public:
			GameObjectManager();

		public:
			static GameObject* AddGameObject(GameObjectData gameobject);
			static void AddGameObject(GameObject* gameobject);
			inline static GameObject* GetGameObject(std::string uid){ return get().object_map[uid]; }

			void AddGameObjects(std::vector<GameObjectData> gameobjects);


		public:
			static void Update();
			static void Draw();
			static void Release();
	};
}
