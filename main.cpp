#define PROFILE_MODE false

#if PROFILE_MODE
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif

#include <windows.h>

#include "InputManager.h"
#include "AcrylicorAPI.h"
#include "AcrylicorTypedefs.h"
#include "IGameState.h"
#include "TestGameState.h"


#if TEST_MODE
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Math2D.h"
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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	if (Acrylicor::Initialize("ObjectFiles/config.json") != 0)
		return 1;

	InputManager& inputMgr = InputManager::GetInstance();
	bool done = false;
	double dt = 0.0;
	IGameState * gameState = new TestGameState();
	gameState->GameStateLoad();
	gameState->GameStateInit();

	while (!done) {
		dt = Acrylicor::FrameStart();
		if (inputMgr.IsKeyPressed(ACR_ESCAPE))
			done = true;

		gameState->GameStateUpdate(dt);
		gameState->GameStateDraw();
		gameState->GameStatePostUpdate();

		Acrylicor::FrameEnd();
	}

	gameState->GameStateFree();
	gameState->GameStateUnload();
	delete gameState;

	#if PROFILE_MODE
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}
#endif