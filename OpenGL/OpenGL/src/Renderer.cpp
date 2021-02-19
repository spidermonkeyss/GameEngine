#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::Renderer(Camera* camera)
	:camera(camera)
{
	proj = glm::ortho(-camera->GetWidthView(), camera->GetWidthView(), -camera->GetWidthView() / camera->GetAspectRatio(), camera->GetWidthView() / camera->GetAspectRatio(), -1.0f, 1.0f);
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer& ib, const Shader & shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetDataType(), nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a));
	// 0.14f, 0.5f, 0.85f, 1.0f
}

void Renderer::SetProjMat4(glm::mat4 mat4)
{
	proj = mat4;
}
