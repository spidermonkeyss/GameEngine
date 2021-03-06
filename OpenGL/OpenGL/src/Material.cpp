#include "Material.h"

Material::Material()
	:shader(nullptr), texture(nullptr)
{
}

Material::Material(std::unique_ptr<Shader> shader_i)
	:texture(nullptr)
{
	shader = std::move(shader_i);
}

Material::Material(std::unique_ptr<Shader> i_shader, std::unique_ptr<Texture> i_texture)
{
	shader = std::move(i_shader);
	texture = std::move(i_texture);
}

Material::~Material()
{
}

void Material::SetShader(std::unique_ptr<Shader> shader_i)
{
	shader = std::move(shader_i);
}

void Material::SetTexture(std::unique_ptr<Texture> texture_i)
{
	texture = std::move(texture_i);
}
