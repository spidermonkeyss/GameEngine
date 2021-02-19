#include "EngineTime.h"
#include "TimeManager.h"

float Time::GetDeltaTime()
{
	return TimeManager::deltaTime;
}

float Time::GetTimeSeconds()
{
	return TimeManager::time / 1000.0f;
}

float Time::GetTimeMilliSenonds()
{
	return TimeManager::time;
}
