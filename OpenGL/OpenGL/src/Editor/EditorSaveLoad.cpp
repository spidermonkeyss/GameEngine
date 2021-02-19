#include "EditorSaveLoad.h"

#include "Camera.h"
#include "SceneSerializer.h"

void EditorSaveLoad::SaveScene(Scene * scene)
{
	std::cout << "Saving Scene" << std::endl;
	
	SceneSerializer ser(scene);
	ser.SerializeYAML("saves/scene.scene");

	/*
	std::fstream scenefile("saves/scene.scene", std::ios::out | std::ios::binary);
	if (scenefile.is_open())
	{
		scenefile.seekg(0, std::ios::beg);

		std::string fileStr = "";

		fileStr += Serializer::SerializeCamera(scene->camera.get());
		
		fileStr += "END\0";

		scenefile << &fileStr[0];
		scenefile.close();
	}
	else
		std::cout << "couldn't open file" << std::endl;

	std::ifstream read("saves/scene.scene", std::ios::in | std::ios::binary);
	if (read.is_open())
	{
		std::streampos size;
		read.seekg(0, std::ios::end);
		size = read.tellg();
		char* fileChar = new char[size];
		read.seekg(0, std::ios::beg);
		read.read(fileChar, size);
		
		std::string str = "";
		for (int i = 0; i < size; i++)
			str += fileChar[i];

		std::cout << str << std::endl;

		read.close();
		
		delete[] fileChar;
	}
	*/
}