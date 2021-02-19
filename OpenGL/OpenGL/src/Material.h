#pragma once

#include "Shader.h"
#include "Texture.h"

class Material
{
private:
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Texture> texture;
public:
	Material();
	Material(std::unique_ptr<Shader> shader_i);
	Material(std::unique_ptr<Shader> shader, std::unique_ptr<Texture> texture);
	~Material();
	
	void SetShader(std::unique_ptr<Shader> shader_i);
	void SetTexture(std::unique_ptr<Texture> texture_i);

	inline Shader* GetShader() const { return shader.get(); }
	inline Texture* GetTexture() const { return texture.get(); }
};