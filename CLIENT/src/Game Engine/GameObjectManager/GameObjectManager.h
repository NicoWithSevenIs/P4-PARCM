#pragma once


#include "../../../../SHARED/Singleton.h"
#include "../../../../SHARED/Time/Time.h"
#include "../GameObject.h"

#include <vector>
#include <unordered_map>

#include "../Component/Mesh Renderer/MeshRenderer.h"
#include "../Camera/Camera.h"

#include "Scene.h"

namespace Engine {
	class GameObjectManager: public Singleton<GameObjectManager> {
		public: 
			Scene main;
			Scene* current_scene = nullptr;

		public:
			GameObjectManager();

		public:
			static void LoadScene(Scene* to_load);
			static void UnloadCurrentScene();

		public:
			static void Update();
			static void Draw();
			static void Release();
			static void ConsolidateScenes(std::vector<Scene*> scenes);
	};
}
