#include "RenderManager.h"
#include "Matrix4x4.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <stdio.h>
#include <glew.h>

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
	glEnable(GL_DEPTH_TEST); // GL_BLEND_TEST <- TODO: for alpha
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

void RenderManager::RenderGameObject(GameObject & gameObject)
{
	// Only attempt to draw if the game object has a sprite component and transform component
	if (!gameObject.Has(CT_TRANSFORM) || !gameObject.Has(CT_SPRITE))
		return;

	glUseProgram(m_currentProgram->GetProgram());
	Matrix4x4 P = Matrix4x4::Perspective(80.0f, 1.0f, 0.1f);
	glUniformMatrix4fv(m_currentProgram->GetUniform("persp_matrix"), 1, true, (float*)&P);
	Matrix4x4 V = Matrix4x4::Scale(1.0f);
	glUniformMatrix4fv(m_currentProgram->GetUniform("pview_matrix"), 1, true, (float*)&V);

	Matrix4x4 M = static_cast<TransformComponent*>(gameObject.Get(CT_TRANSFORM))->GetModelTransform();
	Matrix4x4 N = Matrix4x4::Transpose3x3(Matrix4x4::Inverse3x3(M));
	glUniformMatrix4fv(m_currentProgram->GetUniform("model_matrix"), 1, true, (float*)&M);
	glUniformMatrix4fv(m_currentProgram->GetUniform("normal_matrix"), 1, true, (float*)&N);

	// Generate color for each object
	glUniform4f(m_currentProgram->GetUniform("color"), 1, 1, 1, 1);

	// set shader attributes
	glEnableVertexAttribArray(m_currentProgram->GetAttribute("position"));
	glBindBuffer(GL_ARRAY_BUFFER, static_cast<SpriteComponent*>(gameObject.Get(CT_SPRITE))->GetMesh().GetVertexBuffer());
	glVertexAttribPointer(m_currentProgram->GetAttribute("position"), 4, GL_FLOAT, false, 0, 0); // <- load it to memory
	glEnableVertexAttribArray(m_currentProgram->GetAttribute("position"));

	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

void RenderManager::RenderGameObject(const Camera& camera, GameObject& gameObject)
{
	// Only attempt to draw if the game object has a sprite component and transform component
	if (!gameObject.Has(CT_TRANSFORM) || !gameObject.Has(CT_SPRITE))
		return;

	glUseProgram(m_currentProgram->GetProgram());
	Matrix4x4 P = Matrix4x4::Perspective(80.0f, 1.0f, 0.1f);
	glUniformMatrix4fv(m_currentProgram->GetUniform("persp_matrix"), 1, true, (float*)&P);
	Matrix4x4 V = camera.GetViewMatrix();
	glUniformMatrix4fv(m_currentProgram->GetUniform("pview_matrix"), 1, true, (float*)&V);

	Matrix4x4 M = static_cast<TransformComponent*>(gameObject.Get(CT_TRANSFORM))->GetModelTransform();
	Matrix4x4 N = Matrix4x4::Transpose3x3(Matrix4x4::Inverse3x3(M));
	glUniformMatrix4fv(m_currentProgram->GetUniform("model_matrix"), 1, true, (float*)&M);
	glUniformMatrix4fv(m_currentProgram->GetUniform("normal_matrix"), 1, true, (float*)&N);

	// Generate color for each object
	glUniform4f(m_currentProgram->GetUniform("color"), 1, 1, 1, 1);

	// set shader attributes
	glEnableVertexAttribArray(m_currentProgram->GetAttribute("position"));
	glBindBuffer(GL_ARRAY_BUFFER, static_cast<SpriteComponent*>(gameObject.Get(CT_SPRITE))->GetMesh().GetVertexBuffer());
	glVertexAttribPointer(m_currentProgram->GetAttribute("position"), 4, GL_FLOAT, false, 0, 0); // <- load it to memory
	glEnableVertexAttribArray(m_currentProgram->GetAttribute("position"));

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

// TODO: Don't like
DefaultShaderProgram * RenderManager::CreateDefaultShaderProgram(const char * programName)
{
	DefaultShaderProgram * program = dynamic_cast<DefaultShaderProgram*>(m_shaderPrograms[programName]);
	if (program)
		return program;

	program = new DefaultShaderProgram();
	if (program)
		m_shaderPrograms[programName] = program;

	return program;
}

Shader * RenderManager::CreateVertexShader(const char * vertexShaderText)
{
	return new Shader(vertexShaderText, VERTEX_SHADER);
}

Shader * RenderManager::CreateFragmentShader(const char * fragmentShaderText)
{
	return new Shader(fragmentShaderText, FRAGMENT_SHADER);

}

void RenderManager::SelectShaderProgram(const char * programName)
{
	if (!m_shaderPrograms[programName]) {
		printf("Shader program \"%s\" does not exist.", programName);
		return;
	}
	m_currentProgram = m_shaderPrograms[programName];
}
