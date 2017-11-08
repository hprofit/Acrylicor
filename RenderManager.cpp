#include "RenderManager.h"
#include "Matrix4x4.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include <glew.h>
#include <fstream>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

RenderManager::RenderManager()
{}

RenderManager::~RenderManager()
{
	for (auto comp : m_shaderPrograms) {
		if (comp.second)
			delete comp.second;
	}
	m_shaderPrograms.clear();
}

String RenderManager::LoadTextFile(String fname)
{
	String out, line;
	std::ifstream in(fname);
	std::getline(in, line);
	while (in) {
		out += line + "\n";
		std::getline(in, line);
	}
	return out;
}

void RenderManager::_RenderSprite(SpriteComponent * sComp)
{
	glEnableVertexAttribArray(m_currentProgram->GetAttribute("position"));
	glBindBuffer(GL_ARRAY_BUFFER, sComp->GetMesh().GetVertexBuffer());
	glVertexAttribPointer(m_currentProgram->GetAttribute("position"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0); // <- load it to memory

	glEnableVertexAttribArray(m_currentProgram->GetAttribute("texture_coord"));
	glBindBuffer(GL_ARRAY_BUFFER, sComp->GetMesh().GetTextCoordBuffer());
	glVertexAttribPointer(m_currentProgram->GetAttribute("texture_coord"), 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0); // <- load it to memory

	glUniform2f(m_currentProgram->GetUniform("frame_offset"), sComp->GetFrameVOffset(), sComp->GetFrameUOffset());
	glUniform2f(m_currentProgram->GetUniform("frame_size"), sComp->FrameWidth(), sComp->FrameHeight());

	glUniform1f(m_currentProgram->GetUniform("tile_x"), sComp->TileX());
	glUniform1f(m_currentProgram->GetUniform("tile_y"), sComp->TileY());

	Vector3D color = sComp->GetColor();
	glUniform4f(m_currentProgram->GetUniform("color"), color[0], color[1], color[2], color[3]);

	if (sComp->TextureHasAlpha()) {
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.4f);
		glEnable(GL_BLEND);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else {
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_DEPTH_TEST);
	}

	// select the texture to use
	glBindTexture(GL_TEXTURE_2D, sComp->GetTextureBuffer());

	// draw the mesh
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sComp->GetMesh().GetFaceBuffer());
	glDrawElements(GL_TRIANGLES, 3 * sComp->GetMesh().faceCount(), GL_UNSIGNED_INT, 0);
}

void RenderManager::_RenderScrollingSprite(ScrollingSpriteComponent * sComp)
{
	glUniform1f(m_currentProgram->GetUniform("scroll_offset_x"), sComp->U());
	glUniform1f(m_currentProgram->GetUniform("scroll_offset_y"), sComp->V());
	
	_RenderSprite(sComp);
}

void RenderManager::_RenderGameObject(GameObject & gameObject)
{
	// Only attempt to draw if the game object has a sprite component and transform component
	if (!gameObject.Has(CT_TRANSFORM) || (!gameObject.Has(CT_SPRITE) && !gameObject.Has(CT_SCROLLING_SPRITE)))
		return;

	Matrix4x4 M = static_cast<TransformComponent*>(gameObject.Get(CT_TRANSFORM))->GetModelTransform();
	Matrix4x4 N = Matrix4x4::Transpose3x3(Matrix4x4::Inverse3x3(M));
	glUniformMatrix4fv(m_currentProgram->GetUniform("model_matrix"), 1, true, (float*)M);
	glUniformMatrix4fv(m_currentProgram->GetUniform("normal_matrix"), 1, true, (float*)N);

	// set shader attributes
	if(gameObject.Has(CT_SPRITE))
		_RenderSprite(static_cast<SpriteComponent*>(gameObject.Get(CT_SPRITE)));
	else if (gameObject.Has(CT_SCROLLING_SPRITE))
		_RenderScrollingSprite(static_cast<ScrollingSpriteComponent*>(gameObject.Get(CT_SCROLLING_SPRITE)));
}

void RenderManager::_SelectShaderProgram(GameObject & gameObject)
{
	String shader = "";

	if (gameObject.Has(CT_SPRITE))
		shader = static_cast<SpriteComponent*>(gameObject.Get(CT_SPRITE))->Shader();
	else if (gameObject.Has(CT_SCROLLING_SPRITE))
		shader = static_cast<ScrollingSpriteComponent*>(gameObject.Get(CT_SCROLLING_SPRITE))->Shader();

	SelectShaderProgram(shader.compare("") == 0 ? "default" : shader);
}

