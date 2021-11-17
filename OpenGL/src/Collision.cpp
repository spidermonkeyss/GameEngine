#include "Collision.h"

#include "Collider.h"

Collision::Collision()
{
}

Collision::Collision(Collider* collider, Collider* otherCollider)
	:otherCollider(otherCollider)
{
	
}