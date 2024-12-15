#!/bin/bash
#rm opengl-template

clear

cmake ..

cmake --build .

./opengl-template
