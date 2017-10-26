// Necessary
#include <iostream>
#include "TestGameState.h"
#include "AcrylicorAPI.h"

// Don't like
#include "Mesh.h"

#include "RenderManager.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "SDL.h"

#include "GameObjectFactory.h"

static GameObject * sgpPlayer;

TestGameState::TestGameState()
{
}

TestGameState::~TestGameState()
{
}

void TestGameState::GameStateLoad(void)
{
#pragma region Shader Declaration
#pragma region Vertex Shader Declaration
	Shader * vShader = RenderManager::GetInstance().CreateVertexShader(
		"#version 130\n\
		attribute vec4 position;\
		attribute vec2 texture_coord;\
		\
		uniform mat4 persp_matrix;\
		uniform mat4 view_matrix;\
		uniform mat4 model_matrix;\
		uniform mat4 normal_matrix;\
		\
		out vec4 vcolor;\
		out vec2 vtexture_coord;\
		\
		void main() {\
			vec4 P = model_matrix * position;\
			gl_Position = P;\
			vtexture_coord = texture_coord;\
		}"
	);// gl_Position = persp_matrix * view_matrix * P;

#pragma endregion
	//Shader * vShader = RenderManager::GetInstance().CreateVertexShaderFromFile("diffuse_texture.vert");

#pragma region Fragment Shader Declaration
	Shader * fShader = RenderManager::GetInstance().CreateFragmentShader(
		"#version 130\n\
		uniform sampler2D usampler;\
		\
		in vec2 vtexture_coord;\
		\
		out vec4 frag_color;\
		\
		void main(void) {\
			vec3 diffuse_color = texture(usampler, vtexture_coord).xyz;\
			frag_color = vec4(diffuse_color, 1);\
		}"
	);
#pragma endregion
	//Shader * fShader = RenderManager::GetInstance().CreateFragmentShaderFromFile("diffuse_texture.frag");
	ShaderProgram * program = RenderManager::GetInstance().CreateShaderProgram("default");
	program->AttachShader(*vShader);
	program->AttachShader(*fShader);
	
	program->LinkShaders();

	program->AddAttribute("position");
	//program->AddAttribute("normal");
	program->AddAttribute("texture_coord");

	program->AddUniform("persp_matrix");
	program->AddUniform("view_matrix");
	program->AddUniform("model_matrix");
	program->AddUniform("normal_matrix");
	program->AddUniform("color");
	//program->AddUniform("light_color");

	RenderManager::GetInstance().SelectShaderProgram("default");
#pragma endregion

	// TODO: Look into tying this into the API without exposing so many Mesh calls directly
	//Mesh * mesh = Acrylicor::CreateMesh("player");
	//mesh->AddTriangle(
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f, 0.5f, 0.0f
	//);
	//mesh->FinishMesh();

	Acrylicor::LoadTexture("Textures/airplane.png", "player");
}

void TestGameState::GameStateInit(void)
{
	sgpPlayer = GameObjectFactory::GetInstance().LoadGameObjectFromFile("player.json");
	//Camera * camera = new Camera(Vector3D(0.0f, 0.0f, -10.0f), Vector3D(0, 0, -1));
}

void TestGameState::GameStateUpdate(double deltaTime)
{
	sgpPlayer->Update(deltaTime);
	//camera->Update();
}

void TestGameState::GameStateDraw(void)
{
	Acrylicor::RenderObject(*sgpPlayer);
}

void TestGameState::GameStateFree(void)
{
	delete sgpPlayer;
}

void TestGameState::GameStateUnload(void)
{

}
