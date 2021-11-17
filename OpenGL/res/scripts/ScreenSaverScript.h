#pragma once

#include "DynamicObject.h"

class ScreenSaverScript : public DynamicObject
{
public:
	Camera* camera;

	float xSpeed = 0.01f;
	float ySpeed = 0.01f;
	float x;
	float y;
	float xBound;
	float yBound;
	
	void Start() override;
	void Update() override;
};