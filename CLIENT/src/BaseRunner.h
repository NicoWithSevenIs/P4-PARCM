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
		void OnFocus() override;
		void OnUnfocus() override;
};