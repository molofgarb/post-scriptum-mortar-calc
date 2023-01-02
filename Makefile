.PHONY: all clean

CC := g++
FLAGS := -std=c++17 -O2
LINKS :=

all: psMortarTool.exe

clean:
	-rm *.o

# Build executable
psMortarTool.exe: main.o coordinate.o dist_to_mils.o mortar.o assets.o
	${CC} ${FLAGS} $^ ${LINKS} -o $@

# Compile main
main.o: src/main.cpp
	${CC} ${FLAGS} -c $^ -o $@

# Compile coordinate
coordinate.o: src/coordinate.cpp
	${CC} ${FLAGS} -c $^ -o $@

# Compile dist_to_mils
dist_to_mils.o: src/dist_to_mils.cpp
	${CC} ${FLAGS} -c $^ -o $@

# Compile mortar
mortar.o: src/mortar.cpp
	${CC} ${FLAGS} -c $^ -o $@

# Compile assets
assets.o: src/assets.cpp
	${CC} ${FLAGS} -c $^ -o $@


