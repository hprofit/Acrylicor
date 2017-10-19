#include "ResourceManager.h"
#include "stdio.h"
#include "SDL_surface.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	m_meshes.clear();
	//for (auto &it : m_vertices)
	//	SDL_FreeSurface(it.second);
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

//GLfloat * ResourceManager::LoadSurface(char * pFilePath)
//{
//	GLfloat * pVertices = m_vertices[pFilePath];
//
//	if (pVertices)
//		return pVertices;
//
//	pSurface = SDL_LoadBMP(pFilePath);
//	if (pSurface)
//		m_surfaces[pFilePath] = pSurface;
//
//	return NULL;
//}
