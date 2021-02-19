#include"DynamicObject.h"


DynamicObject::DynamicObject()
{
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::SetAttachedObject(GameObject * gameObject)
{
	attachedObject = gameObject;
}

//Mesh will not be deleted. May be used by another object
void DynamicObject::DestoryGameObject(GameObject * gameobject)
{
	//loop childern first

	for (int i = 0; i < Scene::currentScene->gameObjects.size(); i++)
	{
		if (Scene::currentScene->gameObjects[i].get() == gameobject)
		{
			for (int j = 0; j < Scene::currentScene->colliders.size(); j++)
			{
				if (Scene::currentScene->colliders[j]->gameObject == gameobject)
					Scene::currentScene->colliders.erase(Scene::currentScene->colliders.begin() + j);
			}
			for (int j = 0; j < Scene::currentScene->topGameObjects.size(); j++)
			{
				if (Scene::currentScene->topGameObjects[j] == gameobject)
					Scene::currentScene->topGameObjects.erase(Scene::currentScene->topGameObjects.begin() + j);
			}
			for (int j = 0; j < Scene::currentScene->rigidbodys.size(); j++)
			{
				if (Scene::currentScene->rigidbodys[j]->gameObject == gameobject)
					Scene::currentScene->rigidbodys.erase(Scene::currentScene->rigidbodys.begin() + j);
			}
			for (int j = 0; j < Scene::currentScene->dynamicObjectScripts.size(); j++)
			{
				if (Scene::currentScene->dynamicObjectScripts[j]->attachedObject == gameobject)
					Scene::currentScene->dynamicObjectScripts.erase(Scene::currentScene->dynamicObjectScripts.begin() + j);
			}
			
			Scene::currentScene->gameObjects[i].reset();
			
			Scene::currentScene->gameObjects.erase(Scene::currentScene->gameObjects.begin() + i);
		}
	}
}

void DynamicObject::Start()
{
}

void DynamicObject::Update()
{
}

void DynamicObject::OnCollision(Collision* collision)
{
}

void DynamicObject::OnTriggerCollision(Collision * collision)
{
}
