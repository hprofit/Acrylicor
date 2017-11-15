#include "ResourceManager.h"
#include "RenderManager.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include "JsonReader.h"
#include "json.hpp"
#include "AcryDebugLine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using json = nlohmann::json;

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


void ResourceManager::CreateDebugLine()
{
	m_debugLine = new AcryDebugLine(.5f, .0f, .0f, COLOR::WHITE, -.5f, .0f, .0f, COLOR::WHITE);
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

void ResourceManager::UnloadMesh(String meshName)
{
	if (m_meshes[meshName]) {
		delete m_meshes[meshName];
		m_meshes.erase(meshName);
	}
}


SurfaceTextureBuffer * ResourceManager::LoadTexture(String textureName, String fileName, TextureInfo info)
{
	SurfaceTextureBuffer * stbuff = m_textures[textureName];

	if (stbuff)
		return stbuff;

	STB_Surface * surface = new STB_Surface();
	if (surface) {
		surface->hasAlpha = info.hasAlpha;
		surface->data = stbi_load(fileName.c_str(), 
			&surface->width, &surface->height, 
			&surface->channels, 
			info.hasAlpha ? STBI_rgb_alpha : STBI_rgb);

		if (!surface->data) {
			std::cerr << "Failed to read file: " << fileName << std::endl;
			return nullptr;
		}
		surface->frameWidth = info.frameWidth / surface->width;
		surface->frameHeight = info.frameHeight / surface->height;
		surface->rows = info.rows;
		surface->columns = info.cols;
		GLuint bufferId = RenderManager::GetInstance().CreateTextureBuffer(surface);

		stbuff = new SurfaceTextureBuffer(surface, bufferId);
		m_textures[textureName] = stbuff;
		return stbuff;
	}
	else {
		std::cerr << "Failed to create texture: " << textureName << " : " << fileName << std::endl;
		return nullptr;
	}
}

SurfaceTextureBuffer * ResourceManager::GetTexture(const String textureName)
{
	SurfaceTextureBuffer * stbuff = m_textures[textureName];

	if (stbuff)
		return stbuff;
	else {
		std::cerr << textureName << " has not yet been created." << std::endl;
		return nullptr;
	}
}

void ResourceManager::UnloadTexture(String textureName)
{
	if (m_textures[textureName]) {
		stbi_image_free(m_textures[textureName]->surface->data);
		delete m_textures[textureName]->surface;
		delete m_textures[textureName];

		m_textures.erase(textureName);
	}
}

void ResourceManager::LoadTexturesFromFile(String fileName)
{
	try {
		json j = AcryJson::OpenJsonFile(fileName);

		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				String key = it.key();
				TextureInfo info;
				info.frameWidth = AcryJson::ParseFloat(j, key, "frameWidth");
				info.frameHeight = AcryJson::ParseFloat(j, key, "frameHeight");
				info.rows = AcryJson::ParseInt(j, key, "rows");
				info.cols = AcryJson::ParseInt(j, key, "columns");
				info.hasAlpha = j[key]["alpha"];
				LoadTexture(key, j[key]["filename"], info);
			}
		}
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}


void ResourceManager::UnloadAll()
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
