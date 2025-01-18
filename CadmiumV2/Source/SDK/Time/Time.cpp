#include "Time.h"

Time::Time(int maxFps)
{
	lastTime = std::chrono::high_resolution_clock::now();
	targetFps = maxFps;
	frameDuration = std::chrono::microseconds(1000000 / targetFps);
}

Time::~Time()
{
}


const float Time::GetDeltaTime()
{
	return elapseTime.count() / 1000000;
}

const bool Time::IsUpdated()
{
	currentTime = std::chrono::high_resolution_clock::now();
	elapseTime = currentTime - lastTime;


	if (elapseTime >= frameDuration) {
		lastTime += frameDuration;

		return true;
	}
	return false;
}
