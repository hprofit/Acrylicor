PRG=acrylicor.exe
FLAGS=-O2 -Wall -Wextra -ansi -pedantic -Wunused -std=c++11 -Wno-unknown-pragmas
MSCOPEN=/EHsc /Fe
MSCARGS=opengl32.lib glew32.lib sdl2.lib sdl2main.lib /link /subsystem:console

ifeq (,$(findstring CYGWIN,$(OSTYPE)))
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

gpp:
	echo Compiling with GNU.
	g++ -c Vector2D.cpp $(FLAGS)
	g++ -c Vector3D.cpp $(FLAGS)
	g++ -c Matrix.cpp $(FLAGS)
	g++ -c Matrix2x2.cpp $(FLAGS)
	g++ -c Matrix3x3.cpp $(FLAGS)
	g++ -c LineSegment2D.cpp $(FLAGS)
	g++ -c Math2D.cpp $(FLAGS)
	g++ -c main.cpp $(FLAGS)
	g++ -o $(PRG) Matrix.o Matrix2x2.o Matrix3x3.o Vector3D.o Vector2D.o LineSegment2D.o Math2D.o main.o $(CYGWIN) $(FLAGS)
	
msc:
	echo Compiling with VS.
	cl $(MSCOPEN)$(PRG) main.cpp Matrix.cpp Matrix2x2.cpp Matrix3x3.cpp Vector3D.cpp Vector2D.cpp LineSegment2D.cpp Math2D.cpp $(MSCARGS)

vector:
	$(PRG) -v
	
mem:
	drmemory.exe -show_reachable $(PRG)
	
clean:
	rm -f *.exe *.tds *.o *.obj *manifest*