#include "BoxCollider.h"

#include "GameObject.h"
#include <math.h>

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(float width, float height, Vector3 offset)
	:width(width), height(height)
{
	colliderOffset = offset;
}

bool BoxCollider::CheckCollision(Collider* collider_i)
{
	BoxCollider* collider = dynamic_cast<BoxCollider*>(collider_i);
	if(collider != nullptr)
	{
		//bottom left corner
		float x = gameObject->GetTransfrom()->GetPosition()->x + colliderOffset.x - (scaledWidth/ 2);
		float y = gameObject->GetTransfrom()->GetPosition()->y + colliderOffset.y - (scaledHeight / 2);
		float otherX = collider->gameObject->GetTransfrom()->GetPosition()->x + collider->colliderOffset.x - (collider->scaledWidth/ 2);
		float otherY = collider->gameObject->GetTransfrom()->GetPosition()->y + collider->colliderOffset.y - (collider->scaledHeight / 2);

		if (x < otherX + collider->scaledWidth &&
			x + scaledWidth > otherX &&
			y < otherY + collider->scaledHeight &&
			y + scaledHeight > otherY)
		{
			collidedObjects.push_back(collider_i);
			return true;
		}
	}

	collidedObjects.clear();

	return false;
}

Collision BoxCollider::GenerateCollision(Collider * otherCollider)
{
	BoxCollider* collider = dynamic_cast<BoxCollider*>(otherCollider);
	if (collider != nullptr)
	{
		Collision col;
		col.constrantWidth = (scaledWidth + collider->scaledWidth) / 2;
		col.constrantHeight = (scaledHeight + collider->scaledHeight) / 2;
		col.distanceWidth = abs(gameObject->GetTransfrom()->GetPosition()->x - collider->gameObject->GetTransfrom()->GetPosition()->x);
		col.distanceHeight = abs(gameObject->GetTransfrom()->GetPosition()->y - collider->gameObject->GetTransfrom()->GetPosition()->y);
		col.otherCollider = otherCollider;
		return col;
	}
	
	return Collision();
}

void BoxCollider::SetScale()
{
	scaledWidth = width * gameObject->GetTransfrom()->GetScale().x;
	scaledHeight = height * gameObject->GetTransfrom()->GetScale().y;
}