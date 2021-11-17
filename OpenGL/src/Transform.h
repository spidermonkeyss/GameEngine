#pragma once

#include "Vector3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

class GameObject;

class Transform
{
private:
	//serialied fields
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Transform* parent;

	//non serialied fields
	Vector3 localPosition;
	Vector3 localRotation;
	glm::mat4 transformMat4;
	std::vector<Transform *> childObj;

	void SetPositionRotationScale();
	Vector3 AngleDiffernceOfParentAndChild();

	//Used for deserializiontal
	unsigned int parentId;
public:
	GameObject* gameObject;

	Transform();
	~Transform();

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 vec);
	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3 vec);

	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(Vector3 vec);
	void SetLocalRotation(float x, float y, float z);
	void SetLocalRotation(Vector3 vec);

	void SetScale(float x, float y, float z);
	void SetScale(Vector3 scale);

	void SetParent(Transform* parent);

	void SetParentID(unsigned int parentID);

	inline Vector3* GetPosition() { return &position; }
	inline Vector3* GetLocalPosition() { return &localPosition; }
	inline Vector3 GetScale() { return scale; }
	inline Vector3* GetRotation() { return &rotation; }
	inline Transform* GetParent() { return parent; }
	inline glm::mat4 GetMat4() const { return transformMat4; }
	inline std::vector<Transform *> GetChildObjects() { return childObj; }
	inline unsigned int GetParentID() const { return parentId; }
};