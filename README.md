# Double-Pendulum
This is a simulation of a double pendulum using Google's LiquidFun physics engine.

## Dependencies

### [GLFW](https://www.glfw.org/)
Required Packages:
* build-essential
* libevent-pthreads-2.0.5
* doxygen
* xorg-dev
* libglu1-mesa-dev

### [Box2D](https://github.com/erincatto/box2d)
TODO

## Compiling

### Linux
1. Installing GLFW
  * Navigate to the directory of the GLFW source code
  * Execute `cmake .` to generate build files
  * Execute `make install` to install GLFW on your system (you may need to run this as sudo)
2. Compiling the actual program
  * Navigate to the directory of the source code for this project
  * `g++ -g ./main.cpp -o ./main -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor`
3. The file will be compiled as a shared library file named "main".

### Windows
TODO

### Mac OS
TODO
