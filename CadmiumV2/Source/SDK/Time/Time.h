#pragma once
#include <chrono>



class Time
{
private:
	int targetFps = 300;
	std::chrono::microseconds frameDuration; // 3.33 мс


	std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
	std::chrono::nanoseconds elapseTime;


public:
	Time(int maxFps = 300);
	~Time();

	const float GetDeltaTime();
	const bool IsUpdated();

};

