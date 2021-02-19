#include "GameObject.h"

#include "DynamicObject.h"

#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>

GameObject::GameObject()
	: mesh(nullptr), transform(), dynamicObjectScripts()
{
	GenerateID();
	transform.gameObject = this;
}

GameObject::GameObject(std::string name_i)
	: mesh(nullptr), transform(), dynamicObjectScripts()
{
	GenerateID();
	transform.gameObject = this;
	name = name_i;
}

void GameObject::GenerateID()
{
	id = std::rand() * std::rand() * std::rand() * std::rand();
}

void GameObject::LoadMesh(std::string meshfilePath)
{
	std::string modelFilePath = "";
	std::string materialFilePath = "";

	std::string shaderFilePath = "";
	std::string textureFilePath = "";

	std::ifstream meshFile(meshfilePath, std::ios::in | std::ios::binary);
	if (meshFile.is_open())
	{
		std::vector<std::string> strVec;
		std::string str;
		while (std::getline(meshFile, str))
			strVec.push_back(str);

		modelFilePath = strVec[0].substr(strVec[0].find(':') + 1, strVec[0].find('\r') - str.find(':') + 1);
		materialFilePath = strVec[1].substr(strVec[1].find(':'));
		
		meshFile.close();
	}
	
	std::unique_ptr<Shader> playerShader(new Shader(shaderFilePath));
	playerShader->Bind();
	std::unique_ptr<Texture> playerTexture(new Texture(textureFilePath));
	int slot = 0;
	playerTexture->Bind(slot);
	playerShader->SetUniform1i("u_Texture", slot);

	std::unique_ptr<Material> playerMaterial(new Material(std::move(playerShader), std::move(playerTexture)));

	std::unique_ptr<Mesh> playerMesh(new Mesh());
	playerMesh->ImportModelFromTxtFile(modelFilePath);
	playerMesh->SetMaterial(std::move(playerMaterial));
}

GameObject::~GameObject()
{
	std::cout << "Destructor:" << name << std::endl;
}

void GameObject::SetMesh(std::unique_ptr<Mesh> mesh_i)
{
	mesh = std::move(mesh_i);
}

void GameObject::SetTransformPosition(float x, float y, float z)
{
	transform.SetPosition(x,y,z);
}

void GameObject::SetTransformPosition(Vector3 vec)
{
	transform.SetPosition(vec);
}

void GameObject::AddScript(std::unique_ptr<DynamicObject> script)
{
	script->SetAttachedObject(this);
	dynamicObjectScripts.push_back(std::move(script));
}

void GameObject::SetCollider(std::unique_ptr<Collider> collider_i)
{
	collider = std::move(collider_i);
	collider->gameObject = this;
	collider->topGameObject = this;
	collider->SetScale();
}

void GameObject::SetRigidbody(std::unique_ptr<Rigidbody> rigidbody_i)
{
	rigidbody = std::move(rigidbody_i);
	rigidbody->gameObject = this;
}