#define _USE_MATH_DEFINES
#define _USE_SDL_DEFINES
#define EPSILON 0.0001f
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <windows.h>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Math2D.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

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

	// SDL: initialize and create a window
	SDL_Init(SDL_INIT_VIDEO);
	const char *title = "Acrylicor";
	int width = 500,
		height = 500;
	SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// GLEW: get function bindings (if possible)
	glewInit();
	if (!GLEW_VERSION_2_0) {
		printf("needs OpenGL version 2.0 or better");
		return -1;
	}

	// animation loop
	bool done = false;
	//Client *client = new Client(0);
	Uint32 ticks_last = SDL_GetTicks();
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			//case SDL_KEYDOWN:
			//	if (event.key.keysym.sym == SDLK_ESCAPE)
			//		done = true;
			//	else
			//		client->keypress(event.key.keysym.sym);
			//	break;
			//case SDL_WINDOWEVENT:
			//	if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			//		client->resize(event.window.data1, event.window.data2);
			//	break;
			//case SDL_MOUSEMOTION:
			//	if ((event.motion.state&SDL_BUTTON_LMASK) != 0
			//		|| (event.motion.state&SDL_BUTTON_RMASK) != 0)
			//		client->mousedrag(event.motion.xrel, event.motion.yrel,
			//		(event.motion.state&SDL_BUTTON_LMASK) != 0);
			//	break;
			}
		}
		Uint32 ticks = SDL_GetTicks();
		double dt = 0.001*(ticks - ticks_last);
		ticks_last = ticks;
		//client->draw(dt);
		SDL_GL_SwapWindow(window);
	}

	// clean up
	//delete client;
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	return 0;
}