#!/usr/bin/env bash

# This script builds the program from scratch

# Create build directory
if [ ! -d build ]
then
	mkdir build
fi
cd build

# Compile Program

printf "\n\nBeginning build process...\n\n"

rm -f DoublePendulum

g++ -g ../main.cpp -o ./DoublePendulum -L../libs -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lbox2d

# Check if program compiled

if [ -e DoublePendulum ]
then
	printf "\nProgram successfully compiled in the \"build\" folder!\n"
else
	printf "\nProgram failed to compile. See the output above.\n"
fi
