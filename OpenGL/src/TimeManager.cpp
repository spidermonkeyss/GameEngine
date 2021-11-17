#include "TimeManager.h"

#include <iostream>

//Init static members
float TimeManager::deltaTime = 0;
float TimeManager::time = 0;

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Init()
{
	timer = 0;
	timer2 = 0;
	startTime = 0;
	gameTime = 0;
	prevGameTime = 0;
	frameTime = 0;
	glGetInteger64v(GL_TIMESTAMP, &timer);
	startTime = timer;
}

void TimeManager::OnUpdate()
{
	glGetInteger64v(GL_TIMESTAMP, &timer2);
	gameTime = timer2 - timer;
	frameTime = gameTime - prevGameTime;
	prevGameTime = gameTime;

	deltaTime = (float)frameTime / 1000000000.0f;
	time = (float)gameTime / 1000000.0f;
}
