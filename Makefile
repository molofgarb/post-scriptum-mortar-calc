ver := -std=c++17

# Build executable
psMortarTool.exe: main.o coordinate.o 
	g++ ${ver} main.o coordinate.o -o psMortarTool.exe 

# Compile main
main.o: coordinate.h main.cpp
	g++ -c ${ver} main.cpp -o main.o

# Compile coordinate
coordinate.o: coordinate.h coordinate.cpp
	g++ -c ${ver} coordinate.cpp -o coordinate.o
