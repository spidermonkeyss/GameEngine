#pragma once

#include "Vector3.h"
#include "Physics.h"

class GameObject;
class Collider;
class Collision;

class Rigidbody
{
private:
	Vector3 velocity;
	Physics* physics;
	bool isColliding;
public:
	Rigidbody(Physics* physics);

	bool enabled = true;
	bool doGravity = true;
	GameObject* gameObject;

	void Update();
	void SetVelocity(Vector3 velocity);
	void SetPhysics(Physics* physics_i);
	void AddForce(Vector3 force);

	void OnCollision(Collision* collision);

	inline Vector3 GetVelocity() const { return velocity; }
};