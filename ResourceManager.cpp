#include "ResourceManager.h"
#include "stdio.h"
#include "stb_image.h"

ResourceManager::ResourceManager(){}

ResourceManager::~ResourceManager()
{
	for (auto comp : m_meshes) {
		if (comp.second)
			delete comp.second;
	}
	m_meshes.clear();

	for (auto comp : m_textures) {
		if (comp.second)
			stbi_image_free(comp.second->data);
	}
	m_textures.clear();
}

Mesh * ResourceManager::LoadMesh(const char * meshName)
{
	Mesh * mesh = m_meshes[meshName];
	
	if (mesh)
		return mesh;
	
	mesh = new Mesh();
	if (mesh)
		m_meshes[meshName] = mesh;
	
	return mesh;
}

STB_Surface * ResourceManager::LoadTexture(const char * fileName, const char * textureName)
{
	STB_Surface * texture = m_textures[textureName];

	if (texture)
		return texture;

	texture = new STB_Surface();
	texture->data = stbi_load(fileName, &texture->width, &texture->height, &texture->channels, STBI_rgb_alpha);

	texture = new STB_Surface();
	if (texture)
		m_textures[textureName] = texture;

	return texture;
}
