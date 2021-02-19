#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
private:
	float width;
	float height;
	float scaledWidth;
	float scaledHeight;
public:
	BoxCollider();
	BoxCollider(float width, float height, Vector3 offset);

	bool CheckCollision(Collider* collider) override;
	Collision GenerateCollision(Collider* otherCollider) override;
	void SetScale() override;
};