#!/bin/bash

clear

# Compile the C++ files; if compilation succeeds, run the executable
g++ *.cpp -o main.exe && ./main.exe
