#pragma once

#include "Window/Window.h"
#include "Graphics Engine/GraphicsEngine.h"
#include "Network Handler/NetworkHandler.h"
#include "Imgui Handler/ImguiHandler.h"
#include "Game Engine/GameObjectManager/GameObjectManager.h"

class BaseRunner final: public Window 
{
	public:
		BaseRunner();
		~BaseRunner() = default;

	public:
		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;

	public:
		virtual void OnKeyboardInput(char key, bool up_or_down) override;
		virtual void OnMouseMove(Math::Vector2i point) override;
		virtual void OnMouseInput(int button, bool up_or_down) override;
};