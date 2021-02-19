#include "ScreenSaverScript.h"

void ScreenSaverScript::Start()
{
	x = 0;
	y = 0;

	xBound = camera->GetWidthView() - 0.5f;
	yBound = camera->GetWidthView() / camera->GetAspectRatio() - 0.5f;
}

void ScreenSaverScript::Update()
{
	x += xSpeed;
	y += ySpeed;

	attachedObject->GetTransfrom()->SetPosition(x, y, 0);

	if (x > xBound || x < -xBound)
		xSpeed = -xSpeed;

	if (y > yBound || y < -yBound)
		ySpeed = -ySpeed;
}