#pragma once
#include <chrono>

struct Timer
{
	Timer()
	{
		Reset();
	}

	void Reset();
	void TimerStop();

	std::chrono::steady_clock::time_point start_time;
	std::chrono::steady_clock::time_point end_time;
	std::chrono::nanoseconds time;
	int timeMs;
};

