#pragma once

#include "Transform.h"
#include "GameObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
	float aspectRatio;
	float widthView;
	GameObject* gameObject;
public:
	Camera();
	Camera(float aspectRatio_i, float widthView_i);
	Camera(float aspectRatio_i, float widthView_i, const std::string& name);
	~Camera();

	void SetAspectRatio(float as);
	void SetWidthview(float wv);
	void SetGameObject(GameObject* gameObject);

	inline float GetAspectRatio() const { return aspectRatio; }
	inline float GetWidthView() const { return widthView; }
	inline GameObject* GetGameObject() { return gameObject; }
};