bool RenderManager::Init()
{
	// GLEW: get function bindings (if possible)
	glewInit();
	if (!GLEW_VERSION_2_0) {
		std::cout << "Needs OpenGL version 2.0 or better" << std::endl;
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

void RenderManager::RenderGameObject(GameObject & gameObject)
{
	_SelectShaderProgram(gameObject);
	glUseProgram(m_currentProgram->GetProgram());
	Matrix4x4 P = Matrix4x4::Perspective(80.0f, 1.0f, 0.1f);
	glUniformMatrix4fv(m_currentProgram->GetUniform("persp_matrix"), 1, true, (float*)&P);
	Matrix4x4 V = Matrix4x4::Scale(1.0f);
	glUniformMatrix4fv(m_currentProgram->GetUniform("pview_matrix"), 1, true, (float*)&V);

	_RenderGameObject(gameObject);
}

void RenderManager::RenderGameObject(GameObject & camera, GameObject & gameObject)
{
	if (!camera.Has(CT_CAMERA) || gameObject.Has(CT_CAMERA))
		return;
	CameraComponent * cComp = static_cast<CameraComponent*>(camera.Get(CT_CAMERA));
	_SelectShaderProgram(gameObject);
	glUseProgram(m_currentProgram->GetProgram());
	glUniformMatrix4fv(m_currentProgram->GetUniform("persp_matrix"), 1, true, (float*)cComp->GetPerspectiveMatrix());
	glUniformMatrix4fv(m_currentProgram->GetUniform("view_matrix"), 1, true, (float*)cComp->GetViewMatrix());

	_RenderGameObject(gameObject);
}

void RenderManager::FrameEnd()
{
}

#pragma region Shaders
void RenderManager::LoadShaderProgram(String fileName)
{
	try {
		std::ifstream i(fileName);
		json j;
		i >> j;

		if (j.is_object()) {
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				String programName = it.key();
				ShaderProgram * program = CreateShaderProgram(programName);
				Shader * vShader = CreateVertexShaderFromFile(j[programName]["vertex"]);
				Shader * fShader = CreateFragmentShaderFromFile(j[programName]["fragment"]);

				program->AttachShader(*vShader);
				program->AttachShader(*fShader);
				program->LinkShaders();

				if (j[programName]["uniforms"].is_array()) {
					int unisLen = j[programName]["uniforms"].size();
					for (int i = 0; i < unisLen; i++) {
						program->AddUniform(j[programName]["uniforms"][i]);
					}
				}

				if (j[programName]["attributes"].is_array()) {
					int attrsLen = j[programName]["attributes"].size();
					for (int i = 0; i < attrsLen; i++) {
						program->AddAttribute(j[programName]["attributes"][i]);
					}
				}
			}
		}
	}
	catch (const json::parse_error& ex) {
		std::cerr << ex.what() << std::endl;
	}
}

ShaderProgram * RenderManager::GetShaderProgram(String programName)
{
	ShaderProgram * program = m_shaderPrograms[programName];
	return program;
}

ShaderProgram * RenderManager::CreateShaderProgram(String programName)
{
	ShaderProgram * program = m_shaderPrograms[programName];
	if (program)
		return program;

	program = new ShaderProgram();
	if (program)
		m_shaderPrograms[programName] = program;

	return program;
}

Shader * RenderManager::CreateVertexShader(String vertexShaderText)
{
	return new Shader(vertexShaderText, VERTEX_SHADER);
}

Shader * RenderManager::CreateVertexShaderFromFile(String fileName)
{
	return CreateVertexShader(LoadTextFile(fileName));
}

Shader * RenderManager::CreateFragmentShader(String fragmentShaderText)
{
	return new Shader(fragmentShaderText, FRAGMENT_SHADER);

}

Shader * RenderManager::CreateFragmentShaderFromFile(String fileName)
{
	return CreateFragmentShader(LoadTextFile(fileName));
}

void RenderManager::SelectShaderProgram(String programName)
{
	if (!m_shaderPrograms[programName]) {
		std::cout << "Shader program \"" << programName.c_str() << "\" does not exist." << std::endl;
		return;
	}
	m_currentProgram = m_shaderPrograms[programName];
}
#pragma endregion

GLuint RenderManager::CreateTextureBuffer(const STB_Surface * const stbSurface)
{
	GLuint textureBuffer;
	glGenTextures(1, &textureBuffer);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(GL_TEXTURE_2D, 0,
		stbSurface->hasAlpha ? GL_RGBA : GL_RGB,
		stbSurface->width, stbSurface->height, 0,
		stbSurface->hasAlpha ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE, stbSurface->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return textureBuffer;
}
