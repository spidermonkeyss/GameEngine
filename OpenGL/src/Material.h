#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Color.h"

class Material
{
private:
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Texture> texture;

	unsigned int fileID;
public:
	Color shader_color;
	
	Material();
	Material(unsigned int fileID);
	Material(std::unique_ptr<Shader> shader_i);
	Material(std::unique_ptr<Shader> shader_i, unsigned int fileID);
	Material(std::unique_ptr<Shader> shader, std::unique_ptr<Texture> texture);
	Material(std::unique_ptr<Shader> shader, std::unique_ptr<Texture> texture, unsigned int fileID);
	~Material();
	
	void SetShader(std::unique_ptr<Shader> shader_i);
	void SetTexture(std::unique_ptr<Texture> texture_i);

	inline Shader* GetShader() const { return shader.get(); }
	inline Texture* GetTexture() const { return texture.get(); }
	inline unsigned int GetFileID() const { return fileID; }
};