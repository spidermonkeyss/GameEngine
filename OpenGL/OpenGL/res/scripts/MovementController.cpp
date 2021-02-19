#include "MovementController.h"

void MovementController::Start()
{
}

void MovementController::Update()
{
	if (attachedObject->GetRigidbody()->doGravity)
	{
		attachedObject->GetRigidbody()->SetVelocity(Vector3(0, attachedObject->GetRigidbody()->GetVelocity().y, 0));
		//Jump
		if (Input::GetKeyDown(Input::W))
			attachedObject->GetRigidbody()->AddForce(Vector3(0, jumpForce, 0));
	}
	else
	{
		attachedObject->GetRigidbody()->SetVelocity(Vector3());
		// Move Up
		if (Input::GetKey(Input::W))
			attachedObject->GetRigidbody()->AddForce(Vector3(0, speed, 0));
		// Move Down
		if (Input::GetKey(Input::S))
			attachedObject->GetRigidbody()->AddForce(Vector3(0, -speed,0));
	}
	// Strafe right
	if (Input::GetKey(Input::D))
		attachedObject->GetRigidbody()->AddForce(Vector3(speed, 0, 0));
	// Strafe left
	if (Input::GetKey(Input::A))
		attachedObject->GetRigidbody()->AddForce(Vector3(-speed, 0, 0));

	if (Input::GetKey(Input::H))
		attachedObject->GetTransfrom()->SetScale(2, 2, 0);
}

void MovementController::OnCollision(Collision * collision)
{
}

void MovementController::OnTriggerCollision(Collision * collision)
{
	DestoryGameObject(collision->otherCollider->gameObject);
}
