#pragma once
#include "GLCall.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "GameObject.h"
#include "Color.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer
{
private:
	Camera *camera;
	glm::mat4 proj;
public:
	Color backgroundColor;

	Renderer();
	Renderer(Camera* camera);

	void Draw(const VertexArray& vs, const IndexBuffer& ib, const Shader& shader) const;

	void Clear() const;
	void SetProjMat4(glm::mat4 mat4);

	inline Camera* GetCamera() { return camera; }
	inline glm::mat4 GetProjMat4() const { return proj; }
};