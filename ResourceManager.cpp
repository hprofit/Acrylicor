#include "ResourceManager.h"
#include "stdio.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
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
		if (comp.second) {
			stbi_image_free(comp.second->surface->data);
			delete comp.second->surface;
			delete comp.second;
		}
	}
	m_textures.clear();
}

Mesh * ResourceManager::LoadMesh(String meshName)
{
	Mesh * mesh = m_meshes[meshName];
	
	if (mesh)
		return mesh;
	
	mesh = new Mesh();
	if (mesh)
		m_meshes[meshName] = mesh;
	
	return mesh;
}

Mesh * ResourceManager::GetMesh(String meshName)
{
	Mesh * mesh = m_meshes[meshName];

	if (mesh)
		return mesh;
	else {
		std::cerr << meshName << " has not yet been created." << std::endl;
		return nullptr;
	}
}

GLuint ResourceManager::LoadTexture(String fileName, String textureName)
{
	//TextureBuffer textureBuffer = m_textures[textureName];
	SurfaceTextureBuffer * stbuff = m_textures[textureName];

	//if (textureBuffer)
	//	return textureBuffer->second;
	if (stbuff)
		return stbuff->bufferId;

	STB_Surface * surface = new STB_Surface();
	if (surface) {
		//surface->data = stbi_load(fileName, &surface->width, &surface->height, &surface->channels, STBI_rgb_alpha);
		surface->data = stbi_load(fileName.c_str(), &surface->width, &surface->height, &surface->channels, STBI_rgb);

		if (!surface->data) {
			std::cerr << "Failed to read file: " << fileName << std::endl;
			return -1;
		}
		GLuint bufferId = LoadTextureBuffer(surface);
		//m_textures[textureName] = &std::make_pair(surface, bufferId);

		m_textures[textureName] = new SurfaceTextureBuffer(surface, bufferId);
		return bufferId;
	}
	else {
		std::cerr << "Failed to create texture: " << textureName << " : " << fileName << std::endl;
		return -1;
	}
}

GLuint ResourceManager::GetTexture(const String textureName)
{
	//TextureBuffer textureBuffer = m_textures[textureName];
	SurfaceTextureBuffer * stbuff = m_textures[textureName];

	//if (textureBuffer)
	//	return textureBuffer->second;
	if (stbuff)
		return stbuff->bufferId;
	else {
		std::cerr << textureName << " has not yet been created." << std::endl;
		return -1;
	}
}

void ResourceManager::UnloadMesh(String meshName)
{
	if (m_meshes[meshName]) {
		delete m_meshes[meshName];
		m_meshes.erase(meshName);
	}
}

void ResourceManager::UnloadTexture(String textureName)
{
	if (m_textures[textureName]) {
		//stbi_image_free(m_textures[textureName]->first->data);
		//delete m_textures[textureName]->first;
		//delete m_textures[textureName];

		stbi_image_free(m_textures[textureName]->surface->data);
		delete m_textures[textureName]->surface;
		delete m_textures[textureName];

		m_textures.erase(textureName);
	}
}

GLuint ResourceManager::LoadTextureBuffer(const STB_Surface * const stbSurface)
{
	GLuint textureBuffer;
	glGenTextures(1, &textureBuffer);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, stbSurface->width, stbSurface->height, 0, GL_RGB, GL_UNSIGNED_BYTE, stbSurface->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return textureBuffer;
}
