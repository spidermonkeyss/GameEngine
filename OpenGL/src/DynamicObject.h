#pragma once

#include "GameObject.h"
#include "Time.h"
#include "TimeManager.h"
#include "Camera.h"
#include "Window.h"
#include "Input.h"
#include "Logger.h"
#include "Rigidbody.h"
#include "Scene.h"

#include <iostream>

class DynamicObject
{
protected:
	GameObject* attachedObject;
public:
	DynamicObject();
	~DynamicObject();

	void SetAttachedObject(GameObject* gameObject);
	
	//Mesh will not be deleted. May be used by another object
	void DestoryGameObject(GameObject* gameobject);

	inline Scene* GetScene() { return Scene::currentScene; }

	virtual void Start();
	virtual void Update();
	virtual void OnCollision(Collision* collision);
	virtual void OnTriggerCollision(Collision* collision);
};