#pragma once
#include "ImguiComponent.h"
#include "d3d11.h"

#include "../../Network Handler/NetworkHandler.h"
#include "../../Game Engine/GameObjectManager/GameObjectManager.h"
#include "SceneLoadProgress.h"

class SceneMiniWindow final : public ImguiComponent {

	public:
		ID3D11ShaderResourceView* thumbnailTexture;
		int index = 0;

	inline void Initialize() override {

	}

	inline void Update(double deltaTime) override {
	}

	inline void Render() override {
		ImGui::SetNextWindowPos(ImVec2(x, y));
		ImGui::SetNextWindowSize(ImVec2(width, height));
		ImGui::Begin(this->name.c_str());
		ImTextureID tex = (ImTextureID)thumbnailTexture;
		auto loader = (SceneLoadProgress*)owner->Get("SCENE LOADER SCREEN");

		if (ImGui::ImageButton(tex,ImVec2(64, 64), ImVec2(0, 0),ImVec2(1, 1), 0, ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, 1)))
		{
			if (NetworkHandler::get().progress[index] == 1) 
			{
				GameObjectManager::LoadScene(NetworkHandler::get().scene_cache[index]);
				loader->selected_index = -1;
			}
			else 
			{	
				loader->selected_index = index == loader->selected_index? -1 : index;
			}

			if (loader->selected_index != -1)
				GameObjectManager::UnloadCurrentScene();
		}

		ImGui::ProgressBar(NetworkHandler::get().progress[index]);
		ImGui::End();
	}
};