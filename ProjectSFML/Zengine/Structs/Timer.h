#pragma once
#include <chrono>

struct Timer
{
	std::chrono::steady_clock::time_point start_time;
	std::chrono::steady_clock::time_point end_time;
	std::chrono::nanoseconds time;
	int timeMs;

	Timer()
	{
		start_time = std::chrono::high_resolution_clock::now();
		end_time = std::chrono::high_resolution_clock::now();
		time = (std::chrono::nanoseconds)0;
	}

	void TimerStop()
	{
		end_time = std::chrono::high_resolution_clock::now();
		time = end_time - start_time;
		timeMs = time / std::chrono::milliseconds(1);
	}
};

