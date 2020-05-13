#!/usr/bin/env bash

# This script builds everything from scratch,
# including the install of GLFW and other packages.

# Do not run this if you already have installed
# GLFW or you have already run this script!

# Warn user 

printf "This program will install GLFW and other packages on your system while compiling.\n!! If you wish to exit, press CTRL+C. !!\nDo not run this if you already ran this once or have already installed GLFW.\n\n"

printf "Press any key to continue..."
read -n 1 -s

sudo printf "\n\nBeginning build process...\n\n"

# Create build directory
rm -rf build
mkdir build
cd build

mkdir files
cd files

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


# Compile program
cd ../..
./compile.sh
