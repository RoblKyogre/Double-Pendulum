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
	
	printf "Packages may be missing\nThis script will install any necessary packages on your system.\n!! If you wish to exit, press CTRL+C. !!\n\n"
	
	printf "Press any key to continue..."
	read -n 1 -s
	printf "\n"
	
	sudo apt-get update 
	for package in build-essential cmake make g++ libevent-pthreads-2.0.5 doxygen xorg-dev libglu1-mesa-dev; do sudo apt-get install -y $package; done
	
	g++ -g ../main.cpp -o ./DoublePendulum -L../libs -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lbox2d
	
	if [ -e DoublePendulum ]
	then
		printf "\nProgram successfully compiled in the \"build\" folder!\n"
	else
		printf "\nProgram failed to compile. See the output above.\n"
fi
