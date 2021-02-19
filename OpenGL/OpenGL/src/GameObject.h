#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "Collider.h"
#include "Rigidbody.h"

#include <string>
#include <vector>

class DynamicObject;

class GameObject
{
private:
	std::unique_ptr<Mesh> mesh;
	Mesh mesh2;
	Transform transform;
	std::unique_ptr<Collider> collider;
	std::unique_ptr<Rigidbody> rigidbody;

	//used for save files
	unsigned int id;
	void GenerateID();
	void LoadMesh(std::string meshfilePath);
public:
	std::string name;
	std::string mesh_FilePath;
	std::vector<std::unique_ptr<DynamicObject>> dynamicObjectScripts;
	
	GameObject();
	GameObject(std::string name);
	~GameObject();

	void SetMesh(std::unique_ptr<Mesh> mesh_i);
	void SetTransformPosition(float x, float y, float z);
	void SetTransformPosition(Vector3 vec);
	void AddScript(std::unique_ptr<DynamicObject> script);
	void SetCollider(std::unique_ptr<Collider> collider);
	void SetRigidbody(std::unique_ptr<Rigidbody> rigidbody);
	
	inline Mesh* GetMesh() { return mesh.get(); }
	Transform* GetTransfrom() { return &transform; }
	inline Collider* GetCollider() const { return collider.get(); }
	inline Rigidbody* GetRigidbody() const { return rigidbody.get(); }
	inline unsigned int GetID() const { return id; }
};