#pragma once

#include "Vector3.h"

#include <vector>

class Collider;

class Collision
{
public:
	Collision();
	Collision(Collider* collider, Collider* otherCollider);

	float constrantHeight;
	float constrantWidth;
	float distanceHeight;
	float distanceWidth;

	Collider* otherCollider;
};