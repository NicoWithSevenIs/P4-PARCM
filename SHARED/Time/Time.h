#pragma once

#include <chrono>
#include <ctime>

#include "../Singleton.h"

class Time : Singleton<Time>
{
private:
	double delta_time = 0.0;

private:
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

public:
	static double deltaTime();

public:
	static void LogFrameStart();
	static void LogFrameEnd();

	static std::string now();

};

