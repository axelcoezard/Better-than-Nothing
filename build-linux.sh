#!/bin/bash

# Create build directory
mkdir -p build

# Change to build directory
cd build

# Run cmake
cmake ..

# Run make
make
