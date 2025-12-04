#pragma once
#include <thread>
#include <functional>
#include <chrono>

class Task {
public:
	inline static void Spawn(std::function<void()> callable) {
		std::thread t(callable);
		t.detach();
	}

	inline static void Sleep(int milliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}
};