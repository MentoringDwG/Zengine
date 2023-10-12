// Copyright Z.Z. Zengine (c)

#include "Timer.h"

void Timer::Reset()
{
	start_time = std::chrono::high_resolution_clock::now();
	end_time = std::chrono::high_resolution_clock::now();
	time = (std::chrono::nanoseconds)0;
}

void Timer::TimerStop()
{
	end_time = std::chrono::high_resolution_clock::now();
	time = end_time - start_time;
	timeMs = (int)(time / std::chrono::milliseconds(1));
}