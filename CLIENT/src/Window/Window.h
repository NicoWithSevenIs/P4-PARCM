#pragma once
#include <Windows.h>
#include "../../../Library/Time/Time.h"
#include "../../../Library/Math.h"
#include <iostream>

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

	public:
		virtual void OnFocus();
		virtual void OnUnfocus();

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
