//Script access
#pragma once

//this is managed by TimeManager
class Time
{
public:
	static float GetDeltaTime();
	static float GetTimeSeconds();
	static float GetTimeMilliSenonds();
};