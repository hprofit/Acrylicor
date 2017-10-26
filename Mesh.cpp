#include "Mesh.h"
#include "Matrix4x4.h"

Mesh::Mesh() {}

Mesh::~Mesh()
{
	// delete the vertex, normal, texture coordinate, and face buffers
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_normalBuffer);
	glDeleteBuffers(1, &m_faceBuffer);
	glDeleteBuffers(1, &m_textCoordBuffer);

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
	int vertexBufferSize = sizeof(Vector3D) * vertexCount();
	for (int n = 0; n < vertexCount(); ++n)
		m_normals.push_back(Vector3D(0, 0, 1, 0));
	
#pragma region Vertex Buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		vertexBufferSize,
		vertexArray(), GL_STATIC_DRAW);
#pragma endregion

#pragma region Normal Buffer
	glGenBuffers(1, &m_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, 
		vertexBufferSize, 
		normalArray(), GL_STATIC_DRAW);
#pragma endregion

#pragma region Face Buffer
	glGenBuffers(1, &m_faceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_faceBuffer);
	int faceBufferSize = sizeof(Face)*faceCount();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		faceBufferSize, 
		faceArray(), GL_STATIC_DRAW);
#pragma endregion

#pragma region Texture Coordinate Buffer
	// TODO: This is for a plane only
	glGenBuffers(1, &m_textCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_textCoordBuffer);

	// These need to mirror the triangle coordinates
	GLfloat texcoord[] = {
		.0f, .0f,
		1.0f, 0.0f,
		.0f, 1.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		.0f, 1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * vertexCount(), texcoord, GL_STATIC_DRAW);
	//delete[] texcoord;
#pragma endregion
}

int Mesh::vertexCount() const
{
	return m_vertices.size();
}

Vector3D * Mesh::vertexArray()
{
	return &(m_vertices[0]);
}

const GLuint & Mesh::GetVertexBuffer() const
{
	return m_vertexBuffer;
}

Vector3D * Mesh::normalArray()
{
	return &(m_normals[0]);
}

const GLuint & Mesh::GetNormalBuffer() const
{
	return m_normalBuffer;
}

int Mesh::faceCount() const
{
	return m_faces.size();
}

Face * Mesh::faceArray()
{
	return  &(m_faces[0]);
}

const GLuint & Mesh::GetFaceBuffer() const
{
	return m_faceBuffer;
}

const GLuint & Mesh::GetTextCoordBuffer() const
{
	return m_textCoordBuffer;
}
