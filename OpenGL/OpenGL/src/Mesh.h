#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "Vector3.h"

#include <vector>

class Mesh
{
private:
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	std::unique_ptr<Material> material;
	
	float* verticies;
	unsigned int vertexCount;
	unsigned int vertexSize;

	unsigned int* indices;
	unsigned int indexCount;

	void CreateGpuBuffers();
public:
	Mesh();
	~Mesh();

	bool enabled;

	void ImportModelFromTxtFile(const std::string& filePath);
	void SetMaterial(std::unique_ptr<Material> i_material);

	inline VertexArray* GetVertexArray() { return &vertexArray; }
	inline IndexBuffer* GetIndexBuffer() { return &indexBuffer; }
	inline Material* GetMaterial() { return material.get(); }
};