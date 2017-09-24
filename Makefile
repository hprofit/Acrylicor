PRG=acrylicor.exe
FLAGS=-O2 -Wall -Wextra -ansi -pedantic -Wunused -std=c++11 -Wno-unknown-pragmas

ifeq (,$(findstring CYGWIN,$(OSTYPE)))
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

gpp:
	echo Compile all with C++
	g++ -c Vector2D.cpp $(FLAGS)
	g++ -c Vector3D.cpp $(FLAGS)
	g++ -c Matrix.cpp $(FLAGS)
	g++ -c Matrix2x2.cpp $(FLAGS)
	g++ -c Matrix3x3.cpp $(FLAGS)
	g++ -c main.cpp $(FLAGS)
	g++ -o $(PRG) Matrix.o Matrix2x2.o Matrix3x3.o Vector3D.o Vector2D.o main.o $(CYGWIN) $(FLAGS)
	
vector:
	$(PRG) -v
	
mem:
	drmemory.exe -show_reachable $(PRG)
	
clean:
	rm -f *.exe *.tds *.o *.obj *manifest*