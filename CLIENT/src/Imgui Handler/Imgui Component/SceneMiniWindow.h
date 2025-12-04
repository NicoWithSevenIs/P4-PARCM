#pragma once
#include "ImguiComponent.h"
#include "d3d11.h"

class SceneMiniWindow final : public ImguiComponent {

	public:
		ID3D11ShaderResourceView* thumbnailTexture;

	inline void Initialize() override {

	}

	inline void Update(double deltaTime) override {
		if (this->fDisplayVal < 100) {
			this->fDisplayVal += deltaTime;
		}
		
	}

	inline void Render() override {
		ImGui::SetNextWindowPos(ImVec2(x, y));
		ImGui::SetNextWindowSize(ImVec2(width, height));
		ImGui::Begin(this->name.c_str());
		ImTextureID tex = (ImTextureID)thumbnailTexture;

		if (ImGui::ImageButton(tex,ImVec2(64, 64), ImVec2(0, 0),ImVec2(1, 1), 0, ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, 1)))
		{
			printf("You clicked the image button!\n");
		}
		ImGui::ProgressBar(this->fDisplayVal);
		ImGui::End();
	}
};