#pragma once

#include "Vector3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

class GameObject;

class Transform
{
private:
	glm::mat4 transformMat4;
	Vector3 position;
	Vector3 localPosition;
	Vector3 scale;
	Transform* parent;
	std::vector<Transform *> childObj;
public:
	GameObject* gameObject;

	Transform();
	~Transform();

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 vec);
	
	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(Vector3 vec);

	void SetScale(float x, float y, float z);
	void SetScale(Vector3 scale);

	void SetParent(Transform* parent);

	inline Vector3* GetPosition() { return &position; }
	inline Vector3* GetLocalPosition() { return &localPosition; }
	inline Vector3 GetScale() { return scale; }
	inline Transform* GetParent() { return parent; }
	inline glm::mat4 GetMat4() const { return transformMat4; }
	inline std::vector<Transform *> GetChildObjects() { return childObj; }
};