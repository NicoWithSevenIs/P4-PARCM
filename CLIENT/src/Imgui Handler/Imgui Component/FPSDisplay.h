#pragma once
#include "ImguiComponent.h"

class UI_FPSDisplay final : public ImguiComponent {
	inline void Initialize() override {

	}

	inline void Update(double deltaTime) override {
		float fps = 1 / deltaTime;
		this->fDisplayVal = fps;

	}

	inline void Render() override {
		ImGui::SetNextWindowPos(ImVec2(1080, 600));
		ImGui::SetNextWindowSize(ImVec2(width, height));
		ImGui::Begin("FPS");
		ImGui::Text("FPS: %.2f", this->fDisplayVal);
		ImGui::End();
	}
};