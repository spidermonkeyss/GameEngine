#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Physics.h"

#include <vector>

class Scene
{
public:
	//these 4 are saved in the scene
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Physics> physics;
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<GameObject>> gameObjects;

	//these are for looping
	std::vector<GameObject *> topGameObjects;
	std::vector<DynamicObject *> dynamicObjectScripts;
	std::vector<Collider *> colliders;
	std::vector<Rigidbody *> rigidbodys;

	static Scene* currentScene;

	Scene();
	Scene(Renderer* renderer_i, Physics* physics);
	Scene(Renderer* renderer_i, Physics* physics, Camera* camera);
	~Scene();

	void OnStart();
	void OnUpdate();
	void OnCheckCollision();
	void RenderScene();

	void UnloadCurrentScene();

	void SetSceneHierarchy();

	bool DoCollisions = true;

	void AddGameObjectToScene(std::unique_ptr<GameObject> gameObject);
};