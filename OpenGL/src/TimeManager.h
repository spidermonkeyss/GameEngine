//No script access
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TimeManager
{
private:
	long long timer;
	long long timer2;
	long long startTime;
	long long gameTime;
	long long prevGameTime;
	long long frameTime;
public:
	TimeManager();
	~TimeManager();

	static float deltaTime;
	static float time;
	void Init();
	void OnUpdate();
};
