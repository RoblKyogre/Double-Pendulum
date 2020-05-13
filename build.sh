#!/usr/bin/env bash

g++ -g ./main.cpp -o ./Double\ Pendulum -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -L./libs -lbox2d
