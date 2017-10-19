#include "Mesh.h"

Mesh::Mesh() {}

Mesh::~Mesh()
{
	m_vertices.clear();
	m_normals.clear();
	m_faces.clear();
}

void Mesh::AddTriangle(Vector3D p1, Vector3D p2, Vector3D p3)
{
	unsigned int idx0 = m_vertices.size(), 
		idx1 = idx0 + 1, 
		idx2 = idx0 + 2;
	m_vertices.push_back(p1);
	m_vertices.push_back(p2);
	m_vertices.push_back(p3);

	m_faces.push_back(Face(idx0, idx1, idx2));
}

void Mesh::AddTriangle(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z)
{
	AddTriangle(
		Vector3D(p1x, p1y, p1z),
		Vector3D(p2x, p2y, p2z),
		Vector3D(p3x, p3y, p3z)
	);
}

void Mesh::FinishMesh()
{
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vector3D) * vertextCount(),
		vertexArray(), GL_STATIC_DRAW);
}

int Mesh::vertextCount() const
{
	return m_vertices.size();
}

Vector3D * Mesh::vertexArray()
{
	return &(m_vertices[0]);
}

Vector3D * Mesh::normalArray()
{
	return &(m_normals[0]);
}

int Mesh::faceCount() const
{
	return m_faces.size();
}

Face * Mesh::faceArray()
{
	return  &(m_faces[0]);
}
