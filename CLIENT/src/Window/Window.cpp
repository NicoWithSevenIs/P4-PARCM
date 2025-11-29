#include "Window.h"

Window* window = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	
	extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;
	
	switch (msg) {

	case WM_CREATE:
		window->SetHWND(hwnd);
		break;
	case WM_DESTROY:
		window->OnDestroy();
		::PostQuitMessage(0);
		break;

	case WM_SETFOCUS:
		window->OnFocus();
		::PostQuitMessage(0);
		break;

	case WM_KILLFOCUS:
		window->OnUnfocus();
		::PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return NULL;
}

bool Window::Initialize(int width, int height)
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		return false;

	if (!window)
		window = this;

	this->hwnd = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, 
		"MyWindowClass", 
		"DirectX Application", 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		width,
		height,
		NULL, NULL, NULL, NULL);

	if (!this->hwnd)
		return false;

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	window_size = Math::Vector2u(width, height);
	is_running = true;

	window->OnCreate();
	return true;
}

bool Window::Release()
{
	return ::DestroyWindow(this->hwnd);
}

void Window::Broadcast()
{
	MSG msg;

	Time::LogFrameStart();
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	window->OnUpdate();

	Sleep(0);
	Time::LogFrameEnd();
}

void Window::OnCreate(){}
void Window::OnUpdate() {}
void Window::OnDestroy(){}
void Window::OnFocus() {}
void Window::OnUnfocus(){}

bool Window::IsRunning() 
{
	return this->is_running;
}

RECT Window::ClientWindowRect() 
{
	RECT rc;
	::GetClientRect(this->hwnd, &rc);
	return rc;
}

