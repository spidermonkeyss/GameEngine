#pragma once

#include "Scene.h"

namespace YAML
{
	class Node;
};

class SceneSerializer 
{
private:
	static void UpdateFilePathIDs(const std::string & filePath, unsigned int id);
public:
	SceneSerializer();

	void SerializeYAML(Scene * scene, const std::string& filePath);
	void DeserializeYAML(Scene * scene, const std::string& filePath);

	//These need to be called when they enter the project or when created in editor. Do not call on scene serialize
	static void SerializeMesh(const std::string& filePath, Mesh* mesh);
	static void SerializeMaterial(const std::string& filePath, Material* material);


	static void SerializeCollider();
	static void SerializeRigidbody();

	static std::unique_ptr<Mesh> DeSerializeMesh(unsigned int meshID, YAML::Node idFilePaths);
	static std::unique_ptr<Material> DeSerializeMaterial(unsigned int matID, YAML::Node idFilePaths);
};