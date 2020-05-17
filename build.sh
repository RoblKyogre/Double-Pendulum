#!/usr/bin/env bash

# This script builds everything from scratch,
# including the install of GLFW and other packages
# if they are not installed.

# Create build directory
if [ ! -d build ]
then
	mkdir build
fi
cd build

printf "\n\nBeginning build process...\n\n"

if [ ! -d files ]
then
	mkdir files
fi
cd files

if [ ! -e /usr/local/lib/libglfw3.a ]
then

printf "GLFW has not been detected on your system.\nThis script will install GLFW and other packages on your system.\n!! If you wish to exit, press CTRL+C. !!\n\n"

printf "Press any key to continue..."
read -n 1 -s
printf "\n"

# Install essential packages

sudo apt-get update 
for package in build-essential libevent-pthreads-2.0.5 doxygen xorg-dev libglu1-mesa-dev; do sudo apt-get install -y $package; done


# Install GLFW

wget "https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip"
unzip glfw-3.3.2.zip
cd glfw-3.3.2

mkdir build
cd build
cmake ..
cmake --build .
sudo make install

cd ../..

fi

# Compile program

cd ..

rm -f DoublePendulum

g++ -g ../main.cpp -o ./DoublePendulum -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -L../libs -lbox2d

if [ -e DoublePendulum ]
then
	printf "\nProgram successfully compiled in the \"build\" folder!\n"
else
	printf "\nProgram failed to compile. See the output above.\n"
fi
