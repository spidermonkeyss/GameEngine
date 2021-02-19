#pragma once

#include "Scene.h"

class SceneSerializer 
{
private:
	Scene* scene;
public:
	SceneSerializer(Scene * scene);

	void SerializeYAML(const std::string& filePath);
	void DeserializeYAML(const std::string& filePath);
};