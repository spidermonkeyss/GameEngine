#include "Rigidbody.h"

#include "GameObject.h"
#include "EngineTime.h"
#include "Collision.h"

Rigidbody::Rigidbody(Physics * physics)
	:physics(physics)
{
}

void Rigidbody::Update()
{
	if (!enabled)
		return;
	
	//Gravtity
	if (doGravity)
	{
		float gravtiyForce = (physics->gravtity * Time::GetDeltaTime());
		AddForce(Vector3(0, gravtiyForce, 0));
	}

	//Set position
	gameObject->SetTransformPosition(*gameObject->GetTransfrom()->GetPosition() + (velocity * Time::GetDeltaTime()));
}

void Rigidbody::SetVelocity(Vector3 velocity_i)
{
	velocity = velocity_i;
}

void Rigidbody::SetPhysics(Physics * physics_i)
{
	physics = physics_i;
}

void Rigidbody::AddForce(Vector3 force)
{
	velocity.SetVector3(velocity.x + force.x, velocity.y + force.y, velocity.z + force.z);
}

//Dynamic to static collision
void Rigidbody::OnCollision(Collision * collision)
{
	float widthConstrantDistanceDiffernce = collision->constrantWidth - collision->distanceWidth;
	float heightConstrantDistanceDiffernce = collision->constrantHeight - collision->distanceHeight;

	//apply normal forces
	Vector3 forceNormal;
	if (widthConstrantDistanceDiffernce < heightConstrantDistanceDiffernce)
	{
		forceNormal.x = -(velocity.x);
	}
	else
	{
		if (gameObject->GetTransfrom()->GetPosition()->y > collision->otherCollider->gameObject->GetTransfrom()->GetPosition()->y &&
			velocity.y < 0)
			forceNormal.y = -(velocity.y) + -(physics->gravtity * Time::GetDeltaTime());
		else if (gameObject->GetTransfrom()->GetPosition()->y < collision->otherCollider->gameObject->GetTransfrom()->GetPosition()->y)
			forceNormal.y = -(velocity.y);
	}
	AddForce(forceNormal);
	
	//If collision is this deep then snap object out
	float maxPentartionDistance = 0.001f;
	if (widthConstrantDistanceDiffernce > maxPentartionDistance && heightConstrantDistanceDiffernce > maxPentartionDistance)
	{
		//Penetartion
		if (widthConstrantDistanceDiffernce < heightConstrantDistanceDiffernce)
		{
			float xDiffence = gameObject->GetTransfrom()->GetPosition()->x - collision->otherCollider->gameObject->GetTransfrom()->GetPosition()->x;
			float positiveORnegative = xDiffence / abs(xDiffence);//Get object left or right times 1
			
			if (collision->otherCollider->gameObject->GetRigidbody() != nullptr)//If both objects have rigidbodys push back only half distance
				widthConstrantDistanceDiffernce /= 2; 
			
			gameObject->SetTransformPosition(*gameObject->GetTransfrom()->GetPosition() + Vector3::Right() * widthConstrantDistanceDiffernce * positiveORnegative);
		}
		else
		{
			float yDiffence = gameObject->GetTransfrom()->GetPosition()->y - collision->otherCollider->gameObject->GetTransfrom()->GetPosition()->y;
			float positiveORnegative = yDiffence / abs(yDiffence);//Get object up or down times 1

			if (collision->otherCollider->gameObject->GetRigidbody() != nullptr)//If both objects have rigidbodys push back only half distance
				heightConstrantDistanceDiffernce /= 2;
			
			gameObject->SetTransformPosition(*gameObject->GetTransfrom()->GetPosition() + Vector3::Up() * heightConstrantDistanceDiffernce * yDiffence);
		}
	}
}
