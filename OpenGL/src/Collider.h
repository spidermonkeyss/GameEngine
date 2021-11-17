#pragma once

#include "Vector3.h"
#include "Collision.h"

#include <vector>

class GameObject;

class Collider 
{
protected:
	std::vector<Collider *> collidedObjects;
public:
	GameObject* gameObject;
	GameObject* topGameObject;
	Vector3 colliderOffset;
	bool enabled = true;
	bool isTrigger = false;

	virtual bool CheckCollision(Collider* collider);
	virtual Collision GenerateCollision(Collider* otherCollider);
	virtual void SetScale();
};