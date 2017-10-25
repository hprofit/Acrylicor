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

// Test Files
#include "Player.h"


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
#pragma region Fragment Shader Declaration
	Shader * fShader = RenderManager::GetInstance().CreateFragmentShader(
		"#version 130\n\
		uniform vec3 light_color;\
		uniform sampler2D usampler;\
		\
		in vec4 normal_vector;\
		in vec4 light_vector;\
		in vec2 vtexture_coord;\
		\
		out vec4 frag_color;\
		\
		void main(void) {\
			vec3 diffuse_color = texture(usampler, vtexture_coord).xyz;\
			vec4 m = normalize(normal_vector);\
			vec4 L = normalize(light_vector);\
			vec3 r = max(dot(m, L), 0) * diffuse_color * light_color;\
			frag_color = vec4(r, 1);\
		}"
	);
#pragma endregion
#pragma region Vertex Shader Declaration
	Shader * vShader = RenderManager::GetInstance().CreateVertexShader(
		"#version 130\n\
		in vec4 position;\
		in vec4 normal;\
		in vec2 texture_coord;\
		\
		uniform mat4 persp_matrix;\
		uniform mat4 view_matrix;\
		uniform mat4 model_matrix;\
		uniform mat4 normal_matrix;\
		uniform vec4 color;\
		\
		out vec4 vcolor;\
		\
		void main() {\
			vec4 P = model_matrix * position;\
			gl_Position = P;\
			vec4 m = normal_matrix * normal;\
			float f = max(0,m.z)/length(m);\
			vcolor = vec4(f*color.xyz,color.w);\
			vtexture_coord = texture_coord;\
		}" 
	);// gl_Position = persp_matrix * view_matrix * P;\
#pragma endregion
	ShaderProgram * program = RenderManager::GetInstance().CreateShaderProgram("default");
	program->AttachShader(*fShader);
	program->AttachShader(*vShader);
	program->LinkShaders();
	program->AddAttribute("position");
	program->AddAttribute("normal");

	program->AddUniform("persp_matrix");
	program->AddUniform("view_matrix");
	program->AddUniform("model_matrix");
	program->AddUniform("normal_matrix");
	program->AddUniform("color");

	RenderManager::GetInstance().SelectShaderProgram("default");
#pragma endregion

	// TODO: Look into tying this into the API without exposing so many Mesh calls directly
	Mesh * mesh = Acrylicor::CreateMesh("player");
	mesh->AddTriangle(
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	);
	mesh->FinishMesh();
}

void TestGameState::GameStateInit(void)
{
	sgpPlayer = GameObjectFactory::GetInstance().LoadGameObjectFromFile("player.json");
	//sgpPlayer->AddComponent(new TransformComponent(*sgpPlayer, Vector2D(0, 0, 0), 0.0f, .5f, .5f));
	//sgpPlayer->AddComponent(new ControllerComponent(*sgpPlayer));
	//sgpPlayer->AddComponent(new SpriteComponent(*sgpPlayer, "player"));



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
