ver := -std=c++17

# Build executable
psMortarTool: main.o coordinate.o dist_to_mils.o mortar.o assets.o
	g++ ${ver} \
	main.o \
	coordinate.o \
	dist_to_mils.o \
	mortar.o \
	assets.o \
	-o psMortarTool

# Compile main
main.o: src/coordinate.h src/main.cpp
	g++ -c ${ver} src/main.cpp -o main.o

# Compile coordinate
coordinate.o: src/coordinate.h src/coordinate.cpp
	g++ -c ${ver} src/coordinate.cpp -o coordinate.o

# Compile dist_to_mils
dist_to_mils.o: src/dist_to_mils.h src/dist_to_mils.cpp
	g++ -c ${ver} src/dist_to_mils.cpp -o dist_to_mils.o

# Compile mortar
mortar.o: src/mortar.h src/mortar.cpp
	g++ -c ${ver} src/mortar.cpp -o mortar.o

# Compile assets
assets.o: src/assets.h src/assets.cpp
	g++ -c ${ver} src/assets.cpp -o assets.o
