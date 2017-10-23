// Necessary
#include <iostream>
#include "TestGameState.h"
#include "AcrylicorAPI.h"

// Don't like
#include "Mesh.h"
#include "TransformComponent.h"
#include "RenderManager.h"
#include "Shader.h"
#include "ShaderProgram.h"

// Test Files
#include "Player.h"


static Player * sgpPlayer;

TestGameState::TestGameState()
{
}

TestGameState::~TestGameState()
{
}

void TestGameState::GameStateLoad(void)
{
	GLint value;
#pragma region fshader
	//const char *fragment_shader_text =
	//	"#version 130\n\
	//	in vec4 vcolor;\
	//	out vec4 frag_color;\
	//	void main(void) {\
	//		frag_color = vec4(1,0,1,1);\
	//	}";
	//GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fshader, 1, &fragment_shader_text, 0);
	//glCompileShader(fshader);
	//glGetShaderiv(fshader, GL_COMPILE_STATUS, &value);
	//if (!value) {
	//	std::cerr << "Fragment shader failed to compile" << std::endl;
	//	char buffer[1024];
	//	glGetShaderInfoLog(fshader, 1024, 0, buffer);
	//	std::cerr << buffer << std::endl;
	//}
#pragma endregion
	Shader * fShader = RenderManager::GetInstance().CreateFragmentShader(
		"#version 130\n\
		in vec4 vcolor;\
		out vec4 frag_color;\
		void main(void) {\
			frag_color = vec4(1,0,1,1);\
		}"
	);

#pragma region vshader
	/*const char *vertex_shader_text =
		"#version 130\n\
		attribute vec4 position;\
		attribute vec4 normal;\
		\
		uniform mat4 persp_matrix;\
		uniform mat4 view_matrix;\
		uniform mat4 model_matrix;\
		uniform mat4 normal_matrix;\
		uniform vec4 color;\
		\
		out vec4 vcolor;\
		void main() {\
			gl_Position = persp_matrix * model_matrix * position;\
			vec4 m = normal_matrix * normal;\
			float f = max(0,m.z)/length(m);\
			vcolor = vec4(f*color.xyz,color.w);\
		}"; //persp_matrix * view_matrix * 
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vertex_shader_text, 0);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		std::cerr << "Vertex shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}*/
#pragma endregion
	Shader * vShader = RenderManager::GetInstance().CreateVertexShader(
		"#version 130\n\
		attribute vec4 position;\
		attribute vec4 normal;\
		\
		uniform mat4 persp_matrix;\
		uniform mat4 view_matrix;\
		uniform mat4 model_matrix;\
		uniform mat4 normal_matrix;\
		uniform vec4 color;\
		\
		out vec4 vcolor;\
		void main() {\
			gl_Position = persp_matrix * model_matrix * position;\
			vec4 m = normal_matrix * normal;\
			float f = max(0,m.z)/length(m);\
			vcolor = vec4(color.xyz, color.w);\
		}" //persp_matrix * view_matrix *
	); //vcolor = vec4(f*color.xyz,color.w);\

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

#pragma region link shaders
	//program = glCreateProgram();
	//glAttachShader(program, fshader);
	//glAttachShader(program, vshader);

	//glLinkProgram(program);
	//glGetProgramiv(program, GL_LINK_STATUS, &value);

	//if (!value) {
	//	std::cerr << "vertex shader failed to compile" << std::endl;
	//	char buffer[1024];
	//	glGetShaderInfoLog(vshader, 1024, 0, buffer);
	//	std::cerr << buffer << std::endl;
	//}
#pragma endregion


#pragma region Link attributes
	//aposition = glGetAttribLocation(program, "position");
	//anormal = glGetAttribLocation(program, "normal");
	//upersp_matrix = glGetUniformLocation(program, "persp_matrix");
	//uview_matrix = glGetUniformLocation(program, "view_matrix");
	//umodel_matrix = glGetUniformLocation(program, "model_matrix");
	//unormal_matrix = glGetUniformLocation(program, "normal_matrix");
	//ucolor = glGetUniformLocation(program, "color");
#pragma endregion


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
	sgpPlayer = new Player();
	static_cast<TransformComponent*>(sgpPlayer->Get(CT_TRANSFORM))->SetScale(0.5f);
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
