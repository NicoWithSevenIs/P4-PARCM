
#pragma once

#include <unordered_map>
#include "../../../../SHARED/Time/Time.h"
#include "../GameObject.h"


typedef std::string UID;

class Scene {
	private: 
		std::unordered_map<UID, Engine::GameObject*> scene_objects;

	public:
		inline void operator += (Engine::GameObject* gameobject) {
			if(!scene_objects.contains(gameobject->data.GetUID()))
				scene_objects[gameobject->data.GetUID()] = gameobject;
		}

		inline void operator -= (Engine::GameObject* gameobject) {
			if (scene_objects.contains(gameobject->data.GetUID()))
				scene_objects.erase(gameobject->data.GetUID());
		}

		inline Engine::GameObject* operator[] (const UID& unique_id) {
			return scene_objects[unique_id];
		}

		inline void Update() {
			for (auto& [uid, go] : this->scene_objects) {
				go->Update();
			}
		}

		inline void Clear() {
			scene_objects.clear();
		}
};