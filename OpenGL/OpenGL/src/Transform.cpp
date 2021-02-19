#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"

#include "Logger.h"

Transform::Transform()
	:transformMat4(glm::mat4(1.0f)), position(Vector3()), localPosition(Vector3()), scale(1,1,1), parent(nullptr)
{
}

Transform::~Transform()
{
}

void Transform::SetPosition(float x, float y, float z)
{
	position.SetVector3(x, y, z);
	transformMat4 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void Transform::SetPosition(Vector3 vec)
{
	position.SetVector3(vec);
	transformMat4 = glm::translate(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, vec.z));

	for (int i = 0; i < childObj.size(); i++)
	{
		childObj[i]->SetLocalPosition(childObj[i]->localPosition);
	}
}

void Transform::SetLocalPosition(float x, float y, float z)
{
	Vector3 vec(x, y, z);
	localPosition = vec;
	SetPosition(*parent->GetPosition() + localPosition);
}

void Transform::SetLocalPosition(Vector3 vec)
{
	localPosition = vec;
	SetPosition(*parent->GetPosition() + localPosition);
}

void Transform::SetScale(float x, float y, float z)
{
	scale = Vector3(x,y,z);
	if (gameObject->GetCollider() != nullptr)
		gameObject->GetCollider()->SetScale();
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
		SetLocalPosition(position);
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
