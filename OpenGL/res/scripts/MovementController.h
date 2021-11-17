#pragma once

#include "DynamicObject.h"

class MovementController : public DynamicObject
{
public:
	Camera* camera;
	float speed = 1.0f;
	float jumpForce = 5;

	void Start() override;
	void Update() override;
	void OnCollision(Collision* collision) override;
	void OnTriggerCollision(Collision* collision) override;
}; 