//#define _USE_SDL_DEFINES

#include <stdio.h>
#include <windows.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Math2D.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "FrameRateController.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Camera.h"
#include "RenderManager.h"
#include "DefaultShaderProgram.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include <iostream>

#include "Mesh.h"

#define TEST_MODE 0

#if TEST_MODE
int main(int argc, char ** argv)
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			if (strlen(*argv)>1)
			{
				switch (argv[i][1])
				{
				case 'a':
					Vector2DTests();
					Vector3DTests();
					//MatrixTests();
					Matrix2x2Tests();
					Matrix3x3Tests();
					Matrix4x4Tests();
					StaticCollisionTests();
					break;
				case 'v':
					if (strlen(argv[i]) > 2)
					{
						if (argv[i][2] == '2')
							Vector2DTests();
						else if (argv[i][2] == '3')
							Vector3DTests();
					}
					else {
						Vector2DTests();
						Vector3DTests();
					}
					break;
				case 'm':
					if (strlen(argv[i]) > 2)
					{
						switch (argv[i][2]) {
							case 'a':
								MatrixTests();
								break;
							case '2':
								Matrix2x2Tests();
								break;
							case '3':
								Matrix3x3Tests();
								break;
							case '4':
								Matrix4x4Tests();
							default:
								printf("Unrecognized flag: %s", argv[i]);
								return 1;
						}
					}
					else 
					{
						//MatrixTests();
						Matrix2x2Tests();
						Matrix3x3Tests();
						Matrix4x4Tests();
					}
					break;
				case 's':
					StaticCollisionTests();
					break;
				default:
					printf("Unrecognized flag: %s", argv[i]);
					return 1;
				}
			}
		}
	}
	return 0;
}
#endif

#if !TEST_MODE

//static DefaultShaderProgram * program;
GLint	program,
		aposition,
		anormal,
		upersp_matrix,
		uview_matrix,
		umodel_matrix,
		unormal_matrix,
		ucolor;

int Initialize()
{
	// Init Window
	WindowManager::GetInstance(800, 800, "My Game");

	RenderManager& renderManager = RenderManager::GetInstance();
	if (!renderManager.Init())
		return 1;
	/*
#pragma region Vertex Shader Definition
	const char *vertex_shader_text =
		"#version 130\n\
		uniform mat4 persp_matrix;\
		uniform mat4 view_matrix;\
		uniform mat4 model_matrix;\
		uniform mat4 normal_matrix;\
		uniform vec4 color;\
		\
		out vec4 vcolor;\
		void main() {\
			gl_Position = persp_matrix * view_matrix * model_matrix;\
			vcolor = vec4(color.xyz,color.w);\
		}";
#pragma endregion
	Shader vertexShader = Shader(vertex_shader_text, VERTEX_SHADER);

#pragma region Fragment Shader Definition
	const char *fragment_shader_text =
		"#version 130\n\
		in vec4 vcolor;\
		out vec4 frag_color;\
		void main(void) {\
			frag_color = vcolor;\
		}";
#pragma endregion
	Shader fragmentShader = Shader(fragment_shader_text, FRAGMENT_SHADER);

	//ShaderProgram * program = renderManager.CreateShaderProgram("Default");
	program = new DefaultShaderProgram();
	program->AttachShader(vertexShader);
	program->AttachShader(fragmentShader);
	program->LinkShaders();
	*/

	GLint value;
#pragma region fshader
	const char *fragment_shader_text =
		"#version 130\n\
		in vec4 vcolor;\
		out vec4 frag_color;\
		void main(void) {\
			frag_color = vec4(1,0,1,1);\
		}";
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragment_shader_text, 0);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		std::cerr << "Fragment shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(fshader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}
#pragma endregion

#pragma region vshader
	const char *vertex_shader_text =
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
	}
#pragma endregion

#pragma region link shaders
	program = glCreateProgram();
	glAttachShader(program, fshader);
	glAttachShader(program, vshader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &value);

	if (!value) {
		std::cerr << "vertex shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}
#pragma endregion

#pragma region Link attributes
	aposition = glGetAttribLocation(program, "position");
	anormal = glGetAttribLocation(program, "normal");
	upersp_matrix = glGetUniformLocation(program, "persp_matrix");
	uview_matrix = glGetUniformLocation(program, "view_matrix");
	umodel_matrix = glGetUniformLocation(program, "model_matrix");
	unormal_matrix = glGetUniformLocation(program, "normal_matrix");
	ucolor = glGetUniformLocation(program, "color");

	glEnable(GL_DEPTH_TEST);
#pragma endregion

	ResourceManager& resMgr = ResourceManager::GetInstance();
	Mesh * mesh = resMgr.LoadMesh("player");
	mesh->AddTriangle(
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	);
	mesh->FinishMesh();

	return 0;
}

double FrameStart()
{
	FrameRateController::GetInstance().FrameStart();
	double dt = FrameRateController::GetInstance().GetFrameTime();

	WindowManager::GetInstance().FrameStart();
	RenderManager::GetInstance().FrameStart();

	InputManager::GetInstance().Update();
	return dt;
}

void FrameEnd()
{
	RenderManager::GetInstance().FrameEnd();
	WindowManager::GetInstance().FrameEnd();
	FrameRateController::GetInstance().FrameEnd();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	if (Initialize() != 0)
		return 1;

	RenderManager& renderMgr = RenderManager::GetInstance();
	InputManager& inputMgr = InputManager::GetInstance();
	bool done = false;
	double dt = 0.0;
	Camera * camera = new Camera(Vector3D(0.0f, 0.0f, -10.0f), Vector3D(0, 0, -1));
	GameObject * player = new GameObject();
	player->AddSpriteComponent("player");
	player->AddTransformComponent(Vector2D(0.0f, 0.0f, 1.0f), 0.0f, 0.5f, 0.5f);

	while (!done) {
		dt = FrameStart();

		if (inputMgr.IsKeyPressed(ACR_ESCAPE))
			done = true;

		if (inputMgr.IsKeyPressed(ACR_W)) {
			player->GetTransformComponent()->UpdatePosition(Vector2D(0.0f, 1.0f) * dt);
		}
		if (inputMgr.IsKeyPressed(ACR_S)) {
			player->GetTransformComponent()->UpdatePosition(Vector2D(0.0f, -1.0f) * dt);
		}
		if (inputMgr.IsKeyPressed(ACR_A)) {
			player->GetTransformComponent()->UpdatePosition(Vector2D(-1.0f, 0.0f) * dt);
		}
		if (inputMgr.IsKeyPressed(ACR_D)) {
			player->GetTransformComponent()->UpdatePosition(Vector2D(1.0f, 0.0f) * dt);
		}

		player->GetTransformComponent()->BuildModelTransform();

		//camera->Update();
		renderMgr.RenderGameObject(*camera, *player);

		FrameEnd();
	}

	delete camera;
	delete player;
	//delete program;

	return 0;
}
#endif