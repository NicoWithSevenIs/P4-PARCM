#pragma once
#include "string"
class ImguiComponent {
	public:
		std::string name = "name";
		bool isOpen = true;
		float height = 0.0f;
		float width = 0.0f;
		float fDisplayVal = 0.0f;
		float x = 0.0f;
		float y = 0.0f;

	public:
		virtual void Initialize() = 0;
		virtual void Update(double deltaTime) {};
		virtual void Render() = 0;
};