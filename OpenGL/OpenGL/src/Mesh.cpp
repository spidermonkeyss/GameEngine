#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>

Mesh::Mesh()
	:material(nullptr), enabled(true)
{
	verticies = new float[0];
	indices = new unsigned int[0];
}

Mesh::~Mesh()
{
	delete[] verticies;
	delete[] indices;
}

void Mesh::ImportModelFromTxtFile(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string vertexString = "";
	std::string indexString = "";
	std::string line = "";
	int vertex = 0;
	while (getline(stream, line))
	{
		if (line.find("#") == std::string::npos)
		{
			if (vertex == 0)
				vertexString += line;
			else
				indexString += line;
		}
		else if (line.find("#vertex") != std::string::npos)
			vertex = 0;
		else if (line.find("#index") != std::string::npos)
			vertex = 1;
	}

	std::vector<float> vertexVec;
	std::stringstream s_streamv(vertexString);
	while (s_streamv.good())
	{
		std::string substr = "";
		getline(s_streamv, substr, ',');//get first string delimited by comma
		char* dataPointChar = new char[substr.size() + 1];
		int count = 0;
		for (int i = 0; i < substr.size(); i++)
		{
			dataPointChar[i] = substr[i];
			count++;
		}
		dataPointChar[count] = '\0';
		float dataPoint = 0;
		dataPoint = strtof(dataPointChar, NULL);
		vertexVec.push_back(dataPoint);
		delete[] dataPointChar;
	}

	std::vector<unsigned int> indexVec;
	std::stringstream s_streami(indexString);
	while (s_streami.good())
	{
		std::string substr = "";
		getline(s_streami, substr, ',');//get first string delimited by comma
		char* dataPointChar = new char[substr.size() + 1];
		int count = 0;
		for (int i = 0; i < substr.size(); i++)
		{
			dataPointChar[i] = substr[i];
			count++;
		}
		dataPointChar[count] = '\0';
		unsigned int dataPoint = 0;
		int tempInt = 0;
		tempInt = std::stoi(dataPointChar, NULL);
		dataPoint = tempInt;
		//dataPoint = strtof(dataPointChar, NULL);
		indexVec.push_back(dataPoint);
		delete[] dataPointChar;
	}

	//float* verticies = new float[vertexVec.size()];
	verticies = new float[vertexVec.size()];
	for (int i = 0; i < vertexVec.size(); i++)
		verticies[i] = vertexVec[i];

	//unsigned int* indices = new unsigned int[indexVec.size()];
	indices = new unsigned int[indexVec.size()];
	for (int i = 0; i < indexVec.size(); i++)
		indices[i] = indexVec[i];

	vertexCount = vertexVec.size();
	vertexSize = 4;
	indexCount = indexVec.size();
	
	CreateGpuBuffers();

	/*
	vertexBuffer.GenBuffer(verticies, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);//positions attribute
	layout.Push<float>(2);//texture coords
	vertexArray.AddBuffer(vertexBuffer, layout);

	indexBuffer.BufferData(indices, indexVec.size());
	*/

	/*
	std::cout << std::endl;

	for (int i = 0; i < vertexVec.size(); i++)
		std::cout << verticies[i] << std::endl;

	std::cout << std::endl;

	for (int i = 0; i < indexVec.size(); i++)
		std::cout << indices[i] << std::endl;
	*/

	//delete[] verticies;
	//delete[] indices;
}

void Mesh::CreateGpuBuffers()
{
	vertexBuffer.GenBuffer(verticies, vertexCount * vertexSize * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);//positions attribute
	layout.Push<float>(2);//texture coords
	vertexArray.AddBuffer(vertexBuffer, layout);

	indexBuffer.BufferData(indices, indexCount);
}

void Mesh::SetMaterial(std::unique_ptr<Material> i_material)
{
	material = std::move(i_material);
}