#!/usr/bin/env bash

# This program simply compiles the program.

if [ ! -d build ]
then
	mkdir build
fi
cd build

rm -f DoublePendulum

g++ -g ../main.cpp -o ./DoublePendulum -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -L../libs -lbox2d

if [ -e DoublePendulum ]
then
	printf "\nProgram successfully compiled in the \"build\" folder!\n"
else
	printf "\nProgram failed to compile. See the output above.\n"
fi
