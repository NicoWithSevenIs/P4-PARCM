#pragma once

#include "../../../SHARED/Time/Time.h"
#include "../../../SHARED/Math.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <iostream>
#include <Windows.h>
#include <windowsx.h>
class Window {
	protected:
		HWND hwnd;
		bool is_running;

	protected:
		Math::Vector2u window_size;

	public:
		inline Window(){}
		~Window() = default;

	public:
		bool Initialize(int width, int height);
		bool Release();
		void Broadcast();

	public:
		virtual void OnCreate();
		virtual void OnUpdate();
		virtual void OnDestroy();
		virtual void OnKeyboardInput(char key, bool up_or_down);
		virtual void OnMouseMove(Math::Vector2i point);
		virtual void OnMouseInput(int button, bool up_or_down);

	public:
		bool IsRunning();
		RECT ClientWindowRect();

	public:
		inline Math::Vector2u GetWindowSize() {
			return this->window_size;
		}
		inline HWND GetHWND() {
			return this->hwnd;
		}
		inline void SetHWND(HWND window) {
			this->hwnd = window;
		}


};
