#include "RenderManager.h"
#include <stdio.h>
#include <glew.h>

#include "Matrix4x4.h"

#define MAX_SHADER_PROGRAMS 8

RenderManager::RenderManager()
{}

RenderManager::~RenderManager()
{
	m_shaderPrograms.clear();
}

bool RenderManager::Init()
{
	// GLEW: get function bindings (if possible)
	glewInit();
	if (!GLEW_VERSION_2_0) {
		printf("needs OpenGL version 2.0 or better");
		return false;
	}
	return true;
}

void RenderManager::FrameStart()
{
	// clear frame buffer and z-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void RenderManager::RenderGameObject(const Camera& camera, const GameObject& gameObject)
{
	// Only attempt to draw if the game object has a sprite component
	//if (!gameObject || !gameObject.GetSpriteComponent())
	//	return;
	
	DefaultShaderProgram * program = dynamic_cast<DefaultShaderProgram*>(m_currentProgram);

	glUseProgram(m_currentProgram->GetProgram());
	Matrix4x4 M = gameObject.GetTransformComponent()->GetModelTransform();
	Matrix4x4 N = Matrix4x4::Transpose3x3(Matrix4x4::Inverse3x3(M));
	glUniformMatrix4fv(program->umodel_matrix, 1, true, (float*)&M);
	glUniformMatrix4fv(program->unormal_matrix, 1, true, (float*)&N);

	// Generate color for each object
	glUniform4f(program->ucolor, 1, 0, 1, 1);

	// set shader attributes
	glEnableVertexAttribArray(program->aposition);
	glBindBuffer(GL_ARRAY_BUFFER, gameObject.GetSpriteComponent()->GetMesh().GetVertexBuffer());
	glVertexAttribPointer(program->aposition, 4, GL_FLOAT, false, 0, 0); // <- load it to memory
	glEnableVertexAttribArray(program->aposition);

	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

void RenderManager::FrameEnd()
{
}

ShaderProgram * RenderManager::GetShaderProgram(const char * programName)
{
	ShaderProgram * program = m_shaderPrograms[programName];
	return program;
}

ShaderProgram * RenderManager::CreateShaderProgram(const char * programName)
{
	ShaderProgram * program = m_shaderPrograms[programName];
	if (program)
		return program;

	program = new ShaderProgram();
	if (program)
		m_shaderPrograms[programName] = program;

	return program;
}

void RenderManager::CreateVertexShader(const char * vertexShaderText)
{

}

void RenderManager::CreateFragmentShader(const char * fragmentShaderText)
{

}

void RenderManager::SelectShaderProgram(const char * programName)
{
	if (!m_shaderPrograms[programName]) {
		printf("Shader program \"%s\" does not exist.", programName);
		return;
	}
	m_currentProgram = m_shaderPrograms[programName];
}
