#pragma once
#include "ImguiComponent.h"
#include "../../Game Engine/GameObjectManager/GameObjectManager.h"
#include "../../Network Handler/NetworkHandler.h"


class UI_FPSDisplay final : public ImguiComponent {
	inline void Initialize() override {

	}

	inline void Update(double deltaTime) override {
		float fps = 1 / deltaTime;
		this->fDisplayVal = fps;

	}

	inline void Render() override {
		//ImGui::SetNextWindowPos(ImVec2(1080, 600));
		ImGui::SetNextWindowSize(ImVec2(width, height * 1.6));
		ImGui::Begin("FPS");
		ImGui::Text("FPS: %.2f", this->fDisplayVal);
		if (ImGui::Button("View All")) {

			int ave = 0;
			for (auto& i : NetworkHandler::get().progress) 
				ave+=i;
			
			if (ave / 5 == 1) 
				GameObjectManager::ConsolidateScenes(NetworkHandler::get().scene_cache);
			
		}
		ImGui::End();
	}
};