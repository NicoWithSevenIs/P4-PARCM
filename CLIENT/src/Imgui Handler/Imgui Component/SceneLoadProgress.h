#pragma once
#include "ImguiComponent.h"
#include "../../Game Engine/GameObjectManager/GameObjectManager.h"
#include "../../Network Handler/NetworkHandler.h"

class SceneLoadProgress final : public ImguiComponent {

	public:
		int  selected_index = -1;

	public:

		inline void Initialize() override {


		}
		inline void Update(double deltaTime) override {
			if (selected_index != -1) {
				if (NetworkHandler::get().progress[selected_index] >= 1.f) {
					auto scene = NetworkHandler::get().scene_cache[selected_index];
					GameObjectManager::LoadScene(scene);
					selected_index = -1;
				}
			}
		}

		inline void Render() override {
			ImGui::SetNextWindowSize(ImVec2(width, height));
			if(selected_index >= 0)
				ImGui::ProgressBar(NetworkHandler::get().progress[selected_index]);
			ImGui::End();
		}
};