#include "Camera.h"

Camera::Camera()
	:aspectRatio(0), widthView(0)//, gameObject("Camera")
{

}

Camera::Camera(float aspectRatio_i, float widthView_i)
	:aspectRatio(aspectRatio_i), widthView(widthView_i)//, gameObject("Camera")
{

}

Camera::Camera(float aspectRatio_i, float widthView_i, const std::string & name)
	: aspectRatio(aspectRatio_i), widthView(widthView_i)//, gameObject(name)
{
}

Camera::~Camera()
{
}

void Camera::SetAspectRatio(float as)
{
	aspectRatio = as;
}

void Camera::SetWidthview(float wv)
{
	widthView = wv;
}

void Camera::SetGameObject(GameObject* _gameObject)
{
	gameObject = _gameObject;
}
