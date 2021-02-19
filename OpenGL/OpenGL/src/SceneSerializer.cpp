#include "SceneSerializer.h"

//#include "yaml-cpp/yaml.h"

#include <fstream>

SceneSerializer::SceneSerializer(Scene * scene)
	: scene(scene)
{
}

void SceneSerializer::SerializeYAML(const std::string& filePath)
{
	//YAML::Emitter out;
	//out << YAML::BeginMap;
	//out << YAML::Key << "Scene" << YAML::Value << "DefaultScene";
	//out << YAML::EndMap;
	//std::ofstream fout(filePath);
	//fout << out.c_str();
}

void SceneSerializer::DeserializeYAML(const std::string& filePath)
{
}
