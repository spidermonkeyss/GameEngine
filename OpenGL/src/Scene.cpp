#include "Scene.h"

#include "DynamicObject.h"

Scene* Scene::currentScene;

Scene::Scene()
	:gameObjects(), renderer(nullptr), physics(nullptr), camera(nullptr)
{
}

Scene::Scene(Renderer * renderer_i, Physics* physics)
	: gameObjects(), renderer(renderer_i), physics(physics)
{
}

Scene::Scene(Renderer * renderer_i, Physics * physics, Camera * camera)
	: gameObjects(), renderer(renderer_i), physics(physics), camera(camera)
{
}

Scene::~Scene()
{
}

void Scene::OnStart()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		//get scripts
		//std::vector<DynamicObject *> objectScripts = gameObjects[i]->dynamicObjectScripts;
		for (int j = 0; j < gameObjects[i]->dynamicObjectScripts.size(); j++)
		{
			gameObjects[i]->dynamicObjectScripts[j]->Start();
			dynamicObjectScripts.push_back(gameObjects[i]->dynamicObjectScripts[j].get());
		}

		//get colliders
		if (gameObjects[i]->GetCollider() != nullptr)
			colliders.push_back(gameObjects[i]->GetCollider());

		//get rigidbodys
		if (gameObjects[i]->GetRigidbody() != nullptr)
			rigidbodys.push_back(gameObjects[i]->GetRigidbody());
	}
	SetSceneHierarchy();
}

void Scene::OnUpdate()
{
	for (int i = 0; i < dynamicObjectScripts.size(); i++)
		dynamicObjectScripts[i]->Update();
	if (physics->doGravtity)
	{
		for (int i = 0; i < rigidbodys.size(); i++)
			rigidbodys[i]->Update();
	}
}

void Scene::OnCheckCollision()
{
	if (!DoCollisions)
		return;
	for (int i = colliders.size() - 1; i > 0 ; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (colliders[i]->enabled && colliders[j]->enabled)
			{
				if (colliders[i]->topGameObject != colliders[j]->topGameObject)
				{
					if (colliders[i]->CheckCollision(colliders[j]))
					{
						Collision col = colliders[i]->GenerateCollision(colliders[j]);
						Collision col2 = colliders[j]->GenerateCollision(colliders[i]);
						//Non trigger checks
						if (!colliders[i]->isTrigger && !colliders[j]->isTrigger)
						{
							//Physics collision
							if (colliders[i]->topGameObject->GetRigidbody() != nullptr)
								colliders[i]->topGameObject->GetRigidbody()->OnCollision(&col);
							if (colliders[j]->topGameObject->GetRigidbody() != nullptr)
								colliders[j]->topGameObject->GetRigidbody()->OnCollision(&col2);

							//Script collision
							for (int m = 0; m < colliders[i]->topGameObject->dynamicObjectScripts.size(); m++)
								colliders[i]->topGameObject->dynamicObjectScripts[m]->OnCollision(&col);
							for (int m = 0; m < colliders[j]->topGameObject->dynamicObjectScripts.size(); m++)
								colliders[j]->topGameObject->dynamicObjectScripts[m]->OnCollision(&col2);
						}
						//Trigger checks
						else
						{
							//Script trigger collision
							for (int m = 0; m < colliders[i]->topGameObject->dynamicObjectScripts.size(); m++)
								colliders[i]->topGameObject->dynamicObjectScripts[m]->OnTriggerCollision(&col);
							for (int m = 0; m < colliders[j]->topGameObject->dynamicObjectScripts.size(); m++)
								colliders[j]->topGameObject->dynamicObjectScripts[m]->OnTriggerCollision(&col2);
						}
					}
				}
			}
		}
	}
}

void Scene::RenderScene()
{
	//glm::mat4 mvp;
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetMesh() != nullptr)
		{
			if (gameObjects[i]->GetMesh()->enabled)
			{
				gameObjects[i]->GetMesh()->GetMaterial()->GetShader()->Bind();
				glm::mat4 model = gameObjects[i]->GetTransfrom()->GetMat4();

				mvp = renderer->GetProjMat4() * glm::inverse(renderer->GetCamera()->GetGameObject()->GetTransfrom()->GetMat4()) * model;
				gameObjects[i]->GetMesh()->GetMaterial()->GetShader()->SetUniformMat4f("u_MVP", mvp);
				renderer->Draw(*gameObjects[i]->GetMesh()->GetVertexArray(), *gameObjects[i]->GetMesh()->GetIndexBuffer(), *gameObjects[i]->GetMesh()->GetMaterial()->GetShader());
			}
		}
	}
}

void Scene::UnloadCurrentScene()
{
	currentScene = nullptr;
	gameObjects.clear();
	topGameObjects.clear();
	dynamicObjectScripts.clear();
	colliders.clear();
	rigidbodys.clear();
}

void Scene::SetSceneHierarchy()
{
	topGameObjects.clear();
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetTransfrom()->GetParent() == nullptr)
			topGameObjects.push_back(gameObjects[i].get());
	}
}

void Scene::AddGameObjectToScene(std::unique_ptr<GameObject> gameObject)
{
	gameObjects.push_back(std::move(gameObject));
}
