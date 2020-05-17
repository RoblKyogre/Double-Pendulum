# Double-Pendulum
This is a simulation of a double pendulum using the Box2D physics engine.

## Using the Program

Controls:
* <Enter>: Reset
* <Space>: Pause
* <Scroll>: Zoom In/Out
* <Left Arrow>: Move Left
* <Right Arrow>: Move Right
* <Up Arrow>: Move Up
* <Down Arrow>: Move Down
* <Escape>: Exit

To set your own starting coordinates, add the coordinates when running the program from a terminal window.

Syntax (Linux Example): `./DoublePendulum x1 y1 x2 y2`

This program also generates a .csv file, which can be made into a spreadsheet or graphed.

## Dependencies

### [GLFW](https://www.glfw.org/)
* This must be download and built

Required Packages:
* build-essential
* libevent-pthreads-2.0.5
* doxygen
* xorg-dev
* libglu1-mesa-dev

### [Box2D](https://github.com/erincatto/box2d)
* Included with the project

## Compiling

### Linux
* Run `build.sh` (may require `sudo` access if it doesn't see GLFW installed)
* The file will be compiled as "DoublePendulum" in the "build" folder
* Running it with 4 additional command arguments will use the numbers given as the starting coordinates (see above)
* The program will generate a data.csv file with the data from the simulation
