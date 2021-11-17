#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"

#include "Logger.h"

Transform::Transform()
	:transformMat4(glm::mat4(1.0f)), position(Vector3()), localPosition(Vector3()), rotation(Vector3(0,0,45)), localRotation(Vector3(0,0,0)), scale(1,1,1), parent(nullptr), parentId(0)
{
}

Transform::~Transform()
{
}

void Transform::SetPosition(float x, float y, float z)
{
	position.SetVector3(x,y,z);
	SetPositionRotationScale();

	for (int i = 0; i < childObj.size(); i++)
	{
		childObj[i]->SetLocalPosition(childObj[i]->localPosition);
	}
}

void Transform::SetPosition(Vector3 vec)
{
	position.SetVector3(vec);
	SetPositionRotationScale();

	for (int i = 0; i < childObj.size(); i++)
	{
		childObj[i]->SetLocalPosition(childObj[i]->localPosition);
	}
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation.SetVector3(x, y, z);
	SetPositionRotationScale();
}

void Transform::SetRotation(Vector3 vec)
{
	rotation.SetVector3(vec);
	SetPositionRotationScale();
}

void Transform::SetPositionRotationScale()
{
	glm::mat4 scaleMat4 = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));
	glm::mat4 positionMat4 = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
	glm::mat4 rotationMat4 = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	rotationMat4 = glm::rotate(rotationMat4, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	rotationMat4 = glm::rotate(rotationMat4, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	//scale, rotation, position
	transformMat4 = positionMat4 * rotationMat4 * scaleMat4;
}

Vector3 Transform::AngleDiffernceOfParentAndChild()
{
	Vector3 vec;

	vec.x = tan(localPosition.z / localPosition.y);
	vec.y = tan(localPosition.x / localPosition.z);

	return vec;
}

void Transform::SetLocalPosition(float x, float y, float z)
{
	Vector3 vec(x, y, z);
	localPosition = vec;

	float zR = sqrt((pow(localPosition.x, 2) + pow(localPosition.y, 2)));
	float zX = zR * cos(glm::radians(parent->GetRotation()->z + atan((localPosition.y / localPosition.x)) * 180.0f / 3.14159));
	float zY = zR * sin(glm::radians(parent->GetRotation()->z + atan((localPosition.y / localPosition.x)) * 180.0f / 3.14159));

	Vector3 vec2;
	vec2.x = zX;
	vec2.y = zY;

	SetPosition(*parent->GetPosition() + vec2);
}

void Transform::SetLocalPosition(Vector3 vec)
{
	localPosition = vec;

	float zR, zTheta, zX, zY, xR, xTheta, xY, xZ, yR, yTheta, yZ, yX;

	zR = sqrt((pow(localPosition.x, 2) + pow(localPosition.y, 2)));
	zTheta = atan((localPosition.y / localPosition.x)) * 180.0f / 3.14159;
	if (localPosition.x == 0)
		zTheta = 0;
	zX = zR * cos(glm::radians(parent->GetRotation()->z + zTheta));
	zY = zR * sin(glm::radians(parent->GetRotation()->z + zTheta));

	xR = sqrt((pow(localPosition.z, 2) + pow(localPosition.y, 2)));
	xTheta = atan((localPosition.z / localPosition.y)) * 180.0f / 3.14159;
	if (localPosition.y == 0)
		xTheta = 0;
	xY = xR * cos(glm::radians(parent->GetRotation()->x + xTheta));
	xZ = xR * sin(glm::radians(parent->GetRotation()->x + xTheta));

	yR = sqrt((pow(localPosition.x, 2) + pow(localPosition.z, 2)));
	yTheta = atan((localPosition.x / localPosition.z)) * 180.0f / 3.14159;
	if (localPosition.z == 0)
		yTheta = 0;
	yZ = yR * cos(glm::radians(parent->GetRotation()->y + yTheta));
	yX = yR * sin(glm::radians(parent->GetRotation()->y + yTheta));
	std::cout << xZ;

	Vector3 vec2;
	vec2.x = zX + yX;
	vec2.y = zY + xY;
	vec2.z = xZ + yZ;

	SetPosition(*parent->GetPosition() + vec2);
}

void Transform::SetScale(float x, float y, float z)
{
	scale = Vector3(x,y,z);
	if (gameObject->GetCollider() != nullptr)
		gameObject->GetCollider()->SetScale();

	SetPositionRotationScale();
}

void Transform::SetScale(Vector3 i_scale)
{
	scale = i_scale;
	if (gameObject->GetCollider() != nullptr)
		gameObject->GetCollider()->SetScale();
}

void Transform::SetParent(Transform * i_parent)
{
	if (i_parent != nullptr)
	{
		parent = i_parent;
		i_parent->childObj.push_back(this);
		SetLocalPosition(position.x, position.y, position.z);
		if (gameObject->GetCollider() != nullptr)
			gameObject->GetCollider()->topGameObject = i_parent->gameObject;
		Scene::currentScene->SetSceneHierarchy();
	}
	else
	{
		for (int i = 0; i < i_parent->childObj.size(); i++)
		{
			if (i_parent->childObj[i] == this)
			{
				parent = nullptr;
				if (gameObject->GetCollider() != nullptr)
					gameObject->GetCollider()->topGameObject = gameObject;
				i_parent->childObj.erase(i_parent->childObj.begin() + i);
			}
		}
	}
	Scene::currentScene->SetSceneHierarchy();
}

void Transform::SetParentID(unsigned int _parentID)
{
	parentId = _parentID;
}

